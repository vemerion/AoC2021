#include <iostream>
#include <set>

using Pos = std::pair<int16_t, int16_t>;
using Grid = std::set<Pos>;

struct Image {
  std::string algo;
  Grid grid;
  int16_t start, end, part1, part2;
  uint8_t step = 0;

  char border() {
    if (algo.front() == '.')
      return '0';
    return step % 2 == 0 ? '0' : '1';
  }

  void parse() {
    std::string line;
    
    start = 0;
    end = 0;

    std::cin >> algo;
    while (std::cin >> line) {
      for (uint16_t col = 0; col < line.size(); col++)
        if (line[col] == '#')
          grid.insert(std::make_pair(end, col));
      end++;
    }
    end--;
  }

  uint16_t litCount() {
    return grid.size();
  }

  char get(int16_t row, int16_t col) {
    if (row < start || row > end || col < start || col > end)
      return border();

    if (grid.count(std::make_pair(row, col)))
      return '1';
    return '0';
  }

  void print() {
    for (int16_t i = start; i <= end; i++) {
      for (int16_t j = start; j <= end; j++)
        if (grid.count(std::make_pair(i, j)))
          std::cout << '#';
        else
          std::cout << '.';
      std::cout << '\n';
    }
    std::cout << '\n';
  }

  bool willBeLit(int16_t row, int16_t col) {
    std::string n = "";

    for (int16_t i = -1; i <= 1; i++)
      for (int16_t j = -1; j <= 1; j++)
        n += get(row + i, col + j);
    
    return algo[stoi(n, nullptr, 2)] == '#';
  }


  void run() {
    Grid next;

    for (int16_t row = start - 1; row <= end + 1; row++)
      for (int16_t col = start - 1; col <= end + 1; col++)
        if (willBeLit(row, col))
          next.insert(std::make_pair(row, col));

    grid = next;

    start--;
    end++;

    step++;

    if (step == 2)
      part1 = litCount();
    else if (step == 50)
      part2 = litCount();
  }
};

int main() {
  Image image;

  image.parse();
  for (uint8_t i = 0; i < 50; i++)
    image.run();


  std::cout << "Part 1 result = " << image.part1 << '\n';
  std::cout << "Part 2 result = " << image.part2 << '\n';

  return 0;
}
