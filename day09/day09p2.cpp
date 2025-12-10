#include <algorithm>
#include <cassert>
#include <cstddef>
#include <format>
#include <iostream>
#include <iterator>
#include <queue>
#include <ranges>
#include <unordered_map>
#include <vector>

namespace {
struct Point {
  long row;
  long col;
};

struct Range {
  // inclusive start and stop
  long start;
  long stop;

  bool contains(long n) const {
    return start <= n && n <= stop;
  }
};

struct EdgeMaps {
  // key is row, range is columns
  std::unordered_map<long, std::vector<Range>> horizontal_edges;
  // key is column, Range is rows
  std::unordered_map<long, std::vector<Range>> vertical_edges;
  void add(const Point& p1, const Point& p2) {
    if (p1.row == p2.row) {
      horizontal_edges[p1.row].emplace_back(
          std::min(p1.col, p2.col), std::max(p1.col, p2.col));
    } else {
      assert(p1.col == p2.col);
      vertical_edges[p1.col].emplace_back(
          std::min(p1.row, p2.row), std::max(p1.row, p2.row));
    }
  }
};

std::istream& operator>>(std::istream& in, Point& p) {
  char comma{};
  return in >> p.row >> comma >> p.col;
}

EdgeMaps create_edges(const std::vector<Point>& points) {
  EdgeMaps edge_maps;
  for (auto it = points.begin(); it != points.end() - 1; ++it) {
    edge_maps.add(*it, *(it + 1));
  }
  edge_maps.add(points.back(), points.front());
  return edge_maps;
}

long area(const Point& p1, const Point& p2) {
  return (std::abs(p1.row - p2.row) + 1) * (std::abs(p1.col - p2.col) + 1);
}

bool is_valid(const Point& p1, const Point& p2, const EdgeMaps& edge_maps) {
  for (auto row = std::min(p1.row + 1, p2.row + 1);
       row <= std::max(p1.row - 1, p2.row - 1); ++row) {
    const auto& edges_on_row = edge_maps.horizontal_edges.find(row);
    if (edges_on_row != edge_maps.horizontal_edges.end() &&
        std::any_of(edges_on_row->second.begin(), edges_on_row->second.end(),
            [&p1, &p2](const Range& range) {
              return range.contains(std::min(p1.col, p2.col) + 1) ||
                     range.contains(std::max(p1.col, p2.col) - 1);
            })) {
      return false;
    }
  }
  for (auto col = std::min(p1.col + 1, p2.col + 1);
       col <= std::max(p1.col - 1, p2.col - 1); ++col) {
    const auto& edges_on_col = edge_maps.vertical_edges.find(col);
    if (edges_on_col != edge_maps.vertical_edges.end() &&
        std::any_of(edges_on_col->second.begin(), edges_on_col->second.end(),
            [&p1, &p2](const Range& range) {
              return range.contains(std::min(p1.row, p2.row) + 1) ||
                     range.contains(std::max(p1.row, p2.row) - 1);
            })) {
      return false;
    }
  }
  return true;
}

}

int main() {
  const std::vector<Point> points{
      std::istream_iterator<Point>{std::cin}, std::istream_iterator<Point>{}};
  const auto edge_maps = create_edges(points);
  for (auto [k, v] : edge_maps.horizontal_edges) {
    assert(!v.empty());
  }
  for (auto [k, v] : edge_maps.vertical_edges) {
    assert(!v.empty());
  }
  long max_area{};
  for (const auto& p1 : points) {
    for (const auto& p2 : points) {
      if (&p1 >= &p2) {  // skip double checking
        continue;
      }
      auto current_area = area(p1, p2);
      if (current_area > max_area && is_valid(p1, p2, edge_maps)) {
        max_area = current_area;
      }
    }
  }
  std::cout << max_area << '\n';
}
