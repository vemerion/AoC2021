#include <iostream>
#include <vector>
#include <set>
#include <limits>

struct Node {
  uint16_t value, row, col;
  Node* prev = nullptr;
  uint16_t dist = std::numeric_limits<uint16_t>::max();
};

using Cave = std::vector<std::vector<uint16_t>>;

static uint16_t getValue(Cave& cave, uint16_t row, uint16_t col) {
  uint16_t size = cave.size();
  uint16_t value = cave[row % size][col % size] + row / size + col / size;
  if (value > 9)
    value -= 9;
  return value;
}

static uint16_t path(Cave& cave, uint8_t tiles) {
  const uint16_t size = cave.size() * tiles;

  std::vector<std::vector<Node>> graph;
  for (uint16_t i = 0; i < size; i++) {
    graph.push_back(std::vector<Node>{});
    for (uint16_t j = 0; j < size; j++)
      graph.back().push_back(Node{getValue(cave, i, j), i, j});
  }


  std::set<Node*> nodes;

  for (uint16_t i = 0; i < size; i++)
    for (uint16_t j = 0; j < size; j++)
      nodes.insert(&graph[i][j]);

  graph[0][0].dist = 0;

  while (!nodes.empty()) {
    uint16_t dist = std::numeric_limits<uint16_t>::max();
    Node* next = nullptr;
    for (auto* n : nodes)
      if (n->dist < dist) {
        dist = n->dist;
        next = n;
      }
    nodes.erase(next);
    if (next == &graph[size - 1][size - 1])
      break;
    
    for (int16_t i = -1; i <= 1; i++)
      for (int16_t j = -1; j <= 1; j++) {
        if ((next->row != 0 || i != -1) && (next->col != 0 || j != -1) && (next->row != size - 1 || i != 1) && (next->col != size - 1 || j != 1) && (std::abs(i + j) == 1)) {
          auto& neighbor = graph[next->row + i][next->col + j];
          uint16_t alt = next->dist + neighbor.value;
          if (alt < neighbor.dist) {
            neighbor.dist = alt;
            neighbor.prev = next;
          }
        }
      }
  }

  return graph[size - 1][size - 1].dist;
}

int main() {
  Cave cave;
  std::string line;

  while (std::cin >> line) {
    cave.push_back(std::vector<uint16_t>{});
    for (char c : line)
      cave.back().push_back(c - '0');
  }

  std::cout << "Part 1 result = " << path(cave, 1) << '\n';
  std::cout << "Part 2 result = " << path(cave, 5) << '\n';
  return 0;
}
