#include <iostream>
#include <array>
#include <algorithm>

static uint64_t simulate(std::array<uint64_t, 9> fishes, uint16_t days) {
  uint64_t restart = 0;
  for (uint16_t i = 0; i < days; i++) {
    restart = fishes[0];
    for (uint8_t j = 1; j < fishes.size(); j++) {
      fishes[j - 1] = fishes[j];
    }
    fishes[8] = restart;
    fishes[6] += restart;
  }

  uint64_t sum = 0;
  std::for_each(fishes.begin(), fishes.end(), [&sum](uint64_t n) { sum += n; });

  return sum;
}

int main() {
  std::array<uint64_t, 9> fishes = { 0 };
  uint64_t n;

  while (std::cin >> n) {
    std::cin.ignore(1);
    fishes[n]++;
  }

  std::cout << "Part 1 result = " << simulate(fishes, 80) << '\n';
  std::cout << "Part 2 result = " << simulate(fishes, 256) << '\n';

  return 0;
}
