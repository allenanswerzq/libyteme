// Zero-indexed segment tree
class segtree {
public:
  struct node {
    int add = 0;
    int sum = 0;

    // Each node denotes an interval [l, r).
    void apply(int l, int r, int v) {
      add += v;
      sum += v * (r - l);
    }

    friend ostream& operator<<(ostream& os, node& a) {
      os << "node(" << a.add << ", " << a.sum << ")";
      return os;
    }
  };

  node unite(const node& a, const node& b) {
    node res;
    res.sum = a.sum + b.sum;
    return res;
  }

  void push(int x, int l, int r) {
    int y = l + (r - l) / 2;
    if (tree[x].add != 0) {
      tree[x << 1].apply(l, y, tree[x].add);
      tree[x << 1 | 1].apply(y, r, tree[x].add);
      tree[x].add = 0;
    }
  }

  void pull(int x) {
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
    pull(x);
  }

  template <typename M>
  void build(int x, int l, int r, const vector<M>& v) {
    if (l + 1 == r) {
      assert(0 <= l && l < (int) v.size());
      tree[x].apply(l, r, v[l]);
      return;
    }
    int y = l + (r - l) / 2;
    build(x << 1, l, y, v);
    build(x << 1 | 1, y, r, v);
    pull(x);
  }

  node get(int x, int l, int r, int lx, int rx) {
    if (rx <= l || r <= lx) {
      return node{};
    }
    if (lx <= l && r <= rx) {
      return tree[x];
    }
    push(x, l, r);
    int y = l + (r - l) / 2;
    node res = unite(get(x << 1, l, y, lx, rx), get(x << 1 | 1, y, r, lx, rx));
    pull(x);
    return res;
  }

  template <typename... M>
  void modify(int x, int l, int r, int lx, int rx, const M&... v) {
    if (rx <= l || r <= lx) {
      return;
    }
    if (lx <= l && r <= rx) {
      tree[x].apply(l, r, v...);
      return;
    }
    int y = l + (r - l) / 2;
    push(x, l, r);
    if (lx < y) {
      modify(x << 1, l, y, lx, rx, v...);
    }
    if (rx > y) {
      modify(x << 1 | 1, y, r, lx, rx, v...);
    }
    pull(x);
  }

  int get_size(int x) {
    int t = 1;
    while (t < x) {
      t <<= 1;
    }
    return t;
  }

  segtree(int n_) : n(n_) {
    n = get_size(n);
    tree.resize(2 * n);
    build(1, 0, n);
  }

  template <typename M>
  segtree(const vector<M>& v) {
    n = get_size((int) v.size());
    tree.resize(2 * n);
    vector<M> t = v;
    t.resize(n);
    build(1, 0, n, t);
  }

  node get(int lx, int rx) {
    assert(0 <= lx && lx <= rx && rx <= n);
    return get(1, 0, n, lx, rx);
  }

  node get(int p) {
    assert(0 <= p && p <= n);
    return get(1, 0, n, p, p + 1);
  }

  template <typename... M>
  void modify(int lx, int rx, const M&... v) {
    assert(0 <= lx && lx <= rx && rx <= n);
    modify(1, 0, n, lx, rx, v...);
  }
};

