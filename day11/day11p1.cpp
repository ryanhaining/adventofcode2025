#include <iostream>
#include <limits>
#include <sstream>
#include <unordered_map>
#include <vector>

namespace {
constexpr std::string START = "you";
constexpr std::string GOAL = "out";
struct Node {
  std::vector<std::string> outgoing;
  std::optional<long> paths_to_out;
};

long find_paths_impl(std::unordered_map<std::string, Node>& nodes,
    const std::string& current_label) {
  auto& current = nodes[current_label];
  if (current_label == GOAL) {
    return 1;
  }
  if (current.paths_to_out) {
    return *current.paths_to_out;
  }
  current.paths_to_out.emplace(0);
  for (const auto& next : current.outgoing) {
    *current.paths_to_out += find_paths_impl(nodes, next);
  }
  return *current.paths_to_out;
}

long find_paths(std::unordered_map<std::string, Node>& nodes) {
  return find_paths_impl(nodes, START);
}

std::unordered_map<std::string, Node> read_input() {
  std::unordered_map<std::string, Node> nodes;
  std::string line{};
  while (std::getline(std::cin, line)) {
    std::istringstream in{line};
    std::string label{};
    in >> label;
    label.pop_back();  // drop the ':'
    auto& node = nodes[label];
    while (in >> label) {
      node.outgoing.push_back(label);
    }
  }
  return nodes;
}

}

int main() {
  auto nodes = read_input();
  auto result = find_paths(nodes);
  std::cout << result << '\n';
}
