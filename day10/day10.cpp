#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

static uint16_t getSyntaxErrorScore(char c) {
  switch (c) {
    case ')':
      return 3;
    case ']':
      return 57;
    case '}':
      return 1197;
    case '>':
      return 25137;
  }
  return 0;
}

static uint16_t getAutocompleteScore(char c) {
  switch (c) {
    case '(':
      return 1;
    case '[':
      return 2;
    case '{':
      return 3;
    case '<':
      return 4;
  }
  return 0;
}

int main() {
  std::list<char> stack;
  std::vector<uint64_t> autocompleteScores;
  uint32_t syntaxErrorScore;
  std::string line;
  bool corrupted;

  syntaxErrorScore = 0;

  while (std::cin >> line) {
    corrupted = false;
    for (char c : line) {
      uint16_t score = getSyntaxErrorScore(c);
      if (score == 0) {
        stack.push_front(c);
      } else {
        char start = stack.front();
        stack.pop_front();
        if (start + 1 != c && start + 2 != c) {
          syntaxErrorScore += score;
          corrupted = true;
          break;
        }
      }
    }
    
    if (!corrupted) {
      uint64_t score = 0;
      while (!stack.empty()) {
        char c = stack.front();
        stack.pop_front();
        score = score * 5 + getAutocompleteScore(c);
      }
      autocompleteScores.push_back(score);
    }
    stack.clear();
  }

  std::sort(autocompleteScores.begin(), autocompleteScores.end());

  std::cout << "Part 1 result = " << syntaxErrorScore << '\n';
  std::cout << "Part 2 result = " << autocompleteScores[autocompleteScores.size() / 2] << '\n';
  return 0;
}
