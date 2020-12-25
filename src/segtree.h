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
