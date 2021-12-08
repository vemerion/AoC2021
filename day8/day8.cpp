#include <iostream>
#include <vector>
#include "day8.hpp"

Display Display::parse() {
  Display display;
  std::string digit;

  for (uint8_t i = 0; i < display.digits.size(); i++) {
    std::cin >> digit;
    display.digits[i] = digit;
  }
  std::cin.ignore(2);

  for (uint8_t i = 0; i < display.output.size(); i++) {
    std::cin >> digit;
    display.output[i] = digit;
  }
  return display;
}

uint8_t Display::count1478() const {
  uint8_t count = 0;

  for (const std::string& n : output) {
    uint8_t length = n.length();
    if (length != 5 && length != 6)
      count++;
  }
  return count;
}
void Display::findAndSwap(uint8_t index, uint8_t size, std::function<bool(uint8_t)> pred) {
  for (uint8_t i = 0; i < digits.size(); i++)
    if (digits[i].size() == size && pred(i)) {
      swap(i, index);
      return;
    }
}

void Display::sortDigits() {
  findAndSwap(1, 2, []([[maybe_unused]] uint8_t i) { return true; });
  findAndSwap(4, 4, []([[maybe_unused]] uint8_t i) { return true; });
  findAndSwap(7, 3, []([[maybe_unused]] uint8_t i) { return true; });
  findAndSwap(8, 7, []([[maybe_unused]] uint8_t i) { return true; });
  findAndSwap(9, 6, [this](uint8_t i) { return contains(digits[i], digits[4]); });
  findAndSwap(0, 6, [this](uint8_t i) { return contains(digits[i], digits[1]); });
  findAndSwap(6, 6, [this](uint8_t i) { return !contains(digits[i], digits[1]); });
  findAndSwap(3, 5, [this](uint8_t i) { return contains(digits[i], digits[1]); });
  findAndSwap(5, 5, [this](uint8_t i) { return i != 3 && contains(digits[6], digits[i]); });
}

void Display::swap(uint8_t i, uint8_t j) {
  std::string temp = digits[i];
  digits[i] = digits[j];
  digits[j] = temp;
}

bool Display::contains(const std::string& a, const std::string& b) const{
  for (char c : b)
    if (a.find(c) == std::string::npos)
      return false;

  return true;
}

uint16_t Display::calculateOutput() const {
  uint16_t value = 0;
  for (uint8_t i = 0; i < output.size(); i++)
    value = value * 10 + findDigitValue(output[i]);
  return value;
}

uint16_t Display::findDigitValue(const std::string& a) const {
  for (uint8_t i = 0; i < digits.size(); i++)
    if (a.size() == digits[i].size() && contains(a, digits[i]))
      return i;

  std::cout << "Something has gone terribly wrong!";
  return 10;
}

int main() {
  std::vector<Display> displays;
  uint16_t part1;
  uint32_t part2;

  part1 = 0;
  part2 = 0;

  while (!std::cin.eof()) {
    displays.push_back(Display::parse());
  }

  displays.pop_back();

  for (Display& d : displays) {
    part1 += d.count1478();

    d.sortDigits();
    part2 += d.calculateOutput();
  }

  std::cout << "Part 1 result = " << part1 << '\n';
  std::cout << "Part 2 result = " << part2 << '\n';

  return 0;
}
