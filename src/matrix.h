template <class T>
struct Matrix {
  vector<vector<T>> v_;
  int n_;
  int m_;

  Matrix(int n, int m) : n_(n), m_(m) {
    v_.resize(n_, vector<T>(m_));
  }

  Matrix(const Matrix& o) {
    *this = o;
  }

  vector<T>& operator[](int r) {
    assert(0 <= r && r < n_);
    return v_[r];
  }

  void operator=(const Matrix& o) {
    v_ = o.v_;
    n_ = o.n_;
    m_ = o.m_;
  }

  void debug() {
    trace(v_);
  }

  Matrix& operator*=(const Matrix& o) {
    assert(m_ == o.n_);
    Matrix ans(n_, o.m_);
    for (int i = 0; i < n_; i++) {
      for (int j = 0; j < o.m_; j++) {
        T cur = 0;
        for (int k = 0; k < m_; k++) {
          cur += v_[i][k] * o.v_[k][j];
        }
        ans.v_[i][j] = cur;
      }
    }
    *this = ans;
    return *this;
  }

  Matrix operator^(ll t) {
    assert(t >= 0);
    assert(n_ == m_);
    Matrix ans(n_, m_);
    for (int i = 0; i < n_; i++) {
      ans.v_[i][i] = 1;
    }
    Matrix a(*this);
    while (t) {
      if (t & 1) ans *= a;
      a *= a;
      t >>= 1;
    }
    return ans;
  }

  friend Matrix operator*(const Matrix& a, const Matrix& b) { return Matrix(a) *= b; }
};
