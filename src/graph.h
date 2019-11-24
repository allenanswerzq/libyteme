#include <bits/stdc++.h>
using namespace std;

template <class T, class E>
struct Graph {
  // The number of nodes in a graph.
  int n;

  // The number of edges in a graph.
  int m;

  // Add an edge into the graph.
  virtual void add(int from, int to, T cost = 1) = 0;

  // Get all edges for a node u.
  virtual vector<E*> edges(int u) = 0;
};

// Adjacent list representation of a graph.
template <class T>
struct EdgeAdj {
  int to;
  T cost;
};

template <class T>
struct GraphAdj : public Graph<T, EdgeAdj<T>> {
  vector<vector<EdgeAdj<T>*>> g;

  GraphAdj(int n_)  {
    this->n = n_;
    this->m = 0;
    g.resize(this->n);
  }

  ~GraphAdj() {
    for (int u = 0; u < this->n; u++) {
      for (auto e : g[u]) {
        assert(e);
        delete e;
      }
    }
  }

  vector<EdgeAdj<T>*> edges(int u) override {
    vector<EdgeAdj<T>*> ret;
    for (auto e : g[u]) {
      ret.push_back(e);
    }
    return ret;
  }

  void add(int u, int v, T cost = 1) override {
    this->m++;
    g[u].push_back(new EdgeAdj<T>{v, cost});
  }
};


// Forward star representation of a graph.
template <class T>
struct EdgeStar {
  int to;
  int next;
  T cost;
};

// M denotes the maximum number of edges this graph might have.
template <class T, int M>
struct GraphStar : public Graph<T, EdgeStar<T>> {
  vector<EdgeStar<T>*> g;
  vector<int> cnt;
  const int kDefault = -1;

  GraphStar() {
    this->m = 0;
    g.resize(M);
    cnt.resize(M, -1);
  }

  ~GraphStar() {
    for (int i = 0; i < this->m; i++) {
      assert(g[i]);
      delete g[i];
    }
  }

  vector<EdgeStar<T>*> edges(int u) override {
    vector<EdgeStar<T>*> ret;
    for (int x = cnt[u]; x != -1; x = g[x]->next) {
      ret.push_back(g[x]);
    }
    return ret;
  }

  void add(int u, int v, T cost = 1) override {
    g[this->m] = new EdgeStar<T>{kDefault, kDefault, kDefault};
    g[this->m]->to = v;;
    g[this->m]->cost = cost;
    g[this->m]->next = cnt[u];
    cnt[u] = this->m++;
  }
};

// Left child and right brother representation of a graph.
template <class T>
struct EdgeChild {
  int child;
  int brother;
  T cost;
};

template <class T>
struct GraphChild : public Graph<T, EdgeChild<T>> {
  // int n;
  vector<EdgeChild<T>*> g;
  const int kDefault = -1;

  GraphChild(int n_) {
    this->n = n_;
    g.resize(this->n, new EdgeChild<T>{kDefault, kDefault, 1});
  }

  ~GraphChild() {
    for (auto e : g) {
      delete e;
    }
  }

  vector<EdgeChild<T>*> edges(int u) override {
    vector<EdgeChild<T>*> ret;
    while (u != kDefault) {
      ret.push_back(&g[u]);
      u = g[u].child;
    }
    return ret;
  }

  void add(int u, int v, T cost = 1) override {
    // u-->v
    g[v].brother = g[u].child;
    g[u].child = v;
    g[u].cost = cost;
  }
};

