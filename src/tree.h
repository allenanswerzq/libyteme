// tree
// tree diamter (dp, dfs, bfs)
int diamter(vector<vector<int>>& g) {
  int n = g.size();
  vector<bool> use(n);
  int max_depth = 0;
  int farest = -1;
  function<void(int, int)> dfs = [&](int u, int depth) {
    if (depth > max_depth) {
      max_depth = depth;
      farest = u;
    }
    use[u] = true;
    for (auto v : g[u]) {
      if (!use[v]) {
        dfs(v, depth + 1);
      }
    }
  };
  dfs(0, 0);
  max_depth = 0;
  use.assign(n, false);
  dfs(farest, 0);
  return max_depth;
}

int diamter(vector<vector<int>>& g) {
  int n = g.size();
  // d[i] denotes the farthest distance of the root `i`.
  vector<int> d(n);
  vector<int> f(n);
  vector<bool> use(n);
  int ans = 0;
  function<void(int)> dfs = [&](int u) {
    use[u] = true;
    for (auto v : g[u]) {
      if (!use[v]) {
        dfs(v);
        ans = max(ans, d[u] + d[v] + 1/*weight(u, v)*/);
        d[u] = max(d[u], d[v] + 1/*weight(u, v)*/);
      }
    }
  };
  dfs(0);
  trace(d);
  return ans;
}

// 质心
// 每个点的最远点
