template <class T>
class DinicFlow {
 public:
  explicit DinicFlow(int n) : DinicFlow(n, 0, n - 1) {}

  DinicFlow(int n, int s, int t) : n_(n), src_(s), dst_(t) {
    g_.resize(n_);
    d_.resize(n_);
    cnt_.resize(n_);
    gv_.gvSetDirected();
  }

  void add(int u, int v, int forward_cap, int backward_cap = 0) {
    assert(0 <= u && u < n_);
    assert(0 <= v && v < n_);
    int su = g_[u].size();
    int sv = g_[v].size();
    gv_.gvAddEdge(u, v, forward_cap);
    g_[u].push_back(Edge{v, forward_cap, 0, sv});
    g_[v].push_back(Edge{u, backward_cap, 0, su});
  }

  T max_flow() {
    gv_.gvDrawGraph();
    T flow = 0;
    while (level_graph()) {
      fill(cnt_.begin(), cnt_.end(), 0);
      while (true) {
        T f = dfs(src_, numeric_limits<T>::max());
        if (f == 0) break;
        flow += f;
      }
    }
    return flow;
  }

  vector<bool> min_cut() {
    ll f = max_flow();
    trace(f);
    (void)f;
    vector<bool> ans(n_);
    for (int i = 0; i < n_; i++) {
      ans[i] = (d_[i] != -1);
    }
    return ans;
  }

  T dfs(int u, T w) {
    if (u == dst_) {
      return w;
    }
    for (int& i = cnt_[u]; i < (int)g_[u].size(); i++) {
      Edge& e = g_[u][i];
      if (e.c > e.f && d_[e.v] == d_[u] + 1) {
        T t = dfs(e.v, min(e.c - e.f, w));
        if (t > 0) {
          e.f += t;
          g_[e.v][e.rev].f -= t;
          return t;
        }
      }
    }
    return 0;
  }

  bool level_graph() {
    deque<int> qu;
    qu.push_back(src_);
    fill(d_.begin(), d_.end(), -1);
    d_[src_] = 0;
    while (qu.size()) {
      int u = qu.front();
      qu.pop_front();
      for (Edge& e : g_[u]) {
        if (e.c > e.f && d_[e.v] == -1) {
          d_[e.v] = d_[u] + 1;
          if (e.v == dst_) {
            return true;
          }
          qu.push_back(e.v);
        }
      }
    }
    return false;
  }

  struct Edge {
    int v;
    T c;
    T f;
    int rev;  // The reverse edge position.
    friend ostream& operator<<(ostream& os, const Edge& e) {
      os << "(" << e.v << ", " << e.c << ", " << e.f << ", " << e.rev << ")";
      return os;
    }
  };

  int n_;
  int src_;
  int dst_;
  vector<int> d_;
  vector<int> cnt_;
  vector<vector<Edge>> g_;
  Graphviz gv_;
};
