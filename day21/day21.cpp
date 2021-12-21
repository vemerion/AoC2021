#include <iostream>
#include <tuple>
#include <map>
#include <array>

struct State {
  uint8_t pos;
  uint8_t score;
  uint8_t opponentPos;
  uint8_t opponentScore;
  bool yourTurn;

  bool operator<(const State& other) const {
    return std::make_tuple(pos, score, opponentPos, opponentScore, yourTurn) < std::make_tuple(other.pos, other.score, other.opponentPos, other.opponentScore, other.yourTurn);
  }

  uint8_t getScore() const {
    return yourTurn ? score : opponentScore;
  }

  uint8_t getPos() const {
    return yourTurn ? pos : opponentPos;
  }

  State play(uint8_t roll) const {
    uint8_t newPos = getPos() + roll;
    if (newPos > 10)
      newPos -= 10;
    uint8_t newScore = getScore() + newPos;
    if (yourTurn)
      return {newPos, newScore, opponentPos, opponentScore, !yourTurn};
    else
      return {pos, score, newPos, newScore, !yourTurn};
  }
};

using States = std::map<State, uint64_t>;

struct Player {
  uint8_t pos;
  uint16_t score = 0;

  void play(uint8_t roll) {
    pos += roll;
    pos %= 10;
  }
};

static uint32_t part1(uint8_t p1, uint8_t p2) {
  uint32_t rolls;
  uint8_t die;
  std::array<Player, 2> players;

  players[0].pos = p1 - 1;
  players[1].pos = p2 - 1;
  die = rolls = 0;

  while (true) {
    for (Player& p : players) {
      for (uint8_t i = 0; i < 3; i++) {
        p.play(++die);
        die %= 100;
      }
      p.score += p.pos + 1;
      rolls += 3;
      if (p.score >= 1000)
        return std::min(players[0].score, players[1].score) * rolls;
    }
  }

  return 0;
}

static constexpr std::array<uint8_t, 10> dirac = { 0, 0, 0, 1, 3, 6, 7, 6, 3, 1 };

static uint64_t winningCount(States& states, const State state) {
  if (state.score >= 21)
    return 1;
  else if (state.opponentScore >= 21)
    return 0;

  if (states.count(state))
    return states[state];
  else {
    uint64_t count = 0;
    for (uint8_t i = 3; i < dirac.size(); i++)
      count += dirac[i] * winningCount(states, state.play(i));
    states[state] = count;
    return count;
  }

  return 0;
}

static uint64_t part2(uint8_t p1, uint8_t p2) {
  States states1, states2;

  uint64_t winning1 = winningCount(states1, {p1, 0, p2, 0, true});
  uint64_t winning2 = winningCount(states2, {p2, 0, p1, 0, false});

  return std::max(winning1, winning2);
}

int main() {
  std::cout << "Part 1 result = " << part1(7, 3) << '\n';
  std::cout << "Part 2 result = " << part2(7, 3) << '\n';
  return 0;
}
