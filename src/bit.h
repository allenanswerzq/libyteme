#include <bits/stdc++.h>
using namespace std;

// One-index based
template <class T>
struct Bit {
  vector<T> t;
  int n;

  int lowbit(int x) { return x & -x; }

  Bit(int n_): n(n_) {
    t.resize(n + 1);
  }

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

  T query(int l, int r) {
    return query(r) - query(l - 1);
  }
};

