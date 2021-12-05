#include <iostream>
#include <map>

using Num = uint16_t;
using Pos = std::pair<Num, Num>;
using Grid = std::map<Pos, Num>;

static Num overlap(Grid& grid) {
  Num count = 0;
  for (auto& p : grid)
    count += p.second > 1;
  return count;
}

static void fill(Grid& grid, Num x1, Num y1, Num x2, Num y2, bool diagonals) {
  if (!diagonals && x1 != x2 && y1 != y2)
    return;

  Num countX, countY;
  int16_t dx, dy;

  countX = std::abs(x2 - x1);
  countY = std::abs(y2 - y1);
  dx = x1 == x2 ? 0 : (x2 - x1) / countX;
  dy = y1 == y2 ? 0 : (y2 - y1) / countY;

  for (Num i = 0; i <= std::max(countX, countY); i++) {
    Num count = 0;
    Pos p = std::make_pair(x1 + dx * i, y1 + dy * i);
    if (grid.count(p))
      count = grid[p];
    grid[p] = count + 1;
  }
}

int main() {
  Grid grid1, grid2;
  char dummy;
  Num x1, x2, y1, y2;

  while (std::cin >> x1 >> dummy >> y1 >> dummy >> dummy >> x2 >> dummy >> y2) {
    fill(grid1, x1, y1, x2, y2, false);
    fill(grid2, x1, y1, x2, y2, true);
  }

  std::cout << "Part 1 result = " << overlap(grid1) << '\n';
  std::cout << "Part 2 result = " << overlap(grid2) << '\n';
  return 0;
}
