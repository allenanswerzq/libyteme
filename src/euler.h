class EulerCycle {
 public:
  EulerCycle(int n) : n_(n) {
    g_.resize(n_);
  }

  void AddEdge(int u, int v) {
    int idx = edges_.size();
    g_[u].push_back(idx);
    g_[v].push_back(idx);
    edges_.push_back(make_pair(u, v));
  }

  // Returns a vector has size `m + 1` means cycle exists.
  vector<int> FindEulerCycle() {
    for (int u = 0; u < n_; u++) {
      if (g_[u].size() & 1) {
        return {};
      }
    }
    vector<int> vis(edges_.size());
    vector<int> ans;
    trace(edges_);
    ans.push_back(0);
    Dfs(vis, 0, &ans);
    return ans;
  }

 private:
  void Dfs(vector<int>& vis, int u, vector<int>* ans) {
    while (g_[u].size()) {
      int idx = g_[u].back();
      g_[u].pop_back();
      if (vis[idx]) continue;
      vis[idx] = 1;
      Dfs(vis, edges_[idx].first ^ edges_[idx].second ^ u, ans);
      ans->push_back(u);
    }
  }

  int n_;
  vector<vector<int>> g_;
  vector<pair<int, int>> edges_;
};
