// Compute the mobius value for a number.
int mobius(int n) {
  if (n == 0) {
    return 0;
  }
  int ans = 1;
  for (int x = 2; x * x <= n; x++) {
    if (n % x == 0) {
      // Found a prime factor
      ans = -ans;
      n /= x;
      if (n % x == 0) {
        // x is a square prime factor
        return 0;
      }
    }
  }
  if (n > 1) {
    // n is still a prime factor
    ans = -ans;
  }
  return ans;
}

// Compute the all mobius values for interval [1, N)
// Time complixity: O(N)
template <int N>
vector<int> mobius() {
  vector<int> pr;
  vector<int> lp(N);
  vector<int> ans(N);
  ans[1] = 1;
  for (int i = 2; i < N; i++) {
    if (lp[i] == 0) {
      // This number is a prime number.
      lp[i] = i;
      pr.push_back(i);
      // Set to -1 as it only has odd number of primes
      ans[i] = -1;
    }
    for (int j = 0; j < (int) pr.size() && pr[j] <= lp[i] && i * pr[j] < N; j++) {
      int k = i * pr[j];
      assert(k < N);
      lp[k] = pr[j];
      if (pr[j] == lp[i]) {
        // i * pr[j] will have square primes
        ans[k] = 0;
      }
      else {
        ans[k] = -ans[i];
      }
    }
  }
  return ans;
}

