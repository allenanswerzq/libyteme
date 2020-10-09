// Zero-indexed segment tree
template <typename T>
struct Segtree {
  int n;
  vector<T> tree;

  void build(int x, int l, int r) {
    if (l + 1 == r) {
      return;
    }
    int y = l + (r - l) / 2;
    build(x << 1, l, y);
    build(x << 1 | 1, y, r);
    T::pull_up(tree, x);
  }

  template <typename U>
  void build(int x, int l, int r, const vector<U>& v) {
    if (l + 1 == r) {
      assert(0 <= l && l < (int)v.size());
      tree[x].apply(l, r, v[l]);
      return;
    }
    int y = l + (r - l) / 2;
    build(x << 1, l, y, v);
    build(x << 1 | 1, y, r, v);
    T::pull_up(tree, x);
  }

  T query(int x, int l, int r, int lx, int rx) {
    if (rx <= l || r <= lx) {
      return T{};
    }
    if (lx <= l && r <= rx) {
      return tree[x];
    }
    T::push_down(tree, x, l, r);
    int y = l + (r - l) / 2;
    T left = query(x << 1, l, y, lx, rx);
    T right = query(x << 1 | 1, y, r, lx, rx);
    T res = T::combine(left, right);
    T::pull_up(tree, x);
    return res;
  }

  // NOTE: [lx, rx) denotes the interval need to be modified.
  template <typename U>
  void modify(int x, int l, int r, int lx, int rx, const U& v) {
    if (rx <= l || r <= lx) {
      // No cover at all.
      // [lx, rx)  [l ... r)  [lx, rx)
      // ___________________
      //         ____________________
      return;
    }
    if (lx <= l && r <= rx) {
      // Full cover.
      // [lx_________________rx)
      //     (x)[l------r)
      tree[x].apply(l, r, v);
      return;
    }
    int y = l + (r - l) / 2;
    T::push_down(tree, x, l, r);
    if (lx < y) {
      // Partial cover left child.
      //        [lx______rx)
      //  (x)[l_______y_______r)
      modify(x << 1, l, y, lx, rx, v);
    }
    if (rx > y) {
      // Partial cover right child.
      //     [lx_______________rx)
      //          (x)[l________y________r)
      modify(x << 1 | 1, y, r, lx, rx, v);
    }
    T::pull_up(tree, x);
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

  T query(int lx, int rx) {
    assert(0 <= lx && lx < rx && rx <= n);
    return query(1, 0, n, lx, rx);
  }

  template <typename M>
  void modify(int lx, int rx, const M& v) {
    assert(0 <= lx && lx < rx && rx <= n);
    modify(1, 0, n, lx, rx, v);
  }
};

struct Node {
  int lmax = -INF;
  int rmax = -INF;
  int sum = 0;
  int ans = -INF;

  // NOTE: each Node denotes an interval [l, r).
  void apply(int l, int r, int v) { lmax = rmax = sum = ans = v; }

  static Node combine(const Node& a, const Node& b) {
    Node res;
    res.sum = a.sum + b.sum;
    // (_______ ____)____
    res.lmax = max(a.lmax, a.sum + b.lmax);
    // ___(____ ________)
    res.rmax = max(b.rmax, b.sum + a.rmax);
    // ___(___ ____)_____
    res.ans = max({a.ans, b.ans, a.rmax + b.lmax});
    return res;
  }

  static void push_down(vector<Node>& tree, int x, int l, int r) {}

  static void pull_up(vector<Node>& tree, int x) {
    tree[x] = combine(tree[x << 1], tree[x << 1 | 1]);
  }
};
