#include <array>

#ifndef DAY4
#define DAY4

static constexpr uint8_t LENGTH = 5;

struct Position {
  bool marked = false;
  uint16_t value = 0;
};

class Board {
  public:
    static Board parse();
    void mark(uint16_t value);
    bool winner() const;
    uint32_t score() const;

  private:
    std::array<std::array<Position, LENGTH>, LENGTH> board;
    int8_t lastMarkedRow = 0, lastMarkedCol = 0;
};

#endif
