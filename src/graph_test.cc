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
  GraphScc<int> g(8);
  g.add(0, 1);
  g.add(1, 5);
  g.add(1, 4);
  g.add(4, 0);
  g.add(4, 5);
  g.add(1, 2);
  g.add(2, 6);
  g.add(5, 6);
  g.add(6, 5);
  g.add(2, 3);
  g.add(3, 2);
  g.add(3, 7);
  g.add(6, 7);
  g.add(7, 7);
  EXPECT_EQ(g.m, 14);
  auto tarjan = TarjanScc<int> (&g);
  vector<int> scc = tarjan.compute_scc();
  vector<vector<int>> gp(tarjan.scc_cnt);
  for (int i = 0; i < g.n; i++) {
    gp[scc[i]].push_back(i);
  }
  for (int i = 0; i < tarjan.scc_cnt; i++) {
    sort(gp[i].begin(), gp[i].end());
  }
  vector<vector<int>> right = {
    {7},
    {5, 6},
    {2, 3},
    {0, 1, 4}
  };
  EXPECT_EQ(gp, right);
}

}  // namespace

