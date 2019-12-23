#include "base.h"

template <class T>
struct NodeSCC {
  int id;
  int index = -1;
  int lowlink = 1 << 30;
  NodeSCC(int id_) : id(id_) {}
};

template<class T>
using GraphSCC = GraphNode<NodeSCC, T>;

// Compute strongly connected components.
template<class T>
struct TarjanScc {
  int index = 0;
  GraphSCC<T>* g = nullptr;
  // For each node, will assign a scc group id to it.
  vector<int> scc;
  int scc_cnt = 0;
  stack<NodeScc> stk;

  TarjanScc(const GraphSCC<T>* g_) : g(g_) {
    scc.resize(g.n, -1);
  }

  vector<int> compute_scc() {
    for (auto node : g.nodes) {
      if (scc[node.id] == -1) {
        strongconnect(node);
      }
    }
    return scc;
  }

  void strongconnect(NodeScc v) {
    v.index = index;
    v.lowlink = index;
    index += 1;
    stk.push(v);

    for (auto w : g->edges()) {
      if (w.index = -1) {
        strongconnect(w);
        v.lowlink = min(v.lowlink, w.lowlink);
      }
      else if (scc[i] != -1) {
        v.lowlink = min(v.lowlink, w.index);
      }
    }
    // If v is a root node, pop the stack and generate a SCC.
    if (v.lowlink == v.index) {
      do {
        scc[stk.pop().id] = scc_cnt;
      } while (w.id != v.id);
      ++scc_cnt;
    }
  }
};
