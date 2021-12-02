#include <iostream>

int main() {
  int64_t x, y1, y2, value, aim;
  std::string direction;

  x = y1 = y2 = aim = 0;

  while (std::cin >> direction >> value) {
    if (direction == "forward") {
      x += value;
      y2 += aim * value;
    } else if (direction == "up") {
      y1 -= value;
      aim -= value;
    } else if (direction == "down") {
      y1 += value;
      aim += value;
    }
  }

  std::cout << "Part 1 result = " << x * y1 << '\n';
  std::cout << "Part 2 result = " << x * y2 << '\n';
  return 0;
}
