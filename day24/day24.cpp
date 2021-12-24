#include <iostream>
#include <array>

static constexpr uint8_t VAR_COUNT = 14;

using Constants = std::array<int8_t, VAR_COUNT>;

// Equations derived by hand
static int64_t solve(const Constants& cs, const Constants& ds, bool part1) {
  std::array<std::pair<int8_t, int8_t>, VAR_COUNT / 2> equations = { std::make_pair(0, 13), std::make_pair(1, 12), std::make_pair(10, 11), std::make_pair(8, 9), std::make_pair(2, 7), std::make_pair(5, 6), std::make_pair(3, 4) };
  std::array<int8_t, VAR_COUNT> vars = { 0 };

  for (auto& e : equations) {
    for (int8_t i = part1 ? 9 : 1; i > 0 && 1 < 10; i += part1 ? -1 : 1) {
      int8_t constant = ds[e.first] + cs[e.second];
      if (i + constant > 0 && i + constant < 10) {
        vars[e.first] = i;
        vars[e.second] = i + constant;
        break;
      }
    }
  }

  int64_t result = 0;
  for (auto& v : vars)
    result = result * 10 + v;
  return result;
}

int main() {
  Constants cs = { 10, 15, 14, 15, -8, 10, -16, -4, 11, -3, 12, -7, -15, -7 };
  Constants ds = { 2, 16, 9, 0, 1, 12, 6, 6, 3, 5, 9, 3, 2, 3 };

  std::cout << "Part 1 result = " << solve(cs, ds, true) << '\n';
  std::cout << "Part 2 result = " << solve(cs, ds, false) << '\n';
  return 0;
}
