#include <iostream>
#include <set>

using Pos = std::pair<uint16_t, uint16_t>;
using Dots = std::set<Pos>;

static void printDots(Dots& dots) {
  uint16_t maxX, maxY;

  maxX = maxY = 0;

  for (auto& dot : dots) {
    if (dot.first > maxX)
      maxX = dot.first;
    if (dot.second > maxY)
      maxY = dot.second;
  }

  for (uint16_t y = 0; y <= maxY; y++) {
    for (uint16_t x = 0; x <= maxX; x++)
      if (dots.count(std::make_pair(x, y)))
        std::cout << "#";
      else
        std::cout << " ";
    std::cout << "\n";
  }
}

int main() {
  Dots dots;
  uint16_t value, part1;
  std::string line;
  char direction;

  part1 = 0;

  while (getline(std::cin, line)) {
    size_t split = line.find('=');
    if (split == std::string::npos) {
      split = line.find(',');
      if (split != std::string::npos)
        dots.insert(std::make_pair(stoi(line.substr(0, split)), stoi(line.substr(split + 1, line.size()))));
    } else {
      direction = line[split - 1];
      value = stoi(line.substr(split + 1, line.size()));
      Dots folded;

      for (auto& dot : dots) {
        uint16_t x = direction == 'x' && value < dot.first ? value - (dot.first - value) : dot.first;
        uint16_t y = direction == 'y' && value < dot.second ? value - (dot.second - value) : dot.second;
        folded.insert(std::make_pair(x, y));
      }
      dots = folded;

      if (part1 == 0)
        part1 = dots.size();
    }
  }

  std::cout << "Part 1 result = " << part1 << '\n';
  std::cout << "Part 2 result = \n";
  printDots(dots);
  return 0;
}
