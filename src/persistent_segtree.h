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
