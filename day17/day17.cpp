#include <iostream>

static int32_t topY(int32_t minY, int32_t maxY) {
  int32_t yVel, top, currentTop, y;

  top = 0;

  for (int32_t i = 0; i < std::abs(minY); i++) {
    y = currentTop = 0;
    yVel = i;
    bool valid = false;
    while (y >= minY) {
      y += yVel--;
      if (y > currentTop)
        currentTop = y;
      if (y >= minY && y <= maxY) {
        valid = true;
        break;
      }
    }
    if (valid)
      top = currentTop;
  }
  return top;
}

static uint32_t hits(int32_t minX, int32_t maxX, int32_t minY, int32_t maxY) {
  uint32_t count;
  int32_t yVel, xVel, x, y;

  count = 0;

  for (int32_t i = 0; i <= maxX; i++) {
    for (int32_t j = -std::abs(minY); j <= std::abs(minY); j++) {
      xVel = i;
      yVel = j;
      x = y = 0;
      while (y >= minY) {
        x += xVel;
        xVel = xVel > 0 ? xVel - 1 : xVel < 0 ? xVel + 1 : 0;
        y += yVel--;
        if (y >= minY && y <= maxY && x >= minX && x <= maxX) {
          count++;
          break;
        }
      }
    }
  }
  return count;
}

int main() {
  int32_t minX, maxX, minY, maxY;

  minX = 48;
  maxX = 70;
  minY = -189;
  maxY = -148;

  std::cout << "Part 1 result = " << topY(minY, maxY) << '\n';
  std::cout << "Part 2 result = " << hits(minX, maxX, minY, maxY) << '\n';
  return 0;
}
