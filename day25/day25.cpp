#include <iostream>
#include <map>
#include <array>

using Pos = std::pair<uint8_t, uint8_t>;
using Grid = std::map<Pos, char>;

static Pos move(Grid& grid, Pos start, char c, uint8_t rows, uint8_t cols) {
  Pos p;
  if (c == '>') {
    p = std::make_pair(start.first, start.second == cols - 1 ? 0 : start.second + 1);
  } else if (c == 'v') {
    p = std::make_pair(start.first == rows - 1 ? 0 : start.first + 1, start.second);
  }

  if (grid.count(p))
    return start;

  return p;
}

static constexpr std::array<char, 2> CUCUMBERS = { '>', 'v' };

static uint16_t simulate(Grid& grid, uint8_t rows, uint8_t cols) {
  Grid prev, next;
  uint16_t steps = 0;

  do {
    prev = grid;
    for (char c : CUCUMBERS) {
      for (auto& pair : grid) {
        if (pair.second == c) {
          Pos p = move(grid, pair.first, pair.second, rows, cols);
          next.emplace(p, pair.second);
        } else {
          next.emplace(pair.first, pair.second);
        }
      }
      grid = next;
      next.clear();
    }
    steps++;
  } while (prev != grid);

  return steps;
}

int main() {
  Grid grid;
  std::string line;
  uint8_t row, col;

  row = 0;

  while (std::cin >> line) {
    for (col = 0; col < line.size(); col++)
      if (line[col] != '.')
        grid.emplace(std::make_pair(row, col), line[col]);
    row++;
  }

  std::cout << "Result = " << simulate(grid, row, col) << '\n';
  return 0;
}
