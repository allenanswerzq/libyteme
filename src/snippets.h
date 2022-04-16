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

//
// NOTE: modify a set or map ==> erase the old then insert the new.
// multiset<int> vs set<int>
// st.erase(st.find(x))
// st.insert(val)
//
// if st.empty(); assert(st.begin() == st.end())
//
// auto it = st.lower_bound(x);
// if (it != st.end()) [st.begin(), it - 1] < x
//                     [it ... it.end()] >= x
// if (it == st.end())   all values < x
// if (it == st.begin()) all values >= x
//
// auto it = st.upper_bound(x);
// if (it != st.begin()) [st.begin() ... it - 1] <= x
//                       [it .... it.end()] > x
// if (it == st.end())   all values <= x or st is empty
// if (it == st.begin()) all values > x or st is empty()
//
void solve() {
  int N, M, K; cin >> N >> M >> K;
  multiset<int> st;
  for (int i = 0; i < N; i++) {
    int x; cin >> x;
    st.insert(x);
  }
  vector<int> A(M);
  for (auto& a : A) {
    cin >> a;
  }
  sort(all(A));
  int ans = 0;
  for (int i = 0; i < M; i++) {
    auto it = st.lower_bound(A[i] - K);
    auto pt = st.upper_bound(A[i] + K);
    if (it != pt) {
      ans++;
      st.erase(it);
    }
  }
  cout << ans << "\n";
}
//
// interval problems
// 1. sort interval by first
// 2. sort interval by second
// 3. sort edge point (start, 1), (end, -1)
//
// -----------------------------------------------------------------------------
ListNode* reverse(ListNode* root, int k) {
  ListNode *pre = nullptr;
  auto p = root;
  while (k-- && p) {
    auto t = p->next;
    p->next = pre;
    pre = p;
    p = t;
  }
  root->next = p; // connects with the rest chain
  return pre;
}

ListNode* reverse(ListNode* root) {
  if (!root) return nullptr;
  if (!root->next) return root;
  auto l = reverse(root->next);
  // r l
  // 1->2->3
  // ------|
  // 1  3->2
  root->next->next = root;
  root->next = nullptr;
  return l;
}

ListNode* sortList(ListNode* head) {
  if (!head) return nullptr;
  if (!head->next) return head;
  // 1 2 3 4
  // 1 2 3 4 5 -> (n - 1) / 2
  ListNode *fast, *slow;
  fast = slow = head;
  while (fast->next && fast->next->next) {
    slow = slow->next;
    fast = fast->next->next;
    // fast can not be empty, so has to stop at (1...n)
    // take (n - 1) / 2 steps
  }
  ListNode *last = slow->next;
  slow->next = nullptr;
  //cout << slow->val << endl;
  ListNode *l1 = sortList(head);
  ListNode *l2 = sortList(last);
  return merge(l1, l2);
}

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
  return root->next;
}

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
  for (ListNode **p = &l1; *p; ) {
    while (*p && (*p)->val == val) {
      *p = (*p)->next;
    }
    if (*p) p = &(*p)->next;
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

// Difference array
void func() {
  // Zero indexed
  vector<int> A(N)
  vector<int> v(N);
  for (int i = 0; i < N; i++) {
    // NOTE: the first value equals to itself
    v[i] = A[i] - (i > 0 ? A[i - 1] : 0);
  }
  // Add value x to interval A[l...r]
  //
  v[l] += x;
  v[r + 1] -= x;
  // Compute the final array after applying add ops
  for (int i = 0; i + 1 < N; i++) {
    v[i + 1] += v[i];
  }
  // Compute the prefix sum
  vector<int> pre(N + 1);
  for (int i = 0; i < N; i++) {
    pre[i + 1] = pre[i] + v[i];
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

// two sum
sort(all(A));
int lo = i;
int hi = N;
while (lo + 1 <= hi) {
  int s = A[lo] + A[hi];
  if (s == X) {
    break;
  }
  else if (s > X) {
    hi--;
  }
  else {
    lo++;
  }
}

// Two pointers (660c.cc)
void solve() {
  for (int lo = 0, hi = 0; lo < n; lo++/*NOTE: lo++ here*/) {
    // if (lo > hi) {
    //   hi = lo;
    //   cnt = 0;
    // }
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
template <bool ONE = false>
struct Discreter {
  unordered_map<int, int> raw_dis_;
  vector<int> sorted_;

  Discreter(const vector<int> &val) {
    sorted_ = val;
    sort(all(sorted_));
    sorted_.erase(unique(all(sorted_)), sorted_.end());
    for (int x : val) {
      int p = lower_bound(all(sorted_), x) - sorted_.begin() + ONE;
      raw_dis_[x] = p;
    }
  }

  // The maxinum value after discreting
  int max() { return sorted_.size(); }

  // Given a raw value, returns the discreted value.
  int get(int r) { return raw_dis_[r]; }

  // Given a discreted value, returns the raw value.
  int old(int d) { return sorted_[d - ONE]; }
};

// -----------------------------------------------------------------------------
// Stack (133.cc)
void solve() {
  vector<ll> A(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }
  A.push_back(0), N++;
  vector<int> stk;
  ll ans = 0;
  for (int i = 0; i < N; i++) {
    while (stk.size() && A[stk.back()] > A[i]) {
      ll height = A[stk.back()];
      stk.pop_back();
      ll lo = stk.empty() ? -1 : stk.back();
      ans = max(ans, (i - lo - 1) * height);
    }
    stk.push_back(i);
  }
  cout << ans << "\n";
}

// Nearest Smaller Values at the leaf side
void solve() {
  int N; cin >> N;
  vector<int> A(N);
  for (int& a : A) {
    cin >> a;
  }
  vector<int> stk;
  for (int i = 0; i < N; i++) {
    while (stk.size() && A[stk.back()] >= A[i]) {
      stk.pop_back();
    }
    if (i > 0) {
      cout << " ";
    }
    cout << (stk.empty() ? 0 : stk.back() + 1);
    stk.push_back(i);
  }
  cout << "\n";
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

// Bit one-indexed
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
    for (++x; x > 0; x -= lowbit(x)) {
      ans += t[x];
    }
    return ans;
  }

  // Query sum of interval [l...r].
  T query(int l, int r) { return query(r) - query(l - 1); }
};

// zero-indexed
// range min/max/gcd query
struct Segtree {
  Segtree(const std::vector<int> &v) : n(int(v.size())) {
    log = ceil_pow2(n);
    size = 1 << log;
    d = vector<int>(2 * size);
    for (int i = 0; i < n; i++) {
      d[size + i] = v[i];
    }
    for (int i = size - 1; i >= 1; i--) {
      update(i);
    }
  }

  int ceil_pow2(int n) {
    int x = 0;
    while ((1u << x) < n) {
      x++;
    }
    return x;
  }

  void set(int p, int x) {
    assert(0 <= p && p < n);
    p += size;
    d[p] = x;
    for (int i = 1; i <= log; i++) {
      update(p >> i);
    }
  }

  int get(int p) {
    assert(0 <= p && p < n);
    return d[p + size];
  }

  // [l, r)
  int prod(int l, int r) {
    assert(0 <= l && l <= r && r <= n);
    l += size;
    r += size;
    int sml = d[l];   // for computing gcd
    int smr = d[r - 1];
    while (l < r) {
      if (l & 1) sml = __gcd(sml, d[l++]);
      if (r & 1) smr = __gcd(d[--r], smr);
      l >>= 1;
      r >>= 1;
    }
    return __gcd(sml, smr);
  }

  int all_prod() { return d[1]; }

  int n, size, log;
  std::vector<int> d;

  void update(int k) { d[k] = __gcd(d[2 * k], d[2 * k + 1]); }
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
    //
    //     1
    //   /   \(1)
    //(2)|   3 first add 3 into the queue
    //   \   /
    //     4
    for (auto v : g[u]) {
      if (!vis[v]) {
        qu.push_back(v);
        vis[v] = true; // this is correct
      }
    }
  }
}

//
struct TreeNode {
  int val = 0;
  TreeNode *left = nullptr;
  TreeNode *right = nullptr;

  TreeNode() {}
  TreeNode(int x) : val(x) {}
  TreeNode(int x, TreeNode *l, TreeNode *r)
    : val(x), left(l), right(r) {}

  static int NIL;

  // [1,2,3,4,5,null,6,7,8,9,null]
  // bfs level order
  static TreeNode* create(const vector<int> & v) {
    if (v.empty()) return nullptr;
    vector<TreeNode*> qu;
    auto root = new TreeNode(v[0]);
    qu.push_back(root);
    int k = 1;
    for (int i = 0; i < qu.size(); i++) {
      if (!qu[i]) continue;
      // trace(i, qu[i], k);
      if (k < v.size()) {
        auto l = (v[k] == TreeNode::NIL ? nullptr : new TreeNode(v[k]));
        qu[i]->left = l;
        qu.push_back(l);
        k++;
      }
      if (k < v.size()) {
        auto r = (v[k] == TreeNode::NIL ? nullptr : new TreeNode(v[k]));
        qu[i]->right = r;
        qu.push_back(r);
        k++;
      }
    }
    return root;
  }

  vector<int> serialize() {
    vector<int> ans;
    vector<TreeNode*> qu;
    qu.push_back(this);
    for (int i = 0; i < qu.size(); i++) {
      auto root = qu[i];
      ans.push_back(root ? root->val : NIL);
      if (!root) continue;
      if (!root->left && !root->right) continue;
      qu.push_back(root->left);
      if (!root->right) continue;
      qu.push_back(root->right);
    }
    return ans;
  }
};

int TreeNode::NIL = -1;

// dfs
vector<int> vis(N);
void dfs(int u) {
  vis[u] = true;
  for (auto v : g[u]) {
    if (!vis[v]) {
      dfs(v);
    }
  }
}

// for a tree
void dfs(int u, int parent) {
  for (int v : g[u]) {
    if (v == parent) continue;
    dfs(v);
  }
}

// Undirected graph
vector<int> vis(N);
vector<int> pre(N);
std::function<void(int, int)> dfs = [&](int u, int p) {
  vis[u] = 1;
  for (int v : g[u]) {
    if (v == p) continue;
    if (vis[v]) {
      pre[v] = u;
      vector<int> ans;
      for (int j = u;;j = pre[j]) {
        ans.push_back(j);
        if (j == u && ans.size() > 1) {
          break;
        }
      }
      cout << ans.size() << "\n";
      reverse(all(ans));
      for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] + 1 << (i == ans.size() - 1 ? '\n' : ' ');
      }
      exit(0);
    }
    else {
      pre[v] = u;
      dfs(v, u);
    }
  }
};
for (int i = 0; i < N; i++) {
  if (!vis[i]) {
    pre[i] = -1;
    dfs(i, -1);
  }
}


// Visit edges instead of nodes
vector<int> vis(M);
vector<int> ans;
trace(eu, ev, g);
std::function<void(int)> dfs = [&](int u) {
  while (g[u].size()) {
    int e = g[u].back();
    g[u].pop_back();
    if (vis[e]) continue;
    trace(u, eu[e], ev[e], g[u], ans);
    vis[e] = 1;
    dfs(eu[e] ^ u ^ ev[e]);
    ans.push_back(u);
  }
};


// Directed graph topological sort
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

// all toposort orders
// a --> b, a must start before b, deg[b]++
vector<int> vis(N);
vector<int> deg(N);
vector<vector<int>> paths;
void dfs(vector<int>& ans) {
  // This order should be a array with size N that euqals some permutation,
  for (int u = 0; u < N; u++) {
    // On every position, try use all numbers
    if (deg[u] == 0 && vis[u] == 0) {
      for (int v : g[u]) deg[v]--;
      ans.push_back(u);
      vis[u] = 1;

      dfs(ans);     // backtracking

      ans.pop_back();
      vis[u] = 0;
      for (int v : g[u]) deg[v]++;
    }
  }
  if (ans.size() == N) {
    paths.push_back(ans);
  }
}

//
// 从 1∼n 这 n 个整数中随机选出人意多个，输出所有可能的选择方案。
int N;
vector<vector<int>> paths;
void dfs(int i, vector<int>& ans) {
  if (i == N) {
    paths.push_back(ans);
    return;
  }

  ans.push_back(i + 1);
  dfs(i + 1, ans);
  ans.pop_back();

  dfs(i + 1, ans);
}

// 从 1∼n 这 n 个整数中随机选出m个，输出所有可能的选择方案。
int N, M;
void dfs(int i, vector<int>& ans) {
  if (ans.size() == M) {
    for (int k = 0; k < (int) ans.size(); k++) {
      cout << ans[k] << (k == ans.size() - 1 ? '\n' : ' ');
    }
    return;
  }

  if (i == N) return;

  ans.push_back(i + 1);
  dfs(i + 1, ans);
  ans.pop_back();

  dfs(i + 1, ans);
}

// 把 1∼n 这 n 个整数排成一行后随机打乱顺序，输出所有可能的次序。
int N;
vector<int> vis;
void dfs(vector<int>& ans) {
  // On every position, try use all numbers
  for (int i = 0; i < N; i++) {
    if (vis[i] == 0) {
      vis[i] = 1;
      ans.push_back(i + 1);

      dfs(ans);

      ans.pop_back();
      vis[i] = 0;
    }
  }
  if (ans.size() == N) {
    for (int k = 0; k < N; k++) {
      cout << ans[k] << (k == N - 1 ? '\n' : ' ');
    }
  }
}
// -----------------------------------------------------------------------------
// For directed graph
// 1. back edge (cycle)
// 2. cross edge
// 3. forward edge
//
// For undirected graph
// 1. only has forward edge
//
// Tree related (no cycle)
// 1. simple dfs
std::function<void(int)> dfs = [&](int u, int p) {
  for (int v : g[u]) {
    if (v == p) continue;
    dfs(v);
    f[u] += f[v] + 1;
  }
};
// 2. tree dp
// f[u][] = op(f[v][])
//
// 3. tree difference
// c = lca(u, v)
// p = parent[c]
// point: f[u]++, f[v]++, f[c]--, f[p]--
// edge: f[u]+=x, f[v]+=x, f[c] -= 2*x
//
// 4. change root
std::function<void(int, ll)> dfs2 = [&](int u, ll p) {
  vis[u] = 1;
  ans[u] = p;
  for (int v : g[u]) {
    if (!vis[v]) {
      dfs2(v, p - s[v] + (N - s[v]));
    }
  }
};
// 5. 2^k = 2 * 2^(k-1) | lca
for (int k = 1; k < K; k++) {
  for (int i = 0; i < N; i++) {
    int p = f[i][k - 1];
    if (p >= 0) {
      f[i][k] = f[p][k - 1];
    }
  }
}
for (int i = 0; i < Q; i++) {
  int x, k; cin >> x >> k;
  x--;
  for (int j = 0; j < K; j++) {
    if (k >> j & 1) {
      x = f[x][j];
      if (x < 0) break;
    }
  }
}
// 6: lca f[u] + f[v] - 2*f[lca(u, v)]
// 7: turn subtree into interval
std::function<void(int, int)> dfs = [&](int u, int p) {
  enter[u] = cnt++;
  for (int v : g[u]) {
    if (v == p) continue;
    dfs(v, u);
  }
  leave[u] = cnt++;
};
dfs(0, -1);
Bit<ll> bit(cnt);
for (int i = 0; i < N; i++) {
  bit.add(enter[i], A[i]);
}
trace(cnt, enter, leave);
for (int i = 0; i < Q; i++) {
  int op; cin >> op;
  if (op == 1) {
    int s; ll x; cin >> s >> x;
    s--;
    s = enter[s];
    bit.add(s, x - bit.query(s, s + 1));
  }
  else {
    int s; cin >> s;
    s--;
    cout << bit.query(enter[s], leave[s] + 1) << "\n";
  }
}

//
//------------------------------------------------------------------------------
// Dijkstra shortest path
void dijkstra(int root) {
  vector<int> dist(n, INF);
  priority_queue<ar, vector<ar>> qu;
  dist[root] = 0;
  qu.push_back({0, root});
  while (qu.size()) {
    auto tp = qu.top(); qu.pop();
    int d = -tp[0], u = tp[1];
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

// -----------------------------------------------------------------------------
// weight DP
// Complexity: O(nc)
//
// F[a] := maximum profit for weight >= a
//
// f[i][x] = max(f[i-1][x], f[i-1][x-w] + p)
int knapsackW(vector<int> p, vector<int> w, int c) {
  int n = w.size();
  vector<int> F(c + 1);
  for (int i = 0; i < n; ++i)
    for (int a = c; a >= w[i]; --a)
      F[a] = max(F[a], F[a-w[i]] + p[i]);
  return F[c];
}

// Profit DP
// Complexity: O(n sum p)
//
// F[a] := minimum weight for profit a
//
// f[i][a] == min(f[i-1][a], f[i-1][a - p] + w)
int knapsackP(vector<int> p, vector<int> w, int c) {
  int n = p.size(), P = accumulate(all(p), 0);
  vector<int> F(P+1, c+1);
  F[0] = 0;
  for (int i = 0; i < n; ++i)
    for (int a = P; a >= p[i]; --a)
      F[a] = min(F[a], F[a-p[i]] + w[i]);
  for (int a = P; a >= 0; --a)
    if (F[a] <= c) return a;
}

// 1 2 3 4 5 6 7
// The number of ways to get the sum `s` using the first `i` numbers.
// f[i][s] = f[i - 1][s] + f[i - 1][s - ai]

// the maxinum value if the last is `i`th for something
// f[i] = max(f[j]) + wi (j < i)

// interval dp
for (int len = 2; len <= N; len++) {
  for (int l = 1; l + len - 1 <= N; l++) {
    int r = l + len - 1;
    f[l][r] = INF;
    for (int k = l; k < r; k++) {
      amin(f[l][r], f[l][k] + f[k + 1][r] + s[r] - s[l - 1]);
    }
  }
}

// -----------------------------------------------------------------------------
// 1. z function
// An element Z[i] of Z array stores length of the longest substring
// starting from str[i] which is also a prefix of str[0..n-1].

// 2. string hash

