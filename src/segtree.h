#include <bits/stdc++.h>
using namespace std;

// Zero-indexed segment tree
class Segtree {
public:
  struct node {
    long long add = 0;
    long long sum = 0;

    // NOTE: each node denotes an interval [l, r).
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

  void push_down(int x, int l, int r) {
    int y = l + (r - l) / 2;
    if (tree[x].add != 0) {
      tree[x << 1].apply(l, y, tree[x].add);
      tree[x << 1 | 1].apply(y, r, tree[x].add);
      tree[x].add = 0;
    }
  }

  void pull_up(int x) {
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
    pull_up(x);
  }

  node query(int x, int l, int r, int lx, int rx) {
    if (rx <= l || r <= lx) {
      return node{};
    }
    if (lx <= l && r <= rx) {
      return tree[x];
    }
    push_down(x, l, r);
    int y = l + (r - l) / 2;
    node left = query(x << 1, l, y, lx, rx);
    node right = query(x << 1 | 1, y, r, lx, rx);
    node res = unite(left, right);
    pull_up(x);
    return res;
  }

  template <typename M>
  void modify(int x, int l, int r, int lx, int rx, const M& v) {
    if (rx <= l || r <= lx) {
      return;
    }
    if (lx <= l && r <= rx) {
      tree[x].apply(l, r, v);
      return;
    }
    int y = l + (r - l) / 2;
    push_down(x, l, r);
    if (lx < y) {
      modify(x << 1, l, y, lx, rx, v);
    }
    if (rx > y) {
      modify(x << 1 | 1, y, r, lx, rx, v);
    }
    pull_up(x);
  }

  int big(int x) {
    int t = 1;
    while (t < x) {
      t <<= 1;
    }
    return t;
  }

  Segtree(int n_) : n(n_) {
    n = big(n);
    tree.resize(2 * n);
    build(1, 0, n);
  }

  template <typename M>
  Segtree(const vector<M>& v) {
    n = big((int) v.size());
    tree.resize(2 * n);
    vector<M> t = v;
    t.resize(n);
    build(1, 0, n, t);
  }

  node query(int lx, int rx) {
    assert(0 <= lx && lx < rx && rx <= n);
    return query(1, 0, n, lx, rx);
  }

  node query(int p) {
    assert(0 <= p && p < n);
    return query(1, 0, n, p, p + 1);
  }

  template <typename M>
  void modify(int lx, int rx, const M& v) {
    assert(0 <= lx && lx < rx && rx <= n);
    modify(1, 0, n, lx, rx, v);
  }

  template <typename M>
  void modify(int lx, const M& v) {
    assert(0 <= lx && lx < n);
    modify(1, 0, n, lx, lx + 1, v);
  }

  template <typename M>
  void set(int lx, const M& v) {
    assert(0 <= lx && lx < n);
    modify(lx, v - query(lx).sum);
  }
};

