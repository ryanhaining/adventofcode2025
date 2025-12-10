#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <unordered_set>
#include <vector>


// Dijkstra's but without knowing the vertexes ahead of time
// Each time you visit a vertex, you add any unvisited possible paths
// from it with the new distance into the heap.
// The heap initially just has the one starting point.
// I start at the goal and work towards 0 instead of the other way around,
// though I don't think that actually matters.

namespace {

struct Node {
  std::uint16_t value;
  long distance;
};

class NodeHeap {
  std::vector<Node> data_;

  static std::size_t parent_index(std::size_t index) {
    return (index - 1) / 2;
  }

  static bool is_lower_distance(const Node& lhs, const Node& rhs) {
    return lhs.distance < rhs.distance;
  }

  struct MinNodeByDistance {
    bool operator()(const Node& lhs, const Node& rhs) const {
      return is_lower_distance(rhs, lhs);
    }
  };

 public:
  Node pop() {
    auto ret = data_[0];
    std::pop_heap(data_.begin(), data_.end(), MinNodeByDistance{});
    data_.pop_back();
    return ret;
  }

  void push(std::uint16_t value, long distance) {
    data_.emplace_back(value, distance);
    std::push_heap(data_.begin(), data_.end(), MinNodeByDistance{});
  }

  void update(std::uint16_t val, long new_distance) {
    auto it = std::find_if(data_.begin(), data_.end(),
        [val](const Node& n) { return n.value == val; });
    if (it == data_.end()) {
      push(val, new_distance);
      return;
    }

    if (new_distance >= it->distance) {
      return;
    }

    std::size_t index = (it - data_.begin());
    while (index > 0 &&
           is_lower_distance(data_[index], data_[parent_index(index)])) {
      std::swap(data_[index], data_[parent_index(index)]);
      index = parent_index(index);
    }
  }
};

struct Machine {
  std::uint16_t goal{};
  std::vector<std::uint16_t> switches;
};

Machine parse_machine(std::string line) {
  Machine machine{};
  std::istringstream in{line};
  in.ignore(1);  // lead '['
  {
    std::string goal_str;
    in >> goal_str;
    goal_str.pop_back();  // trailing ']'

    for (auto it = goal_str.rbegin(); it != goal_str.rend(); ++it) {
      machine.goal <<= 1;
      machine.goal |= (*it) == '#';
    }
  }
  std::string switches_str;
  while (in >> switches_str && switches_str[0] == '(') {
    switches_str.pop_back();
    std::istringstream switches_in{switches_str};
    char c{};
    int num{};
    std::uint16_t switch_n{};
    while (switches_in >> c >> num) {
      switch_n |= (1 << num);
    }
    machine.switches.push_back(switch_n);
  }

  return machine;
}

long find_shortest(Machine machine) {
  NodeHeap heap;
  heap.push(machine.goal, 0);
  std::unordered_set<std::uint16_t> done;
  while (true) {
    auto current = heap.pop();
    if (current.value == 0) {
      return current.distance;
    }
    done.insert(current.value);
    for (auto mask : machine.switches) {
      auto next_val = current.value ^ mask;
      if (!done.contains(next_val)) {
        heap.update(next_val, current.distance + 1);
      }
    }
  }
}

}

int main() {
  std::string line{};
  int total{};
  while (std::getline(std::cin, line)) {
    total += find_shortest(parse_machine(line));
  }
  std::cout << total << '\n';
}
