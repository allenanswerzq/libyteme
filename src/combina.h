#include <bits/stdc++.h>
using namespace std;

template <class T>
struct combina_large_t {
// NOTE: T must suports number inverse opertion
  vector<T> fact;
  vector<T> fact_inv;

  explicit combina_large_t(int n) {
    fact.resize(n + 1);
    fact_inv.resize(n + 1);
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) {
      fact[i] = fact[i - 1] * i;
    }
    fact_inv[n] = fact[n].inv();
    for (int i = n - 1; i >= 0; --i) {
      fact_inv[i] = fact_inv[i + 1] * i;
    }
  }

  // Choose k from total n items without permutation
  int nck(int n, int k) {
    return (*this)(n, k);
  }

  // Choose k from total n items with permutation
  int npk(int n, int k) {
    // nPk = nCk * k!
    T ret = nck(n, k);
    ret *= fact[k];
    return (int)ret;
  }

  int operator() (int n, int k) {
    if (k < 0 || n < k) {
      return int(T(0));
    }
    return int(fact[n] * fact_inv[k] * fact_inv[n - k]);
  }
};

struct combina_t {
// Compute cominatrics for a relative small range up to 10^3
  vector<vector<int>> dp;

  // c(n, k) = c(n - 1, k) + c(n - 1, k - 1);
  explicit combina_t(int n) {
    dp.resize(n + 1, vector<int>(n + 1));
    for (int i = 0; i <= n; i++) {
      dp[i][0] = 1;
    }
    for (int i = 1; i <= n; i++) {
      for (int k = 1; k <= i; k++) {
        dp[i][k] = dp[i - 1][k] + dp[i - 1][k - 1];
      }
    }
  }

  // Choose k from total n items without permutation
  int nck(int n, int k) {
    return (*this)(n, k);
  }

  // Choose k from total n items without permutation
  int operator() (int n, int k) {
    return dp[n][k];
  }
};
