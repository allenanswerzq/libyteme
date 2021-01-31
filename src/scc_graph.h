class SccGraph {
 public:
  explicit SccGraph(int n) : n_(n), scc_index_(0) {
    g_.resize(n_);
    z_.resize(n_);
  }

  void add(int u, int v) {
    gv_.gvAddEdge(u, v);
    g_[u].push_back(Edge{v});
    z_[v].push_back(Edge{u});
  }

  int scc_count() const { return scc_index_; }

  vector<vector<int>> component_group() {
    vector<int> scc = do_scc();
    int scc_count = scc_count();
    assert((int)scc.size() == n_);
    assert(scc_count >= 1);
    vector<vector<int>> ans(scc_count);
    for (int i = 0; i < n_; i++) {
      ans[scc[i]].push_back(i);
    }
    for (int i = 0; i < scc_count; i++) {
      assert(ans[i].size() > 0);
    }
    return ans;
  }

  // Returns: scc_id for every node
  std::vector<int> do_scc() {
    if (scc_.size()) {
      return scc_;
    }
    gv_.gvDrawGraph();
    vector<int> vis(n_);
    vector<int> order;
    for (int i = 0; i < n_; i++) {
      if (!vis[i]) {
        dfs(g_, vis, i, &order, /*scc=*/nullptr);
      }
    }
    vis.assign(n_, 0);
    scc_.resize(n_);
    scc_index_ = 0;
    for (int i = order.size() - 1; i >= 0; i--) {
      int u = order[i];
      if (!vis[u]) {
        dfs(z_, vis, u, /*order=*/nullptr, &scc_);
        scc_index_++;
      }
    }
    return scc_;
  }

  vector<vector<int>> component_graph() {
    vector<int> scc = do_scc();
    int cnt = scc_count();
    vector<set<int>> tmp(cnt);
    for (int u = 0; u < n_; u++) {
      for (Edge& e : g_[u]) {
        int v = e.to;
        if (scc[u] != scc[v]) {
          tmp[scc[u]].insert(scc[v]);
        }
      }
    }
    vector<vector<int>> ans(cnt);
    Graphviz cg("cg");
    for (int i = 0; i < cnt; i++) {
      for (int u : tmp[i]) {
        cg.gvAddEdge(i, u);
        ans[i].push_back(u);
      }
    }
    cg.gvDrawGraph();
    return ans;
  }

  // Represents an edge
  struct Edge {
    int to;
  };

  void dfs(vector<vector<Edge>>& g, vector<int>& vis, int u,
           vector<int>* order, vector<int>* scc = nullptr) {
    vis[u] = 1;
    if (scc) {
      assert(scc->size() == g.size());
      scc->operator[](u) = scc_index_;
    }
    for (auto& e : g[u]) {
      int v = e.to;
      if (vis[v] == 0) {
        dfs(g, vis, v, order, scc);
      }
    }
    if (order) {
      order->push_back(u);
    }
    vis[u] = 2;
  }

  int n_;
  int scc_index_;
  Graphviz gv_;
  vector<vector<Edge>> g_;
  vector<vector<Edge>> z_;
  vector<int> scc_;
};

class SATSolver {
 public: explicit SATSolver(int n) : n_(n + 1), g_(2 * n_) {}
  // (u | v) && ()
  // NOTE: use -x to represent not x here, so make sure `0` will not appear.
  void add(int u, int v) {
    // -u ==> v  if u is false, then v must be true
    // -v ==> u
    g_.add(f(-u), f(v));
    g_.add(f(-v), f(u));
  }

  // Returns the boolean value for each variable.
  // https://cp-algorithms.com/graph/2SAT.html
  vector<int> solve() {
    vector<int> scc = g_.do_scc();
    for (int i = 1; i < n_; i++) {
      if (scc[f(i)] == scc[f(-i)]) {
        return vector<int>();
      }
    }
    vector<int> ans(n_);
    for (int i = 1; i < n_; i++) {
      ans[i] = scc[f(i)] > scc[f(-i)];
    }
    return ans;
  }

 private:
  int f(int u) {
    assert(u != 0);
    if (u < 0) {
      return 2 * (-u) + 1;
    }
    else {
      return 2 * u;
    }
  }
  int n_;
  SccGraph g_;
};

// Not tested
struct TarjanScc {
  vector<vector<int>> g;
  vector<int> scc;
  vector<int> pre;
  vector<int> low;
  vector<int> stk;
  int scc_cnt;
  int order;
  int n;
  int m;

  TarjanScc(int n_) : n(n_) {
    g.resize(n);
    scc.resize(n);
    low.resize(n);
    pre.resize(n, -1);
    scc_cnt = 0;
    order = 0;
  }

  void add(int u, int v) {
    g[u].push_back(v);
    m++;
  }

  void dfs(int u) {
    pre[u] = order++;
    low[u] = pre[u];
    stk.push_back(u);
    for (int v : g[u]) {
      if (pre[v] == -1) {
        // Forward edge
        dfs(v);
        low[u] = min(low[u], low[v]);
      }
      else {
        // Back edge or cross edge
        low[u] = min(low[u], pre[v]);
      }
    }
    if (low[u] == pre[u]) {
      // Root node of a scc
      scc[u] = scc_cnt;
      while (true) {
        int v = stk.pop_back();
        scc[v] = scc_cnt;
        pre[v] = m;     // ignore the cross edge
        if (v == u) break;
      }
      scc_cnt++;
    }
  }

  void do_dfs() {
    for (int i = 0; i < N; i++) {
      if (pre[i] == -1) {
        dfs(i);
      }
    }
    assert(stk.empty());
  }

  vector<vector<int>> scc_group() {
    vector<vector<int>> ans;
    for (int i = 0; i < g.scc_cnt; i++) {
      vector<int> cur;
      for (int j = 0; j < N; j++) {
        if (scc[j] == i) {
          cur.push_back(j);
        }
      }
      ans.push_back(cur);
    }
    return ans;
  }

  vector<vector<int>> meta_graph() {
    vector<set<int>> mg(scc_count);
    vector<vector<int>> ans(scc_cnt);
    for (int i = 0; i < N; i++) {
      for (int v : g[i]) {
        if (scc[i] != scc[v]) {
          if (!mg[scc[i]].count(scc[v])) {
            mg[scc[i]].insert(scc[v]);
            ans[scc[i]].push_back(scc[v]);
          }
        }
      }
    }
    return ans;
  }
};
