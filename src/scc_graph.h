struct TarjanScc {
  vector<vector<int>> g;
  vector<int> scc;
  // Pre order sequence
  vector<int> pre;
  // Low link value
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

  void add_edge(int u, int v) {
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
        int v = stk.back();
        stk.pop_back();
        scc[v] = scc_cnt;
        // NOTE: ignore the cross edge
        // r -> u, r -> v, v -> u
        //        r
        //     /     \
        //    u <---- v
        //
        // When processing node v, the edge v -> u will be a cross edge,
        // even though it reaches u, but it does not effect the low link
        // value that v can escape.
        //
        pre[v] = m;
        if (v == u) break;
      }
      scc_cnt++;
    }
  }

  void do_dfs() {
    for (int i = 0; i < n; i++) {
      if (pre[i] == -1) {
        dfs(i);
      }
    }
    assert(stk.empty());
  }

  vector<vector<int>> scc_group() {
    vector<vector<int>> ans(scc_cnt);
    for (int i = 0; i < n; i++) {
      assert(0 <= scc[i] && scc[i] < scc_cnt);
      ans[scc[i]].push_back(i);
    }
    return ans;
  }

  vector<vector<int>> meta_graph() {
    vector<set<int>> mg(scc_cnt);
    vector<vector<int>> ans(scc_cnt);
    for (int u = 0; u < n; u++) {
      for (int v : g[u]) {
        int su = scc[u];
        int sv = scc[v];
        if (su != sv) {
          if (!mg[su].count(sv)) {
            mg[su].insert(sv);
            ans[su].push_back(sv);
          }
        }
      }
    }
    return ans;
  }
};

struct SATSolver {
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
  TarjanScc g_;

  SATSolver(int n) : n_(n + 1), g_(2 * n_) {}

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
    g_.do_dfs();
    vector<int> scc = g_.scc;
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

};


