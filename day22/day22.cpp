#include <iostream>
#include <set>
#include <list>
#include <tuple>

struct Cube {
  bool on;
  int64_t minX, maxX, minY, maxY, minZ, maxZ;

  bool intersect(const Cube& other) const {
    return !(maxX < other.minX || minX > other.maxX || maxY < other.minY || minY > other.maxY || maxZ < other.minZ || minZ > other.maxZ);
  }

  std::list<Cube> split(const Cube& other) const {
    std::list<Cube> splits;

    if (minX < other.minX) {
      splits.push_back({false, minX, other.minX - 1, minY, maxY, minZ, maxZ});
    }
    if (maxX > other.maxX) {
      splits.push_back({false, other.maxX + 1, maxX, minY, maxY, minZ, maxZ});
    }
    if (minY < other.minY) {
      splits.push_back({false, std::max(minX, other.minX), std::min(maxX, other.maxX), minY, other.minY - 1, minZ, maxZ});
    }
    if (maxY > other.maxY) {
      splits.push_back({false, std::max(minX, other.minX), std::min(maxX, other.maxX), other.maxY + 1, maxY, minZ, maxZ});
    }
    if (minZ < other.minZ) {
      splits.push_back({false, std::max(minX, other.minX), std::min(maxX, other.maxX), std::max(minY, other.minY), std::min(maxY, other.maxY), minZ, other.minZ - 1});
    }
    if (maxZ > other.maxZ) {
      splits.push_back({false, std::max(minX, other.minX), std::min(maxX, other.maxX), std::max(minY, other.minY), std::min(maxY, other.maxY), other.maxZ + 1, maxZ});
    }

    return splits;
  }

  uint64_t count() const {
    if (maxX < minX || maxY < minY || maxZ < minZ)
      std::cout << "PROBLEM\n";
    return (maxX - minX + 1) * (maxY - minY + 1) * (maxZ - minZ + 1);
  }

  bool isOutside50() const {
    return minX < -50 || maxX > 50 || minY < -50 || maxY > 50 || minZ < -50 || maxZ > 50;
  }
};

static uint64_t count(std::list<Cube>& rules, bool part1) {
  std::list<Cube> cubes;

  for (Cube& r : rules) {
    if (part1 && r.isOutside50())
      continue;
    std::list<Cube> next;
    for (Cube& c : cubes) {
      if (r.intersect(c)) {
        std::list<Cube> splits = c.split(r);
        for (Cube& split : splits)
          next.push_back(split);
      } else {
        next.push_back(c);
      }
    }
    if (r.on)
      next.push_back(r);
    cubes = next;
  }

  uint64_t count = 0;
  for (Cube& c : cubes)
    count += c.count();
  return count;
}

int main() {
  std::list<Cube> rules;
  std::string on;
  std::int64_t minX, maxX, minY, maxY, minZ, maxZ;
  char dummy;

  while (std::cin >> on >> dummy >> dummy >> minX >> dummy >> dummy >> maxX >> dummy >> dummy >> dummy >> minY >> dummy >> dummy >> maxY >> dummy >> dummy >> dummy >> minZ >> dummy >> dummy >> maxZ) {
    rules.push_back(Cube{on == "on" ? true : false, minX, maxX, minY, maxY, minZ, maxZ});
  }

  std::cout << "Part 1 result = " << count(rules, true) << '\n';
  std::cout << "Part 2 result = " << count(rules, false) << '\n';

  return 0;
}
