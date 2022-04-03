void quick_sort(vector<int>& v, int l, int r) {
  if (l >= r) return;
  int lo = l + 1;
  int hi = r;
  int pivot = v[l];
  while (lo <= hi) {
    while (lo <= hi && v[lo] <= pivot) lo++;
    while (lo <= hi && v[hi] >= pivot) hi--;
    // invariant: v[hi] < pivot && v[lo] > pivot
    if (lo < hi) {
      swap(v[lo], v[hi]);
    }
  }
  // invariant: v[hi] < pivot && v[lo] > pivot
  swap(v[l], v[hi]);
  quick_sort(v, l, hi - 1);
  quick_sort(v, hi + 1, r);
}

void merge_sort(vector<int>& v, vector<int>& aux, int lo, int hi) {
  if (l >= r) return;
  int md = lo + (hi - lo) / 2;
  merge_sort(v, aux, lo, md);
  merge_sort(v, aux, md + 1, hi);
  //  i          j
  // [lo ... md md+1...hi]
  for (int i = lo, j = md + 1, k = lo; k <= hi; k++) {
    if (j > hi || (i <= md && v[i] <= v[j])) {
      aux[k++] = v[i++];
    } else {
      aux[k++] = v[j++];
    }
  }
  for (int k = lo; k <= hi; k++) {
    v[k] = aux[k];
  }
}

template <int N>
vector<int> count_sort(vector<int>& A) {
  vector<int> cnt(N);
  for (int i = 0; i < A.size(); i++) {
    cnt[A[i]]++;
  }
  for (int i = 1; i < N; i++) {
    cnt[i] += cnt[i - 1];
  }
  vector<int> ans(A.size());
  for (int i = 0; i < A.size(); i++) {
    ans[--cnt[A[i]]] = A[i];
  }
  return ans;
}

vector<int> count_sort(vector<int>& A, int D, int radix = 10) {
  int n = A.size();
  vector<int> cnt(radix);
  int v = 1;
  for (int i = 0; i < D; i++) {
    v *= radix;
  }
  for (int i = 0; i < n; i++) {
    cnt[(A[i] / v) % 10]++;
  }
  for (int i = 1; i < radix; i++) {
    cnt[i] += cnt[i - 1];
  }
  vector<int> ans(n);
  // NOTE: go backward to keep the order sorted before
  for (int i = n - 1; i >= 0; i--) {
    int d = (A[i] / v) % 10;
    ans[--cnt[d]] = A[i];
  }
  return ans;
}

vector<int> radix_sort(vector<int>& A, int radix = 10) {
  int mx = *max_element(A.begin(), A.end());
  int digit = log2(mx) / log2(radix) + 1;
  for (int i = 0; i < digit; i++) {
    A = count_sort(A, i, radix);
  }
  return A;
}

vector<int> bucket_sort(vector<int>& A) {
  int mi = *min_element(A.begin(), A.end());
  int mx = *max_element(A.begin(), A.end());
  int n = A.size();
  int bucket_num = n;
  int bucket_range = (mx - mi + 1 + bucket_num - 1) / bucket_num;
  vector<vector<int>> buckets(bucket_num);
  for (int i = 0; i < n; i++) {
    int idx = (A[i] - mi) / bucket_range;
    assert(0 <= idx && idx < bucket_num);
    buckets[idx].push_back(A[i]);
  }
  for (int i = 0; i < bucket_num; i++) {
    sort(buckets[i].begin(), buckets[i].end());
  }
  vector<int> ans;
  for (auto& it : buckets) {
    for (int t : it) {
      ans.push_back(t);
    }
  }
  return ans;
}

// -----------------------------------------------------------------------------
ListNode* merge_list(ListNode* l1, ListNode* l2) {
  if (!l1) return l2;
  if (!l2) return l1;
  ListNode *root = new ListNode(-1), *p;
  p = root;
  while (l1 || l2) {
    if (!l2 || (l1 && l1->val < l2->val)) {
      p->next = l1;
      l1 = l1->next;
    } else {
      p->next = l2;
      l2 = l2->next;
    }
    p = p->next;
  }
  p->next = nullptr;
  return root->next;
}

// -----------------------------------------------------------------------------
struct ListNode {
  ListNode(int val_, ListNode* next_ = nullptr)
    : val(val_), next(next_) {}

  int val;
  ListNode* next;
};

ListNode* build(const vector<int>& v) {
  ListNode* node = nullptr;
  for (int i = (int) v.size() - 1; i >= 0; i--) {
    node = new ListNode(v[i], node);
  }
  return new ListNode(-1, node); // dummy head node
}

void traverse_list(ListNode* l1) {
  for (ListNode **p = &l1->next; *p; p = &(*p)->next) {
    cout << (*p)->val << " ";
  }
  cout << "\n";
}

void delete_node(ListNode* l1, int val) {
  for (ListNode **p = &l1->next; *p; p = &(*p)->next) {
    while ((*p)->val == val) {
      *p = (*p)->next;
    }
  }
}

void insert_after(ListNode* l1, int val) {
  l1->next = new ListNode(val, l1->next);
}

// -----------------------------------------------------------------------------
// Prefix sum
int a[N];
void prefix_sum() {
  for (int i = 1; i <= n; i++) {
    ps[i] = ps[i - 1] + a[i];
  }
  // length l to r
  sum[l... r] = ps[r] - ps[l - 1];
}

int a[N][M];
void prefix_sum2() {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      ps[i][j] = ps[i - 1][j] + ps[i][j - 1] + a[i][j] - ps[i - 1][j - 1];
    }
  }
  // (x1, y1)-------
  //         |      |
  //         |______(x2, y2)
  sum[(x1, y1), (x2, y2)] =
      ps[x2][y2] - ps[x1 - 1][y2] - ps[x2][y1 - 1] + ps[x1 - 1][y1 - 1];
}

// Difference
void func() {
  // Add value x to interval [l...r]
  //                          x...0  -x
  v[l] += x;
  v[r + 1] -= x;
  for (int i = l; i <= r; i++) {
    v[i + 1] += a[i];
  }
}

// Binary search
void binary_search() {
  // 0000000---1111111
  //       lo--hi
  int lo = -1;
  int hi = n + 1;
  while (lo + 1 < hi) {
    int md = lo + (hi - lo) / 2;
    if (check(md)) {
      hi = md;
    } else {
      lo = md;
    }
  }
}

// Two pointers (660c.cc)
void solve() {
  for (int lo = 0, hi = 0; lo < n; lo++) {
    if (lo > hi) {
      hi = lo;
      cnt = 0;
    }
    while (hi < n && check(hi)) {
      hi++;
    }
    // [lo...hi)

    // Move lo one step forward.
    if (cnt > 0) {
      cnt -= !a[lo];
    }
  }
}

// Discrete
template <int N>
struct Discreter {
  vector<int> e;
  vector<int> t;

  Discreter(vector<int>& v) {
    e = v;
    sort(all(e));
    e.erase(unique(all(e)), e.end());
    for (int i = 0; i < N; i++) {
      int x = upper_bound(all(e), i) - e.begin();
      t.push_back(x);
    }
  }

  // Given a original value, returns the discreted value.
  int get(int x) { return t[x]; }

  // Given a discreted value, return the original value.
  int old(int x) { return e[x - 1]; }
};

// -----------------------------------------------------------------------------
// Stack (133.cc)
void solve() {
  vector<ll> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  a.push_back(0), n++;
  trace(a, n);
  vector<int> stk;
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    if (stk.empty() || a[i] >= a[stk.back()]) {
      stk.push_back(i);
      continue;
    }

    while (!stk.empty() && a[stk.back()] > a[i]) {
      ll height = a[stk.back()];
      stk.pop_back();
      ll lo = stk.empty() ? -1 : stk.back();
      ans = max(ans, (i - lo - 1) * height);
    }

    stk.push_back(i);
  }
  cout << ans << "\n";
}

// Queue (137.cc)
// 输入一个长度为 n 的整数序列，从中找出一段长度不超过 <= m 的连续子序列，
// 使得子序列中所有数的和最大。
// 注意： 子序列的长度至少是 1。
void solve() {
  int N, M; cin >> N >> M;
  vector<int> a(N + 1);
  vector<ll> ps(N + 1);
  for (int i = 1; i <= N; i++) {
    cin >> a[i];
    ps[i] = ps[i - 1] + a[i];
  }

  deque<int> qu;
  qu.push_back(0);
  ll ans = INT_MIN;
  for (int i = 1; i <= N; i++) {
    // front [ <-, <-, <-,
    //                     i
    while (qu.size() && i - qu.front() > M) {
      qu.pop_front();
    }

    // ps[i] - ps[i - m] -> i-m+1 ... i (m)
    assert(qu.size());
    ans = max(ans, ps[i] - ps[qu.front()]);

    while (qu.size() && ps[i] <= ps[qu.back()]) {
      qu.pop_back();
    }
    qu.push_back(i);
  }
  cout << ans << "\n";
}

template <int N>
struct Trie {
  vector<array<int, 26>> node;
  vector<int> leaf;
  // 0 is reserved for trie root.
  int p = 1;

  Trie() {
    node.resize(N);
    leaf.resize(N);
  }

  int get(char ch) { return ch - 'a'; }

  void add(const string& s) {
    int u = 0;
    for (auto ch : s) {
      int v = get(ch);
      if (!node[u][v]) {
        node[u][v] = p++;
      }
      u = node[u][v];
    }
    leaf[u]++;
  }

  bool find(const string& s, int* ret = nullptr) {
    int u = 0;
    for (auto ch : s) {
      int v = get(ch);
      if (!node[u][v]) {
        if (ret) *ret = 0;
        return false;
      }
      u = node[u][v];
    }
    *ret = leaf[u];
    return leaf[u] > 0;
  }
};

// Dsu
struct Dsu {
  int n;
  vector<int> e;

  Dsu(int n) : n(n_) { e.resize(n, -1); }

  int size(int x) { return -e[find(x)]; }

  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }

  bool join(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) {
      // Join not occur.
      return false;
    }
    if (size(a) < size(b)) {
      swap(a, b);
    }
    e[a] += e[b];
    e[b] = a;
    n--;
    return true;
  }
};

// Bit
template <class T>
struct Bit {
  vector<T> t;
  int n;

  int lowbit(x) { return x & -x; }

  Bit(int n_) : n(n_) { t.resize(n + 1); }

  void add(int x, int d) {
    for (; x <= n; x += lowbit(x)) {
      t[x] += d;
    }
  }

  // Query sum of interval [1...x].
  T query(int x) {
    T ans = 0;
    for (; x > 0; x -= lowbit(x)) {
      ans += t[x];
    }
    return ans;
  }

  T query(int l, int r) { return query(r) - query(l - 1); }
};

//-----------------------------------------------------------------------------
// bfs
vector<int> vis(N); // whether a node is in queue before
vector<int> g[N];
void bfs() {
  deque<int> qu;
  qu.push_back(root);
  vis[root] = true;
  while (qu.size()) {
    int u = qu.front();
    qu.pop_front();
    // vis[u] = true; this is wrong, we might add the same node
    // into the queue more than once
    for (auto v : g[u]) {
      if (!vis[v]) {
        qu.push_back(v);
        vis[v] = true; // this is correct
      }
    }
  }
}

// dfs (any graph), shouldn't pass `parent`
vector<int> vis(N);
void dfs(int u) {
  vis[u] = true;
  for (auto v : g[u]) {
    if (!vis[v]) {
      dfs(v);
    }
  }
}

// for a tree (with cycle)
void dfs(int u, int parent) {
  for (int v : g[u]) {
    if (v == parent) continue;
    dfs(v);
  }
}

// topological sort
void toposort_dfs() {
  // a --> b, b must start before a
  vector<int> ans;
  vector<int> vis(N);
  std::function<void(int)> dfs = [&](int u) {
    vis[u] = 1; // active
    for (int v : g[u]) {
      if (vis[v] == 1) {
        // Cycle exists.
        cout << "IMPOSSIBLE\n";
        exit(0);
      }
      else if (vis[v] == 0) {
        dfs(v);
      }
      else {
        assert(vis[v] == 2);
        // already processed
      }
    }
    // all tasks need to be done finished, then we start to do `u`
    ans.push_back(u);
    vis[u] = 2; // finished
  };
  for (int i = 0; i < N; i++) {
    if (!vis[i]) {
      dfs(i);
    }
  }
}

bool toposort() {
  // a --> b, a must start before b, deg[b]++
  vector<int> free_nodes;
  vector<int> deg;  // incoming degree
  for (int i = 0; i < n; i++) {
    if (!deg[i]) {
      free_nodes.push_back(i);
    }
  }
  vector<int> order;
  while (free_nodes.size()) {
    int u = free_nodes.back();
    free_nodes.pop_back();
    order.push_back(u);
    for (auto v : g[u]) {
      if (--deg[v] == 0) {
        free_nodes.push_back(v);
      }
    }
  }
  // whether topological sort exists.
  return (int)order.size() == n;
}

// Dijkstra shortest path
void dijkstra(int root) {
  vector<int> dist(n, INF);
  priority_queue<ar, vector<ar>> qu;
  dist[root] = 0;
  qu.push_back({0, root});
  while (qu.size()) {
    auto tp = -qu.top(); qu.pop();
    int d = tp[0], u = tp[1];
    //     1
    //   /   \(1)
    //(2)|   3
    //   \   /(0)
    //     4
    // If the shortest path already know.
    if (dist[u] < d) continue;
    // step1: (-2, 4)(4 in queue first), (-1, 3)
    // step2: (-1, 4), (-2, 4)
    for (auto v : g[u]) {
      if (dist[v] > d + weight[u][v]) {
        dist[v] = d + weight[u][v];
        qu.push_back({-dist[v], v});
      }
    }
  }
}

// bellman_ford can detect negative cycle
void bellman_ford() {
  vector<T> dist(n, INF);
  dist[root] = 0;
  for (int i = 0; i < n - 1; i++) {
    for (int u = 0; u < n; u++) {
      for (auto [v, w] : g[u]) {
        dist[v] = min(dist[v], dist[u] + w);
      }
    }
  }
  bool negative_cycle = false;
  for (int u = 0; u < n; u++) {
    for (auto [v, w] : g[u]) {
      if (dist[u] + w < dist[v]) {
        negative_cycle = true;
        return;
      }
    }
  }
}
