  vector<int> vis(N + M);
  vector<int> match(N + M, -1);
  std::function<bool(int)> dfs = [&](int u) {
    vis[u] = 1;
    for (int v : g[u]) {
      assert(0 <= u && u < N);
      assert(0 <= v && v < M);
      if (match[v] == -1 || (!vis[match[v]] && dfs(match[v]))) {
        // If node v has not been matched
        // or we can assign new match for his match
        // then we are free to match u and v together and maxinum total matches
        match[v] = u;
        trace("match", u, v);
        return true;
      }
    }
    return false;
  };
  int f = 0;
  for (int i = 0; i < N; i++) {
    fill(vis.begin(), vis.end(), 0);
    trace("dfs start");
    f += dfs(i);
    trace("dfs end", f);
  }
  cout << f << "\n";
  for (int i = 0; i < N; i++) {
    if (~match[i]) {
      cout << match[i] + 1 << " " << i + 1 << "\n";
    }
  }
