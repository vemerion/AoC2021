#include <iostream>
#include <array>
#include <list>


static constexpr uint8_t SIZE = 10;

using Grid = std::array<std::array<uint8_t, SIZE>, SIZE>;
using Pos = std::pair<uint8_t, uint8_t>;

static uint16_t simulate(Grid grid, uint8_t steps) {
  uint16_t total = 0;

  for (uint16_t step = 0; step < steps || steps == 0; step++) {
    std::list<Pos> positions;

    for (uint8_t row = 0; row < SIZE; row++)
      for (uint8_t col = 0; col < SIZE; col++)
        if (++grid[row][col] > 9)
          positions.push_back(std::make_pair(row, col));

    while (!positions.empty()) {
      Pos p = positions.front();
      uint8_t row = p.first;
      uint8_t col = p.second;
      positions.pop_front();

      for (int8_t r = -1; r <= 1; r++)
        for (int8_t c = -1; c <= 1; c++)
          if ((r != 0 || c != 0) && (row != 0 || r != -1) && (col != 0 || c != -1) && (row != SIZE - 1 || r != 1) && (col != SIZE - 1 || c != 1) && grid[row + r][col + c] <= 9 && ++grid[row + r][col + c] > 9)
            positions.push_back(std::make_pair(row + r, col + c));
    }

    uint8_t count = 0;
    for (uint8_t row = 0; row < SIZE; row++)
      for (uint8_t col = 0; col < SIZE; col++)
        if (grid[row][col] > 9) {
          grid[row][col] = 0;
          count++;
        }

    total += count;
    if (count == SIZE * SIZE)
      return step + 1;
  }

  return total;
}

int main() {
  Grid grid;
  std::string line;

  for (uint8_t row = 0; row < SIZE; row++) {
    std::cin >> line;
    for (uint8_t col = 0; col < SIZE; col++) {
      grid[row][col] = line[col] - '0';
    }
  }

  std::cout << "Part 1 result = " << simulate(grid, 100) << '\n';
  std::cout << "Part 2 result = " << simulate(grid, 0) << '\n';
  
  return 0;
}
