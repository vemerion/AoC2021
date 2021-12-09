#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

struct Location {
  uint8_t height;
  bool visited = false;
};

using Row = std::vector<Location>;
using Grid = std::vector<Row>;

static bool isLowPoint(Grid& grid, uint16_t row, uint16_t col) {
  uint8_t height = grid[row][col].height;
  
  return (row == 0 || grid[row - 1][col].height > height) && (col == 0 || grid[row][col - 1].height > height) && (row == grid.size() - 1 || grid[row + 1][col].height > height) && (col == grid[row].size() - 1 || grid[row][col + 1].height > height);
}

static uint16_t riskPointSum(Grid& grid) {
  uint16_t sum = 0;

  for (uint16_t row = 0; row < grid.size(); row++)
    for (uint16_t col = 0; col < grid[row].size(); col++)
      if (isLowPoint(grid, row, col))
        sum += grid[row][col].height + 1;

  return sum;
}

static uint16_t countBasin(Grid& grid, uint16_t startRow, uint16_t startCol) {
  std::list<std::pair<uint16_t, uint16_t>> positions;
  uint16_t count = 0;

  positions.push_back(std::make_pair(startRow, startCol));

  while (!positions.empty()) {
    auto pos = positions.front();
    positions.pop_front();
    uint16_t row = pos.first;
    uint16_t col = pos.second;

    if (grid[row][col].visited)
      continue;
    count++;
    grid[row][col].visited = true;
    for (int8_t i = -1; i <= 1; i++)
      for (int8_t j = -1; j <= 1; j++)
        if (std::abs(i + j) == 1 && (row != 0 || i != -1) && (col != 0 || j != -1) && (row != grid.size() - 1 || i != 1) && (col != grid[row + i].size() - 1 || j != 1) && !grid[row + i][col + j].visited && grid[row + i][col + j].height != 9)
          positions.push_back(std::make_pair(row + i, col + j));
  }

  return count;
}

static uint32_t part2(Grid& grid) {
  std::vector<uint16_t> basins;
  for (uint16_t row = 0; row < grid.size(); row++)
    for (uint16_t col = 0; col < grid[row].size(); col++)
      if (isLowPoint(grid, row, col)) {
        basins.push_back(countBasin(grid, row, col));
      }

  std::sort(basins.begin(), basins.end());
  return basins[basins.size() - 1] * basins[basins.size() - 2] * basins[basins.size() - 3];
}

int main() {
  Grid grid;
  std::string line;

  while (std::cin >> line) {
    grid.push_back(Row{});
    for (char c : line) {
      Location p{};
      p.height = c - '0';
      grid.back().push_back(p);
    }
  }

  std::cout << "Part 1 result = " << riskPointSum(grid) << '\n';
  std::cout << "Part 2 result = " << part2(grid) << '\n';
  return 0;
}
