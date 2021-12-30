#include <iostream>
#include <vector>
#include <array>

using Pos = std::pair<uint8_t, uint8_t>;
using Grid = std::vector<std::vector<char>>;

static Pos move(Grid& grid, Pos start) {
  Pos p;
  char c = grid[start.first][start.second];
  if (c == '>') {
    p = std::make_pair(start.first, start.second == grid[start.first].size() - 1 ? 0 : start.second + 1);
  } else if (c == 'v') {
    p = std::make_pair(start.first == grid.size() - 1 ? 0 : start.first + 1, start.second);
  }

  if (grid[p.first][p.second] != '.')
    return start;

  return p;
}

static constexpr std::array<char, 2> CUCUMBERS = { '>', 'v' };

static uint16_t simulate(Grid& grid) {
  Grid prev, next;
  uint16_t steps = 0;

  next = grid;

  do {
    prev = grid;
    for (char c : CUCUMBERS) {
      for (uint8_t row = 0; row < grid.size(); row++) {
        for (uint8_t col = 0; col < grid[row].size(); col++) {
          if (grid[row][col] == c) {
            Pos p = move(grid, std::make_pair(row, col));
            next[row][col] = '.';
            next[p.first][p.second] = c;
          }
        }
      }
      grid = next;
    }
    steps++;
  } while (prev != grid);

  return steps;
}

int main() {
  Grid grid;
  std::string line;
  uint8_t row = 0;

  row = 0;

  while (std::cin >> line) {
    grid.push_back(std::vector<char>{});
    for (uint8_t col = 0; col < line.size(); col++)
      grid.back().push_back(line[col]);
    row++;
  }

  std::cout << "Result = " << simulate(grid) << '\n';
  return 0;
}
