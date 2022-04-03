// Time complexity: O(n)
template <int N>
vector<int> sieve() {
  // Every number can be represented as i = lp[i] * x,
  // where lp[i] is the mininum prime factor, thus lp[i] <= lp[x]
  vector<int> lp(N);
  vector<int> pr;
  for (int i = 2; i < N; i++) {
    if (lp[i] == 0) {
      // i is a prime number
      lp[i] = i;
      pr.push_back(i);
    }
    // Now, we know the mininum prime factor for i is lp[i]
    for (int j = 0; j < (int) pr.size() && pr[j] <= lp[i] && i * pr[j] < N; j++) {
      lp[i * pr[j]] = pr[j];
    }
  }
  return pr;
}

// time complexity: O(nlogn)
template <int N>
bitset<N> sieve() {
  bitset<N> bs;
  bs.set();
  bs[0] = 0;
  bs[1] = 0;
  for (int i = 2; i < N; i++) {
    if (bs[i] == 1) {
      for (int j = i + i; j < N; j += i) {
        bs[j] = 0;
      }
    }
  }
  return bs;
}

template <int N>
vector<int> get_prime() {
  vector<int> prime;
  auto bs = sieve<N>();
  for (int i = 1; i < N; i++) {
    if (bs.test(i)) {
      prime.push_back(i);
    }
  }
  return prime;
}

// time complexity: O(sqrt(n))
// number of prime pactors: O(log(n))
template <class T>
vector<int> prime_factor(T n) {
  vector<int> fact;
  for (T i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      fact.push_back(i);
      while (n % i == 0) {
        n /= i;
      }
    }
  }
  if (n > 1) {
    fact.push_back(n);
  }
  return fact;
}

// Linear sieve algorithm
template <int N>
vector<int> sieve() {
  // Every number can be represented as i = lp[i] * x,
  // where lp[i] is the mininum prime factor, thus lp[i] <= lp[x]
  vector<int> lp(N);
  vector<int> pr;
  for (int i = 2; i < N; i++) {
    if (lp[i] == 0) {
      // i is a prime number
      lp[i] = i;
      pr.push_back(i);
    }
    trace(i);
    // Now, we know the mininum prime factor for i is lp[i]
    for (int j = 0; j < (int) pr.size() && pr[j] <= lp[i] && i * pr[j] < N; j++) {
      trace(i, i * pr[j]);
      lp[i * pr[j]] = pr[j];
    }
  }
  return pr;
}
