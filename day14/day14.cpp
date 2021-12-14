#include <iostream>
#include <map>
#include <algorithm>
#include <limits>

static void add(std::map<std::string, uint64_t>& counts, std::string key, uint64_t value) {
  value += counts.count(key) == 0 ? 0 : counts[key];
  counts[key] = value;
}

static uint64_t process(std::string& sequence, std::map<std::string, std::string>& rules, uint8_t steps) {
  std::map<std::string, uint64_t> counts;

  for (auto& rule : rules)
    counts.insert(std::make_pair(rule.first, 0));

  for (uint8_t i = 0; i < sequence.size() - 1; i++)
    counts[sequence.substr(i, 2)]++;

  for (uint8_t i = 0; i < steps; i++) {
    std::map<std::string, uint64_t> step;
    for (auto& pair : counts) {
      std::string middle = rules[pair.first];
      add(step, pair.first[0] + middle, pair.second);
      add(step, middle + pair.first[1], pair.second);
    }
    counts = step;
  }

  uint64_t min, max;

  max = 0;
  min = std::numeric_limits<uint64_t>::max();

  for (char c = 'A'; c <= 'Z'; c++) {
    uint64_t count = 0;
    for (auto& pair : counts)
        if (pair.first[0] == c)
          count += pair.second;
    if (c == sequence[sequence.size() - 1])
      count++;
    if (count != 0) {
      if (count < min)
        min = count;
      if (count > max)
        max = count;
    }
  }
  return max - min;
}

int main() {
  std::string sequence, pair, dummy, insertion;
  std::map<std::string, std::string> rules;

  std::cin >> sequence;
  while (std::cin >> pair >> dummy >> insertion)
    rules.insert(std::make_pair(pair, insertion));

  std::cout << "Part 1 result = " << process(sequence, rules, 10) << '\n';
  std::cout << "Part 2 result = " << process(sequence, rules, 40) << '\n';
                                                              
  return 0;
}
