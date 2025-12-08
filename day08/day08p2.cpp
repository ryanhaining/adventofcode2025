#include <algorithm>
#include <cassert>
#include <cmath>
#include <format>
#include <iostream>
#include <iterator>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace {
struct Point {
  int x;
  int y;
  int z;
};

using PointSet = std::unordered_set<const Point *>;

std::istream &operator>>(std::istream &in, Point &p) {
  char comma{};
  return in >> p.x >> comma >> p.y >> comma >> p.z;
}

double distance(const Point &p1, const Point &p2) {
  return std::sqrt(std::pow((p1.x - p2.x), 2) + std::pow((p1.y - p2.y), 2) +
                   std::pow((p1.z - p2.z), 2));
}

struct Edge {
  const Point *p1;
  const Point *p2;
  double distance;

  bool operator<(const Edge &other) const {
    // easy, hacky way to get a min heap
    return distance >= other.distance;
  }
};
} // namespace

int main() {
  const std::vector<Point> points{std::istream_iterator<Point>{std::cin},
                                  std::istream_iterator<Point>{}};
  std::vector<Edge> edges;
  edges.reserve(points.size() * points.size());
  for (const Point &p1 : points) {
    for (const Point &p2 : points) {
      if (&p1 >= &p2) {
        continue;
      }
      edges.emplace_back(&p1, &p2, distance(p1, p2));
    }
  }
  std::unordered_map<const Point *, std::shared_ptr<PointSet>> point_groups;
  for (const auto &p : points) {
    point_groups.emplace(&p, std::make_shared<PointSet>());
    point_groups[&p]->insert(&p);
  }

  std::make_heap(edges.begin(), edges.end());
  while (true) {
    auto e = edges.front();
    std::pop_heap(edges.begin(), edges.end());
    edges.pop_back();
    auto g1 = point_groups[e.p1];
    auto g2 = point_groups[e.p2];
    assert(!g1->empty());
    assert(!g2->empty());
    if (g1 != g2) {
      g2->insert(g1->begin(), g1->end());
      for (auto *p : *g1) {
        point_groups[p] = g2;
      }
      g1->clear();
    }
    if (g2->size() == points.size()) {
      std::cout << long{e.p1->x} * long{e.p2->x} << '\n';
      break;
    }
  }
}
