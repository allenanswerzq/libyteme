#include <bits/stdc++.h>
using namespace std;

// Link SO: c-why-is-boosthash-combine-the-best-way-to-combine-hash-values
size_t hash_combine(const size_t& a, const size_t& b) {
  return a ^ (b + 0x9e3779b9 + (a << 6) + (a >> 2) );
}

namespace std {
template <>
struct hash<vector<int>> {
  size_t operator()(const vector<int>& v) const {
    size_t seed = v.size();
    for (auto x : v) {
      seed ^= x + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }
    return seed;
  }
};
}

template <int N>
struct HashString {
  using ull = unsigned long long;
  const int base = 131;
  vector<ull> hash;
  vector<ull> hash_rev; // reverse hash
  vector<ull> mul;
  int n = 0;

  void init() {
    hash.resize(N);
    hash_rev.resize(N);
    mul.resize(N);
    mul[0] = 1;
    for (int i = 1; i < N; i++) {
      mul[i] = mul[i - 1] * base;
    }
  }

  HashString() { init(); }

  HashString(const string& s) {
    init();
    append(s);
  }

  // Given zero based index, returns the hash value.
  ull get(int l, int r) {
    assert(0 <= l && l <= r && r < n);
    return hash[r + 1] - hash[l] * mul[r - l + 1];
  }

  int reverse_index(int x) {
    assert(0 <= x && x < n);
    return n - x - 1;
  }

  ull get_rev(int l, int r) {
    assert(1 <= l && l <= r);
    int nl = reverse_index(r);
    int nr = reverse_index(l);
    return hash_rev[nr + 1] - hash_rev[nl] * mul[r - l + 1];
  }

  void append(const string& s) {
    int l = s.size();
    for (int i = 0; i < l; i++) {
      hash[n + 1 + i] = hash[n + i] * base + s[i] - 'a';
      hash_rev[n + 1 + i] = hash_rev[n + i] * base + s[l - i - 1] - 'a';
    }
    n += l;
  }
};
