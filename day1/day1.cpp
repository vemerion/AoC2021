#include <iostream>
#include <list>

static int16_t sliding_window(std::list<int16_t>& depths, int16_t depth) {
  depths.push_back(depth);
  if (depths.size() == 5)
    depths.pop_front();
  if (depths.size() == 4)
    return depths.back() - depths.front();
  return 0;
}

int main() {
  int16_t depth, depth0;
  uint16_t part1, part2;
  std::list<int16_t> depths;
  
  depth = depth0 = -1;
  part1 = part2 = 0;

  while (std::cin >> depth) {
    if (depth0 != -1 && depth > depth0)
      part1++;
    depth0 = depth;

    if (sliding_window(depths, depth) > 0)
      part2++;
  }

  std::cout << "Part 1 result = " << part1 << '\n';
  std::cout << "Part 2 result = " << part2;
  return 0;
}
