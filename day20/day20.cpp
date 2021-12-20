#include <iostream>
#include <map>
#include <limits>

using Pos = std::pair<int16_t, int16_t>;

struct Image {
  std::string algo;
  std::map<Pos, char> grid;
  int16_t start, end, part1, part2;
  uint8_t step = 0;

  char border() {
    if (algo.front() == '.')
      return '0';
    return step % 2 == 0 ? '0' : '1';
  }

  void growBorder() {
    start--;
    end++;
    char c = border();
    for (int16_t i = start; i <= end; i++) {
      grid[std::make_pair(start, i)] = c;
      grid[std::make_pair(i, start)] = c;
      grid[std::make_pair(end, i)] = c;
      grid[std::make_pair(i, end)] = c;
    }
  }

  void parse() {
    std::string line;
    
    start = 0;
    end = 0;

    std::cin >> algo;
    while (std::cin >> line) {
      for (uint16_t col = 0; col < line.size(); col++)
        grid[std::make_pair(end, col)] = line[col] == '#' ? '1' : '0';
      end++;
    }
    end--;
  }

  uint16_t litCount() {
    uint16_t count = 0;
    for (auto& pair : grid)
      count += pair.second == '1';
    return count;
  }

  char get(int16_t row, int16_t col) {
    Pos p = std::make_pair(row, col);
    if (grid.count(p))
      return grid[p];
    return border();
  }

  void print() {
    for (int16_t i = start; i <= end; i++) {
      for (int16_t j = start; j <= end; j++)
        std::cout << (grid[std::make_pair(i, j)] == '1' ? '#' : '.');
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
    std::map<Pos, char> next;

    growBorder();

    for (auto& pair : grid) {
      uint16_t row = pair.first.first;
      uint16_t col = pair.first.second;
      for (int16_t i = -1; i <= 1; i++)
        for (int16_t j = -1; j <= 1; j++)
          next[std::make_pair(row + i, col + j)] = willBeLit(row + i, col + j) ? '1' : '0';
    }

    grid = next;

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
