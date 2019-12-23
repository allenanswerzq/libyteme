#include "base.h"
#include "graph.h"
#include "tarjan_scc.h"

namespace {

TEST(Graph, TestGraph) {
  Graph<int> g(4);
  g.add(0, 1);
  g.add(0, 2);
  g.add(1, 2);
  g.add(0, 3);
  EXPECT_EQ(g.n, 4);
  EXPECT_EQ(g.m, 4);
  vector<pair<int, int>> e;
  for (auto v : g.get_edges(0)) {
    e.emplace_back(0, v->to->id);
  }
  sort(e.begin(), e.end());
  vector<pair<int, int>> r = {{0, 1}, {0, 2}, {0, 3}};
  EXPECT_EQ(e, r);
}

TEST(TarjanScc, TestSCC) {
  Graph<int> g(4);
  g.add(0, 1);
  g.add(1, 5);
  g.add(1, 4);
  g.add(4, 0);
  a.add(1, 2);
  g.add(2, 6);
  g.add(5, 6);
  g.add(6, 5);
  g.add(2, 3);
  g.add(3, 2);
  g.add(3, 7);
  g.add(7, 7);
  auto tarjan = TarjanScc<int> (&g)
  scc = tarjan.compute_scc();
  for (int i = 0; i < g.n; i++) {
    cout << scc[i] << '\n';
  }
}

}  // namespace

