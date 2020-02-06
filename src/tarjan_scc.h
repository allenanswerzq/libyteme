#include "base.h"

struct NodeScc {
  int id;
  int index = -1;
  int lowlink = 1 << 30;
  bool onstack = false;
  NodeScc(int id_) : id(id_) {}
};

template <class T>
using GraphScc = GraphNode<NodeScc, T>;

// Compute strongly connected components.
template <class T>
struct TarjanScc {
  int index = 0;
  GraphScc<T>* g = nullptr;  // not owned

  // For each node, will assign a scc group id to it.
  vector<int> scc;
  int scc_cnt = 0;
  stack<NodeScc*> stk;

  explicit TarjanScc(GraphScc<T>* g_) : g(g_) { scc.resize(g->n, -1); }

  vector<int> compute_scc() {
    index = 0;
    for (auto node : g->nodes) {
      assert(node);
      assert(0 <= node->id && node->id < g->n);
      if (scc[node->id] == -1) {
        strongconnect(node);
      }
    }
    return scc;
  }

  void strongconnect(NodeScc* v) {
    assert(v);
    v->index = index;
    v->lowlink = index;
    index += 1;
    stk.push(v);
    v->onstack = true;

    for (auto w : g->get_edges(v->id)) {
      if (w->to->index == -1) {
        strongconnect(w->to);
        v->lowlink = min(v->lowlink, w->to->lowlink);
      }
      else if (w->to->onstack) {
        v->lowlink = min(v->lowlink, w->to->index);
      }
      else {
        // Do nothing.
      }
    }

    // If v is a root node, pop the stack and generate a SCC.
    if (v->lowlink == v->index) {
      NodeScc* w;
      do {
        w = stk.top();
        stk.pop();
        scc[w->id] = scc_cnt;
        w->onstack = false;
      } while (w->id != v->id);
      scc_cnt++;
    }
  }
};
