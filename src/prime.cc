template <int N>
bitset<N> sieve() {
  bitset<N> bs;
  bs.set();
  bs[0] = 0;
  bs[1] = 0;
  for (int i = 2; i < N; i++) {
    if (bs.test(i)) {
      for (int j = i + i; j < N; j += i) {
        bs.reset(j);
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
