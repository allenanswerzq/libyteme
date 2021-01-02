#include <bits/stdc++.h>
using namespace std;

// Link SO: c-why-is-boosthash-combine-the-best-way-to-combine-hash-values
size_t hash_combine(const size_t& a, const size_t& b) {
  return a ^ (b + 0x9e3779b9 + (a << 6) + (a >> 2));
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
}  // namespace std
