#include <iostream>
#include <map>
#include <list>
#include <algorithm>

using Cave = std::list<std::string>;

class Path : public std::list<std::string> {
  public:
    bool visitedTwice = false;
};

uint32_t countPaths(std::map<std::string, Cave>& caves, bool part2) {
  uint32_t count = 0;

  std::list<Path> paths;
  Path start;
  start.push_back("start");
  paths.push_back(start);

  while (!paths.empty()) {
    auto path = paths.front();
    paths.pop_front();
    if (path.back() == "end") {
      count++;
      continue;
    }

    Cave& cave = caves[path.back()];
    for (std::string& connection : cave) {
      auto caveCount = std::count(path.begin(), path.end(), connection);
      bool visitTwice = false;
      if (connection != "start" && (isupper(connection[0]) || caveCount == 0 || (visitTwice = (caveCount == 1 && part2 && !path.visitedTwice)))) {
        auto newPath = path;
        newPath.push_back(connection);
        if (visitTwice)
          newPath.visitedTwice = true;
        paths.push_back(newPath);
      }
    }
  }

  return count;
}

int main() {
  std::map<std::string, Cave> caves;
  std::string line;

  while (std::cin >> line) {
    auto split = line.find('-');
    std::string from = line.substr(0, split);
    std::string to = line.substr(split + 1, line.size());
    if (!caves.count(from))
      caves.insert(std::make_pair(from, Cave{}));
    if (!caves.count(to))
      caves.insert(std::make_pair(to, Cave{}));
    caves[from].push_back(to);
    caves[to].push_back(from);
  }
  
  std::cout << "Part 1 result = " << countPaths(caves, false) << '\n';
  std::cout << "Part 2 result = " << countPaths(caves, true) << '\n';
  return 0;
}
