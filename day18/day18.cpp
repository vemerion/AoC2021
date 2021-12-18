#include <iostream>
#include <vector>
#include <list>

struct Node {
  uint16_t value;
  std::vector<Node> children;

  Node(uint16_t value) {
    this->value = value;
  }

  Node() = default;

  bool isLeaf() {
    return children.empty();
  }

  void print() {
    if (isLeaf())
      std::cout << value;
    else {
      std::cout << '[';
      children[0].print();
      std::cout << ',';
      children[1].print();
      std::cout << ']';
    }
  }

  void gatherLeaves(Node* n, std::vector<Node*>& leaves) {
    if (n->isLeaf() || n == this)
      leaves.push_back(n);
    else
      for (Node& child : n->children)
        gatherLeaves(&child, leaves);
  }

  void doExplode(Node* root) {
    std::vector<Node*> leaves;
    gatherLeaves(root, leaves);

    for (uint16_t i = 0; i < leaves.size(); i++) {
      if (leaves[i] == this) {
        if (i != 0)
          leaves[i - 1]->value += leaves[i]->children[0].value;
        if (i != leaves.size() - 1)
          leaves[i + 1]->value += leaves[i]->children[1].value;
        leaves[i]->children.clear();
        leaves[i]->value = 0;
      }
    }
  }

  bool explode(Node* root, uint8_t depth) {
    if (depth == 4 && !isLeaf()) {
      doExplode(root);
      return true;
    }

    for (auto& child : children)
      if (child.explode(root, depth + 1))
        return true;
    return false;
  }

  bool explode() {
    return explode(this, 0);
  }

  bool split() {
    if (isLeaf()) {
      if (value >= 10) {
        children.emplace_back(value / 2);
        children.emplace_back(value / 2 + (value % 2 == 1));
        return true;
      }
    } else 
      for (Node& child : children)
        if (child.split())
          return true;
    return false;
  }

  uint16_t magnitude() {
    if (isLeaf())
      return value;
    else
      return children[0].magnitude() * 3 + children[1].magnitude() * 2;
  }

  uint16_t reduce() {
    while (true) {
      while (explode())
        ;

      if (!split())
        break;
    }

    return magnitude();
  }
};

static Node parse(std::string line, uint16_t& index) {
  Node node;
  if (line[index] == '[') {
    for (uint8_t i = 0; i < 2; i++) {
      index++;
      node.children.push_back(parse(line, index));
    }
    index++;
  } else {
    node.value = line[index] - '0';
    index++;
  }

  return node;
}

static Node parse(std::string line) {
  uint16_t index = 0;
  return parse(line, index);
}

static Node combine(Node& n1, Node& n2) {
  Node combination;
  combination.children.push_back(n1);
  combination.children.push_back(n2);
  return combination;
}

int main() {
  std::string line;
  std::vector<Node> nodes;
  Node node;
  uint16_t part2;

  part2 = 0;

  while (std::cin >> line)
    nodes.push_back(parse(line));

  node = nodes[0];
  for (uint16_t i = 1; i < nodes.size(); i++) {
    node = combine(node, nodes[i]);
    node.reduce();
  }

  for (uint16_t i = 0; i < nodes.size(); i++) {
    for (uint16_t j = 0; j < nodes.size(); j++) {
      if (i == j)
        continue;
      Node comb = combine(nodes[i], nodes[j]);
      uint16_t magnitude = comb.reduce();
      if (magnitude > part2)
        part2 = magnitude;
    }
  }

  std::cout << "Part 1 result = " << node.reduce() << '\n';
  std::cout << "Part 2 result = " << part2 << '\n';
  return 0;
}
