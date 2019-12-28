#include "base.h"

struct NodeBase {
  // A Node should at least has an id.
  int id;
  // Each node may also have other properties,
  // but here only use id to initialize one Node object.
  NodeBase(int id_) : id(id_) {}
};

template <class N, class T>
struct EdgeBase {
  // An Edge should at least have two nodes.
  N* from;
  N* to;
  T cost;
  EdgeBase(N* from_, N* to_, T cost_ = 1)
    : from(from_), to(to_), cost(cost_) {}
};

template <class N, template <class X, class Y> class E, class T>
struct GraphBase {
  // The number of nodes in a graph.
  int n;

  // The number of edges in a graph.
  int m;

  // All the nodes in a graph.
  vector<N*> nodes;

  // All the edges in a graph.
  vector< E<N, T>* > edges;

  // The place where a Node is indexed.
  vector<int> place;

  // Add an edge into the graph.
  virtual void add(int from, int to, T cost = 1) = 0;

  // Get all edges for a node u.
  virtual vector< E<N, T>* > get_edges(int u) = 0;

  // Get or create a new Node
  virtual N* get_or_create(int id) = 0;
};

template <class N, template <class X, class Y> class E, class T>
struct GraphAdj : public GraphBase<N, E, T> {
  vector< vector< E<N, T>* >> g;

  GraphAdj(int n_)  {
    this->n = n_;
    this->m = 0;
    this->place.resize(n_, -1);
    this->nodes.clear();
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

  vector< E<N, T>* > get_edges(int u) override {
    assert(0 <= u && u < this->n);
    return g[u];
  }

  N* get_or_create(int id) override {
    assert(0 <= id && id < this->n);
    if (this->place[id] != -1) {
      return this->nodes[this->place[id]];
    }
    N* node = new N(id);
    this->nodes.push_back(node);
    this->place[id] = int(this->nodes.size()) - 1;
    return node;
  }

  void add(int u, int v, T cost = 1) override {
    N* from = get_or_create(u);
    N* to = get_or_create(v);
    E<N, T>* e = new E<N, T> (from, to, cost);
    this->edges.push_back(e);
    this->m++;
    g[u].push_back(e);
  }
};

template <class T>
using Graph = GraphAdj<NodeBase, EdgeBase, T>;

template <class N, class T>
using GraphNode = GraphAdj<N, EdgeBase, T>;
