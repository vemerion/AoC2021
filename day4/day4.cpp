#include <iostream>
#include <vector>
#include "day4.hpp"

Board Board::parse() {
  Board b;
  uint16_t n;

  for (uint8_t i = 0; i < LENGTH; i++)
    for (uint8_t j = 0; j < LENGTH; j++) {
      std::cin >> n;
      b.board[i][j].value = n;
    }

  return b;
}

void Board::mark(uint16_t value) {
  for (uint8_t row = 0; row < board.size(); row++)
    for (uint8_t col = 0; col < board[row].size(); col++)
      if (board[row][col].value == value) {
        board[row][col].marked = true;
        lastMarkedRow = row;
        lastMarkedCol = col;
        return;
      }
}

bool Board::winner() const {
  return score() != 0;
}

uint32_t Board::score() const {
  uint32_t score;
  bool rowDone, colDone;

  score = 0;
  rowDone = colDone = true;

  for (uint8_t i = 0; i < LENGTH; i++) {
    rowDone &= board[lastMarkedRow][i].marked;
    colDone &= board[i][lastMarkedCol].marked;
  }

  if (!rowDone && !colDone)
    return 0;

  for (auto& row : board)
    for (auto& pos : row)
      if (!pos.marked)
        score += pos.value;

  return score * board[lastMarkedRow][lastMarkedCol].value;
}

int main() {
  uint8_t winners;
  uint16_t n;
  uint32_t part1, part2;
  std::vector<uint8_t> numbers;
  std::vector<Board> boards;

  part1 = part2 = 0;
  winners = 0;

  do {
    std::cin >> n;
    numbers.push_back(n);
  } while (std::cin.get() == ',');

  while (!std::cin.eof()) {
    boards.push_back(Board::parse());
  }

  boards.pop_back();
    
  for (uint16_t i : numbers) {
    part2 = 0;
    for (Board& b : boards) {
      if (b.winner())
        continue;
      b.mark(i);
      if (b.winner()) {
        uint32_t score = b.score();
        if (part1 == 0)
          part1 = score;

        winners++;
        if (part2 == 0 || part2 > score)
          part2 = score;
        if (winners == boards.size())
          break;
      }
    }
    if (winners == boards.size())
      break;
  }

  std::cout << "Part 1 result = " << part1 << '\n';
  std::cout << "Part 2 result = " << part2 << '\n';
  return 0;
}
