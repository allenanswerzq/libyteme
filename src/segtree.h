struct Segtree {
  struct node {
    ll sum = 0;
    ll z0 = 0;
    ll z1 = 0;

    void apply(int l, int r, ll x0, ll x1, int d) {
      r--;
      // [a ... ...           b]
      //       [l2 ... r2]
      // l2 - a + 1, l2 - a + 2, ... l2 - a + r2 - l2 + 1
      // ==> (1 - a) * (r2 - l2 + 1) + (l2 + l2 + 1, ..., r2)
      sum += d + (ll) (r - l + 1) * x0 + x1 * ((ll) r * (r + 1) / 2 - (ll) l * (l - 1) / 2);
      z0 += x0;
      z1 += x1;
    }
  };

  node unite(const node& a, const node& b) const {
    return node{a.sum + b.sum, 0, 0};
  }

  inline void push_down(int x, int l, int r) {
    int md = l + (r - l) / 2;
    tree[x << 1].apply(l, md, tree[x].z0, tree[x].z1, 0);
    tree[x << 1 | 1].apply(md, r, tree[x].z0, tree[x].z1, 0);
    tree[x].z0 = 0;
    tree[x].z1 = 0;
  }

  inline void pull_up(int x) {
    tree[x] = unite(tree[x << 1], tree[x << 1 | 1]);
  }

  int n;
  vector<node> tree;

  void build(int x, int l, int r) {
    if (l + 1 == r) {
      return;
    }
    int y = l + (r - l) / 2;
    build(x << 1, l, y);
    build(x << 1 | 1, y, r);
    pull_up(x);
  }

  template <typename U>
  void build(int x, int l, int r, const vector<U>& v) {
    if (l + 1 == r) {
      assert(0 <= l && l < (int) v.size());
      tree[x].apply(l, r, v[l]);
      return;
    }
    int y = l + (r - l) / 2;
    build(x << 1, l, y, v);
    build(x << 1 | 1, y, r, v);
    pull_up(x);
  }

  node query_impl(int x, int l, int r, int lx, int rx) {
    if (rx <= l || r <= lx) {
      return node{};
    }
    if (lx <= l && r <= rx) {
      return tree[x];
    }
    push_down(x, l, r);
    int y = l + (r - l) / 2;
    node left = query_impl(x << 1, l, y, lx, rx);
    node right = query_impl(x << 1 | 1, y, r, lx, rx);
    node res = unite(left, right);
    pull_up(x);
    return res;
  }

  void debug_impl(int x, int l, int r, int lx, int rx, int level = 1) {
    if (rx <= l || r <= lx) {
      return;
    }
    if (l + 1 < r) {
      push_down(x, l, r);
    }
    if (lx <= l && r <= rx) {
      cerr << string(level, ' ') << l << "->" << r << " "
           << tree[x].sum << " " << tree[x].z0 << " " << tree[x].z1 << "\n";
    }
    if (l + 1 < r) {
      int y = l + (r - l) / 2;
      debug_impl(x << 1, l, y, lx, rx, 2 * level);
      debug_impl(x << 1 | 1, y, r, lx, rx, 2 * level);
      pull_up(x);
    }
  }

  template <typename ...U>
  void modify_impl(int x, int l, int r, int lx, int rx, const U&... v) {
    if (rx <= l || r <= lx) {
      return;
    }
    if (lx <= l && r <= rx) {
      tree[x].apply(l, r, v...);
      return;
    }
    int y = l + (r - l) / 2;
    push_down(x, l, r);
    if (lx < y) {
      modify_impl(x << 1, l, y, lx, rx, v...);
    }
    if (rx > y) {
      modify_impl(x << 1 | 1, y, r, lx, rx, v...);
    }
    pull_up(x);
  }

  int ceil_pow2(int x) {
    int t = 1;
    while (t < x) {
      t <<= 1;
    }
    return t;
  }

  Segtree(int n_) : n(ceil_pow2(n_)) {
    tree.resize(2 * n);
    build(1, 0, n);
  }

  template <typename M>
  Segtree(vector<M>& v) : n(ceil_pow2(v.size())) {
    tree.resize(2 * n);
    v.resize(n);
    build(1, 0, n, v);
  }

  node query(int lx, int rx) {
    assert(0 <= lx && lx <= rx && rx <= n);
    return query_impl(1, 0, n, lx, rx);
  }

  template <typename ...M>
  void modify(int lx, int rx, const M&... v) {
    assert(0 <= lx && lx <= rx && rx <= n);
    modify_impl(1, 0, n, lx, rx, v...);
  }

  void debug() {
    debug_impl(1, 0, n, 0, n);
  }
};

// --------------------------------------------------------------
// Without use lazy property
struct Segtree {
  struct node {
    ll pre_sum = 0;
    ll tot_sum = 0;
    int pre_len = 0;
    int tot_len = 0;

    void apply(int l, int r, int val) {
      pre_sum = val;
      tot_sum = val;
      pre_len = 1;
      tot_len = r - l;
    }

    string debug_string() {
      return to_string(pre_sum) + " " + to_string(pre_len) + " " + to_string(tot_len);
    }
  };

  node unite(const node& a, const node& b) const {
    node res;
    if (a.pre_len == a.tot_len) {
      assert(a.pre_sum == a.tot_sum);
      res.pre_sum = max({a.pre_sum, a.tot_sum + b.pre_sum});
      if (res.pre_sum == a.pre_sum) {
        res.pre_len = a.pre_len;
      }
      else {
        res.pre_len = a.tot_len + b.pre_len;
      }
    }
    else {
      res.pre_sum = max({a.pre_sum, a.tot_sum + b.pre_sum});
      if (res.pre_sum == a.pre_sum) {
        res.pre_len = a.pre_len;
      }
      else {
        res.pre_len = a.tot_len + b.pre_len;
      }
    }
    res.tot_len = a.tot_len + b.tot_len;
    res.tot_sum = a.tot_sum + b.tot_sum;
    return res;
  }

  inline void push_down(int x, int l, int r) {
    (void)x;
    (void)l;
    (void)r;
  }

  inline void pull_up(int x) {
    tree[x] = unite(tree[x << 1], tree[x << 1 | 1]);
  }

  int n;
  vector<node> tree;

  void build(int x, int l, int r) {
    if (l + 1 == r) {
      return;
    }
    int y = l + (r - l) / 2;
    build(x << 1, l, y);
    build(x << 1 | 1, y, r);
    pull_up(x);
  }

  template <typename U>
  void build(int x, int l, int r, const vector<U>& v) {
    if (l + 1 == r) {
      assert(0 <= l && l < (int) v.size());
      tree[x].apply(l, r, v[l]);
      return;
    }
    int y = l + (r - l) / 2;
    build(x << 1, l, y, v);
    build(x << 1 | 1, y, r, v);
    pull_up(x);
  }

  node query_impl(int x, int l, int r, int lx, int rx) {
    if (rx <= l || r <= lx) {
      return node{};
    }
    if (lx <= l && r <= rx) {
      return tree[x];
    }
    push_down(x, l, r);
    int y = l + (r - l) / 2;
    node left = query_impl(x << 1, l, y, lx, rx);
    node right = query_impl(x << 1 | 1, y, r, lx, rx);
    node res = unite(left, right);
    pull_up(x);
    return res;
  }

  void debug_impl(int x, int l, int r, int lx, int rx, int level = 1) {
    if (rx <= l || r <= lx) {
      return;
    }
    if (l + 1 < r) {
      push_down(x, l, r);
    }
    if (lx <= l && r <= rx) {
      cerr << string(level, ' ')
           << l << "->" << r << " ("
           << tree[x].debug_string()
           << ")\n";
    }
    if (l + 1 < r) {
      int y = l + (r - l) / 2;
      debug_impl(x << 1, l, y, lx, rx, 2 * level);
      debug_impl(x << 1 | 1, y, r, lx, rx, 2 * level);
      pull_up(x);
    }
  }

  template <typename ...U>
  void modify_impl(int x, int l, int r, int lx, int rx, const U&... v) {
    if (rx <= l || r <= lx) {
      return;
    }
    if (lx <= l && r <= rx) {
      tree[x].apply(l, r, v...);
      return;
    }
    int y = l + (r - l) / 2;
    push_down(x, l, r);
    if (lx < y) {
      modify_impl(x << 1, l, y, lx, rx, v...);
    }
    if (rx > y) {
      modify_impl(x << 1 | 1, y, r, lx, rx, v...);
    }
    pull_up(x);
  }

  int ceil_pow2(int x) {
    int t = 1;
    while (t < x) {
      t <<= 1;
    }
    return t;
  }

  Segtree(int n_) : n(ceil_pow2(n_)) {
    tree.resize(2 * n);
    build(1, 0, n);
  }

  template <typename M>
  Segtree(vector<M>& v) : n(ceil_pow2(v.size())) {
    tree.resize(2 * n);
    v.resize(n);
    build(1, 0, n, v);
  }

  node query(int lx, int rx) {
    assert(0 <= lx && lx <= rx && rx <= n);
    return query_impl(1, 0, n, lx, rx);
  }

  template <typename ...M>
  void modify(int lx, int rx, const M&... v) {
    assert(0 <= lx && lx <= rx && rx <= n);
    modify_impl(1, 0, n, lx, rx, v...);
  }

  void debug() {
#ifdef LOCAL
    debug_impl(1, 0, n, 0, n);
#endif
  }
};

// --------------------------------------------------------------
struct Node {
  Node* left = nullptr;
  Node* right = nullptr;
  ll val = 0;
  int l = 0;
  int r = 0;

  Node() {}
  Node(ll x, int lo, int hi) : val(x), l(lo), r(hi) {}

  // denotes an interval [l, r)
  void apply(int lo, int hi, int x) {
    l = lo;
    r = hi;
    val += (hi - lo) * x;
    trace(this, l, r, val);
  }

  string debug_string() {
    ostringstream oss;
    oss << "(" << l << "," << r << "," << val << "," << ")";
    return oss.str();
  }

  void unite(Node* lhs, Node* rhs) {
    this->val = lhs->val + rhs->val;
    this->l = lhs->l;
    this->r = rhs->r;
  }
};

struct PersistentSegTree {
  int n;

  int ceil_pow2(int x) {
    int t = 1;
    while (t < x) {
      t <<= 1;
    }
    return t;
  }

  Node* build(vector<int>& v) {
    n = ceil_pow2((int) v.size());
    v.resize(n);
    return build(v, 0, n);
  }

  void pull_up(Node* cur) { cur->unite(cur->left, cur->right); }

  Node* build(vector<int>& v, int l, int r) {
    if (l + 1 == r) {
      return new Node(v[l], l, r);
    }
    int y = l + (r - l) / 2;
    Node* root = new Node();
    root->left = build(v, l, y);
    root->right = build(v, y, r);
    pull_up(root);
    return root;
  }

  ll query_impl(Node* cur, int l, int r, int lx, int rx) {
    assert(cur);
    if (rx <= l || r <= lx) {
      return 0;
    }
    if (lx <= l && r <= rx) {
      return cur->val;
    }
    // push_down(x, l, r);
    int y = l + (r - l) / 2;
    ll left = query_impl(cur->left, l, y, lx, rx);
    ll right = query_impl(cur->right, y, r, lx, rx);
    ll res = left + right;
    pull_up(cur);
    return res;
  }

  void modify_impl(Node* pre, Node* cur, int l, int r, int lx, int rx, int x) {
    // [l, r)
    if (rx <= l || r <= lx) {
      return;
    }
    if (lx <= l && r <= rx) {
      cur->apply(l, r, x);
      return;
    }
    // push_down(cur, l, r, x);
    trace(pre, cur, l, r, lx, rx, x);
    assert(pre);
    int y = l + (r - l) / 2;
    if (lx < y) {
      cur->left = new Node();
      modify_impl(pre->left, cur->left, l, y, lx, rx, x);
    }
    else {
      cur->left = pre->left;
    }
    if (rx > y) {
      cur->right = new Node();
      modify_impl(pre->right, cur->right, y, r, lx, rx, x);
    }
    else {
      cur->right = pre->right;
    }
    pull_up(cur);
  }

  void debug_impl(Node* cur, int l, int r, int lx, int rx, int level = 1) {
    if (rx <= l || r <= lx) {
      return;
    }
    // if (l + 1 < r) {
    //   push_down(x, l, r);
    // }
    if (lx <= l && r <= rx) {
      assert(cur);
      cerr << string(level, ' ') << l << "->" << r
           << " (" << cur->debug_string() << ")\n";
    }
    if (l + 1 < r) {
      int y = l + (r - l) / 2;
      debug_impl(cur->left, l, y, lx, rx, 2 * level);
      debug_impl(cur->right, y, r, lx, rx, 2 * level);
      // pull_up(cur);
    }
  }

  void modify(Node * pre, Node* cur, int lx, int rx, int x) {
    assert(pre && cur && 0 <= lx && lx <= rx && rx <= n);
    modify_impl(pre, cur, 0, n, lx, rx, x);
  }

  ll query(Node * cur, int lx, int rx) {
    assert(0 <= lx && lx <= rx && rx <= n);
    return query_impl(cur, 0, n, lx, rx);
  }

  void debug(Node* cur) {
#ifdef LOCAL
    debug_impl(cur, 0, n, 0, n);
#endif
  }
};

void solve() {
  int N, Q; cin >> N >> Q;
  vector<int> A(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
  }
  PersistentSegTree seg;
  map<int, Node*> versions;
  int array_idx = 0;
  versions[array_idx] = seg.build(A);
  for (int i = 0; i < Q; i++) {
    int op; cin >> op;
    if (op == 1) {
      int k, a, x; cin >> k >> a >> x;
      k--, a--;
      Node* cur = new Node();
      seg.modify(versions[k], cur, a, a + 1, x);
      versions[k] = cur;
      seg.debug(cur);
    }
    else if (op == 2) {
      int k, a, b; cin >> k >> a >> b;
      k--, a--;
      trace(i, k, a, b, versions);
      assert(versions[k]);
      cout << seg.query(versions[k], a, b) << "\n";
    }
    else {
      int k; cin >> k;
      k--;
      array_idx++;
      versions[array_idx] = versions[k];
    }
  }
}
