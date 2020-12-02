// Zero-index based
template <class T>
class Bit {
 public:
  Bit(int n) : n_(n) { t_.resize(n_ + 1); }

  void add(int x, int d) {
    for (++x; x <= n_; x += lowbit(x)) {
      t_[x] += d;
    }
  }

  // Query sum of interval [0...x].
  T query(int x) {
    T ans = 0;
    for (++x; x > 0; x -= lowbit(x)) {
      ans += t_[x];
    }
    return ans;
  }

  T query(int l, int r) { return query(r) - query(l - 1); }

 private:
  int lowbit(int x) { return x & -x; }
  int n_;
  vector<T> t_;
};

// 2d Bit: Zero-index based
template <class T>
class Bit {
 public:
  Bit(int n, int m) : n_(n), m_(m) { t_.resize(n_ + 1, vector<T>(m_ + 1)); }

  void add(int x, int y, int d) {
    for (++x; x <= n_; x += lowbit(x)) {
      int y1 = y;
      for (++y1; y1 <= m_; y1 += lowbit(y1)) {
        t_[x][y1] += d;
      }
    }
  }

  // Query sum of interval [0...x].
  T query(int x, int y) {
    T ans = 0;
    for (++x; x > 0; x -= lowbit(x)) {
      int y1 = y;
      for (++y1; y1 > 0; y1 -= lowbit(y1)) {
        ans += t_[x][y1];
      }
    }
    return ans;
  }

  T query(int x1, int y1, int x2, int y2) {
    x1--, y1--;
    return query(x2, y2) - query(x1, y2) - query(x2, y1) + query(x1, y1);
  }

 private:
  int lowbit(int x) { return x & -x; }
  int n_, m_;
  vector<vector<T>> t_;
};
