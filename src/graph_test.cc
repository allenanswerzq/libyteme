#include "graph.h"
#include "shortest_path.h"
#include "gtest/gtest.h"

namespace {

TEST(GraphStar, IteratorTest) {
  GraphStar<int, 20> ga;
  ga.add(0, 1);
  ga.add(0, 2);
  ga.add(1, 2);
  ga.add(0, 3);
  vector<pair<int, int>> e;
  for (auto v : ga.edges(0)) {
    e.emplace_back(0, v->to);
  }
  sort(e.begin(), e.end());
  vector<pair<int, int>> r = {{0, 1}, {0, 2}, {0, 3}};
  EXPECT_EQ(e, r);
}

TEST(GraphAdj, Dijkstra) {
  GraphAdj<int> ga(4);
  ga.add(0, 1);
  ga.add(0, 2);
  ga.add(1, 2);
  ga.add(0, 3);
  EXPECT_EQ(ga.n, 4);
  EXPECT_EQ(ga.m, 4);
  vector<pair<int, int>> e;
  for (auto v : ga.edges(0)) {
    e.emplace_back(0, v->to);
  }
  sort(e.begin(), e.end());
  vector<pair<int, int>> r = {{0, 1}, {0, 2}, {0, 3}};
  EXPECT_EQ(e, r);
  vector<int> right = {0, 1, 1, 1};
  vector<int> dist = dijkstra<int, int(1e9)>(ga, 0);
  EXPECT_EQ(dist, right);
}

}  // namespace
