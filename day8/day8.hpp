#include <array>
#include <string>
#include <functional>

#ifndef DAY8
#define DAY8

class Display {
  public:
    static Display parse();
    uint8_t count1478() const;
    void sortDigits();
    uint16_t calculateOutput() const;
  private:
    void swap(uint8_t i, uint8_t j);
    void findAndSwap(uint8_t index, uint8_t size, std::function<bool(uint8_t)> pred);
    bool contains(const std::string& a, const std::string& b) const;
    uint16_t findDigitValue(const std::string& a) const;
    std::array<std::string, 10> digits;
    std::array<std::string, 4> output;
};

#endif
