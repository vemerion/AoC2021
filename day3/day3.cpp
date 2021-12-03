#include <iostream>
#include <array>
#include <vector>
#include <limits>

static constexpr uint8_t DIGITS = 12;

static uint32_t gammaMulEpsilon(std::array<uint16_t, DIGITS>& onesCount, uint16_t numberCount) {
  uint32_t gamma = 0;

  for (uint16_t i = 0; i < onesCount.size(); i++)
    if (onesCount[i] > numberCount / 2)
      gamma |= 1 << (DIGITS - i - 1);

  uint8_t shift = std::numeric_limits<uint32_t>::digits - DIGITS;
  return gamma * (~gamma << shift >> shift);
}

static uint16_t filter(std::vector<std::string> numbers, bool oxygen) {
  for (uint8_t i = 0; i < DIGITS; i++) {
    uint16_t oneCount = 0;
    for (std::string& n : numbers)
      if (n[i] == '1')
        oneCount++;

    uint16_t zeroCount = numbers.size() - oneCount;
    char valid;
    if (oxygen) {
      valid = oneCount >= zeroCount ? '1' : '0';
    } else {
      valid = zeroCount <= oneCount ? '0' : '1';
    }

    for (auto it = numbers.begin(); it != numbers.end(); it++)
      if ((*it)[i] != valid)
        numbers.erase(it--);

    if (numbers.size() == 1)
      return std::stoi(numbers[0], nullptr, 2);
  }
  return 0;
}

int main() {
  std::string number;
  std::array<uint16_t, DIGITS> onesCount = { 0 };
  std::vector<std::string> numbers;

  while (std::cin >> number) {
    for (uint8_t i = 0; i < number.size(); i++)
      if (number[i] == '1')
        onesCount[i]++;
    numbers.push_back(number);
  }

  std::cout << "Part 1 result = " << gammaMulEpsilon(onesCount, numbers.size()) << '\n';
  std::cout << "Part 2 result = " << filter(numbers, true) * filter(numbers, false) << '\n';

  return 0;
}
