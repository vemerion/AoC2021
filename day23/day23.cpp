#include <iostream>
#include <map>
#include <unordered_map>
#include <list>
#include <set>
#include <vector>

using Pos = std::pair<int8_t, int8_t>;
using Grid = std::map<Pos, char>;
using Cache = std::unordered_map<std::string, uint32_t>;

static uint8_t roomSize(Grid& grid) {
  uint8_t size = 0;
  while (grid.count(std::make_pair(2, size)))
    size++;
  return size;
}

#if 0
static void print(Grid& grid) {
  for (int8_t y = 0; y < roomSize(grid); y++) {
    for (int8_t x = 0; x < 11; x++) {
      Pos p = std::make_pair(x, y);
      if (grid.count(p))
        std::cout << grid[p];
      else
        std::cout << '#';
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}
#endif

static char roomType(int8_t x) {
  switch (x) {
    case 2:
      return 'A';
    case 4:
      return 'B';
    case 6:
      return 'C';
    case 8:
      return 'D';
  }
  
  std::cout << "ROOM TYPE PROBLEMS :(\n";
  return 0;
}

static int8_t filledUp(Grid& grid, int8_t x) {
  uint8_t y = roomSize(grid) - 1;
  char type = roomType(x);
  while (y > 0) {
    if (grid[std::make_pair(x, y)] != type)
      return y + 1;
    y--;
  }
  return y + 1;
}

static bool isDone(Grid& grid) {
  for (uint8_t i = 1; i < roomSize(grid); i++) {
    for (uint8_t x = 2; x <= 8; x += 2)
      if (grid[std::make_pair(x, i)] != roomType(x))
        return false;
  }
  return true;
}

struct Move {
  Pos pos;
  uint32_t count;

  int8_t x() {
    return pos.first;
  }

  int8_t y() {
    return pos.second;
  }

  uint32_t getCost(char type) {
    switch (type) {
      case 'A':
        return count;
      case 'B':
        return count * 10;
      case 'C':
        return count * 100;
      case 'D':
        return count * 1000;
    }
    std::cout << "Big trouble! " << type << '\n';
    return 0;
  }

  Pos travel(int8_t x, int8_t y) {
    return std::make_pair(pos.first + x, pos.second + y);
  }
};

bool isInFinalRoom(Pos pos, char type) {
  return pos.second != 0 && roomType(pos.first) == type;
}

static std::vector<Move> findMoves(Grid& grid, Pos start, char type) {
  std::vector<Move> moves, validated;
  std::set<Pos> positions;

  moves.push_back({start, 0});
  positions.insert(start);

  for (uint8_t i = 0; i < moves.size(); i++) {
    Move m = moves[i];
    for (int8_t x = -1; x <= 1; x++) {
      for (int8_t y = -1; y <= 1; y++) {
        if (std::abs(x + y) == 1) {
          Pos p = m.travel(x, y);
          if (positions.count(p) || !grid.count(p) || grid[p] != '.')
            continue;
          moves.push_back({p, m.count + 1});
          positions.insert(p);
        }
      }
    }
  }

  for (Move& m : moves) {
    if (start == m.pos)
      continue;

    int8_t x = m.x();
    int8_t y = m.y();


    if (x == start.first)
      continue;

    if (y == 0 && (x == 2 || x == 4 || x == 6 || x == 8))
      continue;
  
    if (y == 0 && start.second == 0)
      continue;

    if (y > 0 && roomType(x) != type)
      continue;

    if (y > 0 && isInFinalRoom(m.pos, type) && filledUp(grid, x) > y + 1)
      continue;

    validated.push_back(m);
  }

  return validated;
}

static std::string toString(Grid& grid) {
  std::string s;
  for (auto& pair : grid)
    s += pair.second;
  return s;
}

static void organize(Grid& grid, uint32_t cost, uint32_t& cheapest, Cache& cache) {
  if (cheapest != 0 && cost >= cheapest)
    return;

  std::string s = toString(grid);
  if (cache.count(s) && cache[s] <= cost) {
    return;
  } else
    cache[s] = cost;
    
  if (isDone(grid)) {
    if (cost < cheapest || cheapest == 0)
      cheapest = cost;
    if (cheapest == 0)
      std::cout << "TELEPORTING FISH!\n";
    return;
  }

  for (auto& pair : grid) {
    auto pos = pair.first;
    char type = pair.second;
    if (type == '.' || (isInFinalRoom(pos, type) && filledUp(grid, pos.first) <= pos.second))
      continue;
    std::vector<Move> moves = findMoves(grid, pos, type);
    for (Move& m : moves) {
      Grid next = grid;
      next[pos] = '.';
      next[m.pos] = type;
      organize(next, cost + m.getCost(type), cheapest, cache);
    }
  }
}

static uint32_t organize(Grid& grid) {
  uint32_t cost = 0;
  Cache cache;
  organize(grid, 0, cost, cache);

  return cost;
}

int main() {
  Grid grid1, grid2;

  for (uint8_t i = 0; i < 11; i++) {
    grid1[std::make_pair(i, 0)] = '.';
    grid2[std::make_pair(i, 0)] = '.';
  }

  grid1[std::make_pair(2, 1)] = 'D';
  grid1[std::make_pair(2, 2)] = 'C';
  grid1[std::make_pair(4, 1)] = 'C';
  grid1[std::make_pair(4, 2)] = 'A';
  grid1[std::make_pair(6, 1)] = 'D';
  grid1[std::make_pair(6, 2)] = 'A';
  grid1[std::make_pair(8, 1)] = 'B';
  grid1[std::make_pair(8, 2)] = 'B';

  grid2[std::make_pair(2, 1)] = 'D';
  grid2[std::make_pair(2, 2)] = 'D';
  grid2[std::make_pair(2, 3)] = 'D';
  grid2[std::make_pair(2, 4)] = 'C';
  grid2[std::make_pair(4, 1)] = 'C';
  grid2[std::make_pair(4, 2)] = 'C';
  grid2[std::make_pair(4, 3)] = 'B';
  grid2[std::make_pair(4, 4)] = 'A';
  grid2[std::make_pair(6, 1)] = 'D';
  grid2[std::make_pair(6, 2)] = 'B';
  grid2[std::make_pair(6, 3)] = 'A';
  grid2[std::make_pair(6, 4)] = 'A';
  grid2[std::make_pair(8, 1)] = 'B';
  grid2[std::make_pair(8, 2)] = 'A';
  grid2[std::make_pair(8, 3)] = 'C';
  grid2[std::make_pair(8, 4)] = 'B';

  std::cout << "Part 1 result = " << organize(grid1) << '\n';
  std::cout << "Part 2 result = " << organize(grid2) << '\n';
  return 0;
}
