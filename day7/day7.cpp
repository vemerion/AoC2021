#include <iostream>
#include <vector>
#include <limits>

static uint64_t arithmeticSum(uint16_t n) {
  return n * (n + 1) / 2;
}

static uint64_t align(std::vector<uint16_t> crabs, uint16_t min, uint16_t max, bool part2) {
  uint64_t distance, minDistance;

  minDistance = std::numeric_limits<uint32_t>::max();

  for (int16_t i = min; i <= max; i++) {
    distance = 0;
    for (uint16_t crab : crabs)
      distance += part2 ? arithmeticSum(std::abs(i - crab)) : std::abs(i - crab);

    if (distance < minDistance)
      minDistance = distance;
  }

  return minDistance;
}

int main() {
  uint16_t n, min, max;
  std::vector<uint16_t> crabs;

  max = 0;
  min = std::numeric_limits<uint16_t>::max();

  while (std::cin >> n) {
    std::cin.ignore(1);
    crabs.push_back(n);
    
    if (n < min)
      min = n;
    else if (n > max)
      max = n;
  }
  
  std::cout << "Part 1 result = " << align(crabs, min, max, false) << '\n';
  std::cout << "Part 2 result = " << align(crabs, min, max, true) << '\n';
  return 0;
}
