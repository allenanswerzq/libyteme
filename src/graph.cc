template <typename T>
class graph {
  public:
  struct edge {
    int from;
    int to;
    T cost;
  };

  vector<edge> edges;
  vector< vector<int> > g;
  int n;

  function<bool(int)> ignore;

  graph(int _n) : n(_n) {
    g.resize(n);
    ignore = nullptr;
  }

  virtual int add(int from, int to, T cost) = 0;

  virtual void set_ignore_edge_rule(const function<bool(int)> &f) {
    ignore = f;
  }

  virtual void reset_ignore_edge_rule() {
    ignore = nullptr;
  }
};

template <typename T>
class forest : public graph<T> {
  public:
  using graph<T>::edges;
  using graph<T>::g;
  using graph<T>::n;

  forest(int _n) : graph<T>(_n) {
  }

  int add(int from, int to, T cost = 1) {
    assert(0 <= from && from < n && 0 <= to && to < n);
    int id = (int) edges.size();
    assert(id < n - 1);
    g[from].push_back(id);
    g[to].push_back(id);
    edges.push_back({from, to, cost});
    return id;
  }
};

template <typename T>
class dfs_forest : public forest<T> {
  public:
  using forest<T>::edges;
  using forest<T>::g;
  using forest<T>::n;
  using forest<T>::ignore;

  vector<int> pv;
  vector<int> pe;
  vector<int> order;
  vector<int> pos;
  vector<int> end;
  vector<int> sz;
  vector<int> root;
  vector<int> depth;
  vector<T> dist;

  dfs_forest(int _n) : forest<T>(_n) {
  }

  void init() {
    pv = vector<int>(n, -1);
    pe = vector<int>(n, -1);
    order.clear();
    pos = vector<int>(n, -1);
    end = vector<int>(n, -1);
    sz = vector<int>(n, 0);
    root = vector<int>(n, -1);
    depth = vector<int>(n, -1);
    dist = vector<T>(n);
  }

  void clear() {
    pv.clear();
    pe.clear();
    order.clear();
    pos.clear();
    end.clear();
    sz.clear();
    root.clear();
    depth.clear();
    dist.clear();
  }

  private:
  void do_dfs(int v) {
    pos[v] = (int) order.size();
    order.push_back(v);
    sz[v] = 1;
    for (int id : g[v]) {
      if (id == pe[v] || (ignore != nullptr && ignore(id))) {
        continue;
      }
      auto &e = edges[id];
      int to = e.from ^ e.to ^ v;
      depth[to] = depth[v] + 1;
      dist[to] = dist[v] + e.cost;
      pv[to] = v;
      pe[to] = id;
      root[to] = (root[v] != -1 ? root[v] : to);
      do_dfs(to);
      sz[v] += sz[to];
    }
    end[v] = (int) order.size() - 1;
  }

  void do_dfs_from(int v) {
    depth[v] = 0;
    dist[v] = T{};
    root[v] = v;
    pv[v] = pe[v] = -1;
    do_dfs(v);
  }

  public:
  void dfs(int v, bool clear_order = true) {
    if (pv.empty()) {
      init();
    } else {
      if (clear_order) {
        order.clear();
      }
    }
    do_dfs_from(v);
  }

  void dfs_all() {
    init();
    for (int v = 0; v < n; v++) {
      if (depth[v] == -1) {
        do_dfs_from(v);
      }
    }
    assert((int) order.size() == n);
  }
};

template <typename T>
class lca_forest : public dfs_forest<T> {
  public:
  using dfs_forest<T>::edges;
  using dfs_forest<T>::g;
  using dfs_forest<T>::n;
  using dfs_forest<T>::pv;
  using dfs_forest<T>::pos;
  using dfs_forest<T>::end;
  using dfs_forest<T>::depth;

  int h;
  vector< vector<int> > pr;

  lca_forest(int _n) : dfs_forest<T>(_n) {
  }

  inline void build_lca() {
    assert(!pv.empty());
    int max_depth = 0;
    for (int i = 0; i < n; i++) {
      max_depth = max(max_depth, depth[i]);
    }
    h = 1;
    while ((1 << h) <= max_depth) {
      h++;
    }
    pr.resize(n);
    for (int i = 0; i < n; i++) {
      pr[i].resize(h);
      pr[i][0] = pv[i];
    }
    for (int j = 1; j < h; j++) {
      for (int i = 0; i < n; i++) {
        pr[i][j] = (pr[i][j - 1] == -1 ? -1 : pr[pr[i][j - 1]][j - 1]);
      }
    }
  }

  inline bool anc(int x, int y) {
    return (pos[x] <= pos[y] && end[y] <= end[x]);
  }

  inline int lca(int x, int y) {
    assert(!pr.empty());
    if (anc(x, y)) {
      return x;
    }
    if (anc(y, x)) {
      return y;
    }
    for (int j = h - 1; j >= 0; j--) {
      if (pr[x][j] != -1 && !anc(pr[x][j], y)) {
        x = pr[x][j];
      }
    }
    return pr[x][0];
  }
};

template <typename T>
class hld_forest : public lca_forest<T> {
  public:
  using lca_forest<T>::edges;
  using lca_forest<T>::g;
  using lca_forest<T>::n;
  using lca_forest<T>::ignore;
  using lca_forest<T>::pv;
  using lca_forest<T>::sz;
  using lca_forest<T>::pos;
  using lca_forest<T>::order;
  using lca_forest<T>::depth;
  using lca_forest<T>::dfs;
  using lca_forest<T>::dfs_all;
  using lca_forest<T>::lca;
  using lca_forest<T>::build_lca;

  vector<int> head;
  vector<int> visited;

  hld_forest(int _n) : lca_forest<T>(_n) {
    visited.resize(n);
  }

  void build_hld(const vector<int> &vs) {
    for (int tries = 0; tries < 2; tries++) {
      if (vs.empty()) {
        dfs_all();
      } else {
        order.clear();
        for (int v : vs) {
//          assert(depth[v] == -1);
          dfs(v, false);
        }
        assert((int) order.size() == n);
      }
      if (tries == 1) {
        break;
      }
      for (int i = 0; i < n; i++) {
        if (g[i].empty()) {
          continue;
        }
        int best = -1, bid = 0;
        for (int j = 0; j < (int) g[i].size(); j++) {
          int id = g[i][j];
          if (ignore != nullptr && ignore(id)) {
            continue;
          }
          int v = edges[id].from ^ edges[id].to ^ i;
          if (pv[v] != i) {
            continue;
          }
          if (sz[v] > best) {
            best = sz[v];
            bid = j;
          }
        }
        swap(g[i][0], g[i][bid]);
      }
    }
    build_lca();
    head.resize(n);
    for (int i = 0; i < n; i++) {
      head[i] = i;
    }
    for (int i = 0; i < n - 1; i++) {
      int x = order[i];
      int y = order[i + 1];
      if (pv[y] == x) {
        head[y] = head[x];
      }
    }
  }

  void build_hld(int v) {
    build_hld(vector<int>(1, v));
  }

  void build_hld_all() {
    build_hld(vector<int>());
  }

  bool apply_on_path(int x, int y, bool with_lca, function<void(int,int,bool)> f) {
    // f(x, y, up): up -- whether this part of the path goes up
    assert(!head.empty());
    int z = lca(x, y);
    if (z == -1) {
      return false;
    }
    {
      int v = x;
      while (v != z) {
        if (depth[head[v]] <= depth[z]) {
          f(pos[z] + 1, pos[v], true);
          break;
        }
        f(pos[head[v]], pos[v], true);
        v = pv[head[v]];
      }
    }
    if (with_lca) {
      f(pos[z], pos[z], false);
    }
    {
      int v = y;
      int cnt_visited = 0;
      while (v != z) {
        if (depth[head[v]] <= depth[z]) {
          f(pos[z] + 1, pos[v], false);
          break;
        }
        visited[cnt_visited++] = v;
        v = pv[head[v]];
      }
      for (int at = cnt_visited - 1; at >= 0; at--) {
        v = visited[at];
        f(pos[head[v]], pos[v], false);
      }
    }
    return true;
  }
};

template <class T>
struct edge {
  int to;
  T cost;
  friend ostream& operator<<(ostream& os, const edge& e) {
    os << "(" << e.to << ", " << e.cost << ")";
    return os;
  }
};

template <class T>
class graph {
 public:
  // Adjcent list representation of a graph
  vector<vector<edge<T>>> g;
  int n;

  graph(int n_) : n(n_) {
    g.resize(n);
  }

  void add_direct(int from, int to) {
    g[from].push_back(edge{to, 0});
  }

  void add_direct(int from, int to, const T& cost) {
    g[from].push_back(edge{to, cost});
  }

  void add_undirect(int from, int to, const T& cost) {
    add_direct(from, to, cost);
    add_direct(to, from, cost);
  }

  graph& operator[](int u) {
    return g[u];
  }
};

// single source shortest path
// o(e * logv)
template <class T>
vector<T> dijkstra(int src) {
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
    if (d > dist[u]) {
    // Very important line of code here
      continue;
    }
    for (edge e : g[tp.second]) {
      if (dist[u] + e.cost < dist[e.to]) {
        dist[e.to] = dist[u] + e.cost;
        q.push(PII{dist[e.to], e.to});
      }
    }
  }
  return dist;

// O(v * e)
vector<int> bellman_ford(const graph& g, int src, bool* negative_cycle) {
  int n = g.n;
  vector<int> dist(n, INF);
  dist[src] = 0;
  for (int i = 0; i < n - 1; i++) {
    for (int u = 0; u < n; u++) {
      for (edge e : g[u]) {
        dist[e.to] = min(dist[e.to], dist[u] + e.cost);
      }
    }
  }
  for (int u = 0; u < n; u++) {
    for (edge e : g[u]) {
      if (dist[u] + e.cost < dist[e.to]) {
        negative_cycle = true;
      }
    }
  }
  return negative_cycle ? vector<int>{} : dist;
}

// all pairs shortest path
// o(v ^ 3)
vector<vector<int>> floyd_warshall(const graph& g) {
  int n = g.n;
  vector<vector<int>> dist(n, vector<int>(n));
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
    for (edge e : g[u]) {
      dist[u][e.to] = e.cost;
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

// Forward star representation of a graph
class graph {
 public:
  struct edge_t {
    int to;
    int next;
    int w;
  };

  const int N = 1e5;
  edge_t edge[N];
  int cnt;
  int g[N];

  graph() {
    cnt = 0;
    memset(g, -1, sizeof(g));
  }

  void add_edge(int u, int v, int w = 0) {
    edge[cnt].to
    edge[cnt].w = w;
    edge[cnt].next = g[u];
    g[u] = cnt++;
  }

  void travse(int s) {
    for (int u = g[s]; u != -1; u = edge[u].next) {
      int v = edge[u].to;
      // u --> v
    }
  }
};

