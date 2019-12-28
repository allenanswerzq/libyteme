// Shortest path algorithm on graph

// single source shortest path
// o(e * logv)
template <class T, T INF, class E>
vector<T> dijkstra(Graph<T, E>& ga, int src) {
  int n = ga.n;
  vector<T> dist(n, INF);
  typedef pair<T, int> PII;
  priority_queue<PII, vector<PII>, greater<PII>> q;
  dist[src] = 0;
  q.push({0, src});
  while (!q.empty()) {
    auto tp = q.top();
    q.pop();
    T d = tp.first;
    int u = tp.second;
    // Very important piece of code here
    if (d > dist[u]) {
      continue;
    }
    for (auto e : ga.edges(tp.second)) {
      if (dist[u] + e->cost < dist[e->to]) {
        dist[e->to] = dist[u] + e->cost;
        q.push(PII{dist[e->to], e->to});
      }
    }
  }
  return dist;
}

// O(v * e)
template <class T, T INF, class E>
vector<T> bellman_ford(const Graph<T, E>& ga, int src, bool* negative_cycle) {
  int n = ga.n;
  vector<T> dist(n, INF);
  dist[src] = 0;
  for (int i = 0; i < n - 1; i++) {
    for (int u = 0; u < n; u++) {
      for (auto e : ga.edges(u)) {
        dist[e->to] = min(dist[e->to], dist[u] + e->cost);
      }
    }
  }
  for (int u = 0; u < n; u++) {
    for (auto e : ga.edges(u)) {
      if (dist[u] + e->cost < dist[e->to]) {
        negative_cycle = true;
      }
    }
  }
  return negative_cycle ? vector<T>{} : dist;
}

// all pairs shortest path
// o(v ^ 3)
template <class T, T INF, class E>
vector<vector<T>> floyd_warshall(const Graph<T, E>& ga) {
  int n = ga.n;
  vector<vector<T>> dist(n, vector<T>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j) {
        dist[i][j] = 0;
      }
      else {
        dist[i][j] = INF;
      }
    }
  }
  for (int u = 0; u < n; u++) {
    for (auto e : ga.edges(u)) {
      dist[u][e->to] = e.cost;
    }
  }
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }
  return dist;
}
