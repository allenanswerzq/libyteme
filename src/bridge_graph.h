// Compute bridge and articulation points for a graph
struct GraphBridge {
  using Edge = pair<int, int>;
  vector<vector<Edge>> g;
  vector<int> low;
  vector<int> art;
  vector<int> pre;
  vector<pair<int, int>> bridge;
  int order;
  int cnt;
  int n;

  GraphBridge(int n_) : n(n_) {
    g.resize(n);
    low.resize(n);
    art.resize(n);
    pre.resize(n, -1); // pre order
    cnt = 0;
    order = 0;
  }

  void add(int u, int v) {
    g[u].push_back({v, cnt});
    g[v].push_back({u, cnt});
    cnt++;
  }

  // NOTE: use edge id to treat parallel edegs as different edges
  void dfs(int u, int p, int id) {
    pre[u] = order++;
    low[u] = pre[u];
    bool has_fwd = false;
    for (auto& e : g[u]) {
      int v = e.first;
      int c = e.second;
      if (c == id) continue;
      if (pre[v] != -1) {
        // Back edge
        low[u] = min(low[u], pre[v]);
      }
      else {
        // Forward edge
        dfs(v, u, c);
        low[u] = min(low[u], low[v]);
        if (low[v] == pre[v]) {
          bridge.push_back({u, v});
        }
        if (p != -1 ? low[v] >= pre[u] : has_fwd) {
          art[u] = true;
        }
        has_fwd = true;
      }
    }
  }
};
