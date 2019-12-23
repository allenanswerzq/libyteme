#include "base.h"

struct NodeBase {
  // A Node should at least has an id.
  int id;
  // Each node may also have other properties,
  // but here only use id to initialize one Node object.
  NodeBase(int id_) : id(id_) {}
};

template <class T>
struct EdgeBase {
  // An Edge should at least have two nodes.
  NodeBase* from;
  NodeBase* to;
  T cost;
  EdgeBase(NodeBase* from_, NodeBase* to_, T cost_ = 1)
    : from(from_), to(to_), cost(cost_) {}
};

template <class N, template <class T> class E, class T>
struct GraphBase {
  // The number of nodes in a graph.
  int n;

  // The number of edges in a graph.
  int m;

  // All the nodes in a graph.
  vector<N*> nodes;

  // All the edges in a graph.
  vector< E<T>* > edges;

  // The place where a Node is indexed.
  vector<int> place;

  // Add an edge into the graph.
  virtual void add(int from, int to, T cost = 1) = 0;

  // Get all edges for a node u.
  virtual vector< E<T>* > get_edges(int u) = 0;

  // Get or create a new Node
  virtual N* get_or_create(int id) = 0;
};

template <class N, template <class T> class E, class T>
struct GraphAdj : public GraphBase<N, E, T> {
  vector<vector< E<T>* >> g;

  GraphAdj(int n_)  {
    this->n = n_;
    this->m = 0;
    this->nodes.resize(n_);
    this->place.resize(n_, -1);
    this->edges.clear();
    g.resize(this->n);
  }

  ~GraphAdj() {
    for (int i = 0; i < this->n; i++) {
      if (this->nodes[i]) {
        delete this->nodes[i];
      }
    }
    for (int i = 0; i < this->m; i++) {
      if (this->edges[i]) {
        delete this->edges[i];
      }
    }
  }

  vector<E<T>*> get_edges(int u) override {
    vector<E<T>*> ret;
    for (auto e : g[u]) {
      ret.push_back(e);
    }
    return ret;
  }

  N* get_or_create(int id) override {
    if (this->place[id] != -1) {
      return this->nodes[this->place[id]];
    }
    N* node = new N(id);
    this->nodes.push_back(node);
    this->place[id] = int(this->nodes.size()) - 1;
    return node;
  }

  void add(int u, int v, T cost = 1) override {
    // Create two ndoes first.
    N* from = get_or_create(u);
    N* to = get_or_create(v);
    E<T>* e = new E<T>(from, to, cost);
    this->edges.push_back(e);
    this->m++;
    g[u].push_back(e);
  }
};

template <class T> using Graph = GraphAdj<NodeBase, EdgeBase, T>;

template <class N, class T> using GraphNode = GraphAdj<N, EdgeBase, T>;

// // Forward star representation of a graph.
// template <class T>
// struct EdgeStar {
//   int to;
//   int next;
//   T cost;
// };

// // M denotes the maximum number of edges this graph might have.
// template <class T, int M>
// struct GraphStar : public GraphBase<T, EdgeStar<T>> {
//   vector<EdgeStar<T>*> g;
//   vector<int> cnt;
//   const int kDefault = -1;

//   GraphStar() {
//    this->m = 0;
//     this->n = 0;
//     g.resize(M);
//     cnt.resize(M, -1);
//   }

//   ~GraphStar() {
//     for (int i = 0; i < this->m; i++) {
//       assert(g[i]);
//       delete g[i];
//     }
//   }

//   vector<EdgeStar<T>*> edges(int u) override {
//     vector<EdgeStar<T>*> ret;
//     for (int x = cnt[u]; x != -1; x = g[x]->next) {
//       ret.push_back(g[x]);
//     }
//     return ret;
//   }

//   void add(int u, int v, T cost = 1) override {
//     g[this->m] = new EdgeStar<T>{kDefault, kDefault, kDefault};
//     g[this->m]->to = v;;
//     g[this->m]->cost = cost;
//     g[this->m]->next = cnt[u];
//     cnt[u] = this->m++;
//   }
// };

// // Left child and right brother representation of a graph.
// template <class T>
// struct EdgeChild {
//   int child;
//   int brother;
//   T cost;
// };

// template <class T>
// struct GraphChild : public GraphBase<T, EdgeChild<T>> {
//   vector<EdgeChild<T>*> g;
//   const int kDefault = -1;

//   GraphChild(int n_) {
//     this->n = n_;
//     this->m = 0;
//     g.resize(this->n, new EdgeChild<T>{kDefault, kDefault, 1});
//   }

//   ~GraphChild() {
//     for (auto e : g) {
//       delete e;
//     }
//   }

//   vector<EdgeChild<T>*> edges(int u) override {
//     vector<EdgeChild<T>*> ret;
//     while (u != kDefault) {
//       ret.push_back(&g[u]);
//       u = g[u].child;
//     }
//     return ret;
//   }

//   void add(int u, int v, T cost = 1) override {
//     this->m++;
//     g[v].brother = g[u].child;
//     g[u].child = v;
//     g[u].cost = cost;
//   }
// };

