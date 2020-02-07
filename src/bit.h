#include <bits/stdc++.h>
using namespace std;

template <class T>
struct Bit {
  // Zero index based binary index tree.
  int n;
  vector<T> bt;

  Bit(int n_) : n(n_ + 1) { bt.resize(n); }

  Bit(const vector<T>& v) {
    n = v.size() + 1;
    bt.resize(n);
    for (int i = 0; i < n - 1; i++) {
      add(i, v[i]);
    }
  }

  // Adds the val k to the ith position
  void add(int i, int k) {
    for (++i; i < n; i += i & (-i)) {
      bt[i] += k;
    }
  }

  // Returns the sum from index 0 to i
  T query(int i) {
    T res = 0;
    for (++i; i > 0; i -= i & (-i)) {
      res += bt[i];
    }
    return res;
  }

  // Queries an interval for zero based indexes
  T query(int x, int y) {
    assert(0 <= x && x < n - 1);
    assert(0 <= y && y < n - 1);
    return query(y) - (x - 1 >= 0 ? query(x - 1) : 0);
  }
};
