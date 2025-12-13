#include <iostream>
#include <limits>
#include <sstream>
#include <unordered_map>
#include <vector>

namespace {
constexpr std::string START = "svr";
constexpr std::string GOAL = "out";
constexpr std::string FFT = "fft";
constexpr std::string DAC = "dac";
struct Node {
  std::vector<std::string> outgoing;
};

struct State {
  std::string label{};
  bool visited_dac{};
  bool visited_fft{};
  bool operator==(const State&) const = default;
  bool operator!=(const State&) const = default;
};

struct StateHash {
  std::size_t operator()(const State& state) const {
    return std::hash<std::string>{}(state.label) ^ (state.visited_dac << 1) ^
           state.visited_fft;
  }
};

long find_paths_impl(std::unordered_map<std::string, Node>& nodes,
    std::unordered_map<State, long, StateHash>& cache, const State& state) {
  auto& current = nodes[state.label];
  if (state.label == GOAL) {
    return state.visited_dac && state.visited_fft ? 1 : 0;
  }
  if (auto it = cache.find(state); it != cache.end()) {
    return it->second;
  }
  long paths_count{};
  for (const auto& next : current.outgoing) {
    paths_count += find_paths_impl(nodes, cache,
        State{next, state.visited_dac || next == DAC,
            state.visited_fft || next == FFT});
  }
  cache[state] = paths_count;
  return paths_count;
}

long find_paths(std::unordered_map<std::string, Node>& nodes) {
  std::unordered_map<State, long, StateHash> cache;
  return find_paths_impl(nodes, cache, State{START, false, false});
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
