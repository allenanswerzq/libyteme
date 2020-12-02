#include <bits/stdc++.h>
using namespace std;

// Taken from https://codeforces.com/contest/1151/submission/52973403
template <int mod_>
struct Modnum {
  static constexpr int mod = mod_;
  static_assert(mod_ > 0, "mod must be positive");

  typedef Modnum MD;

 private:
  using ll = long long;
  int v;

  static int inv(int a, int m) {
    a %= m;
    assert(a);
    return a == 1 ? 1 : int(m - ll(inv(m, a)) * ll(m) / a);
  }

 public:
  Modnum() : v(0) {}

  Modnum(ll v_) : v(int(v_ % mod)) {
    if (v < 0) {
      v += mod;
    }
  }

  explicit operator int() const { return v; }

  friend std::ostream& operator<<(std::ostream& out, const MD& n) {
    return out << int(n);
  }

  friend std::istream& operator>>(std::istream& in, MD& n) {
    ll x;
    in >> x;
    n = MD(x);
    return in;
  }

  friend bool operator==(const MD& a, const MD& b) { return a.v == b.v; }
  friend bool operator!=(const MD& a, const MD& b) { return a.v != b.v; }

  MD inv() const {
    MD res;
    res.v = inv(v, mod);
    return res;
  }

  MD neg() const {
    MD res;
    res.v = v ? mod - v : 0;
    return res;
  }

  MD operator-() const { return neg(); }

  MD operator+() const { return MD(*this); }

  MD& operator++() {
    v++;
    if (v == mod) v = 0;
    return *this;
  }

  MD& operator--() {
    if (v == 0) v = mod;
    v--;
    return *this;
  }

  MD& operator+=(const MD& o) {
    v += o.v;
    if (v >= mod) v -= mod;
    return *this;
  }

  MD& operator-=(const MD& o) {
    v -= o.v;
    if (v < 0) v += mod;
    return *this;
  }

  MD& operator*=(const MD& o) {
    v = int(ll(v) * ll(o.v) % mod);
    return *this;
  }

  MD& operator/=(const MD& o) { return *this *= o.inv(); }

  friend MD operator++(MD& a, int) {
    MD r = a;
    ++a;
    return r;
  }
  friend MD operator--(MD& a, int) {
    MD r = a;
    --a;
    return r;
  }
  friend MD operator+(const MD& a, const MD& b) { return MD(a) += b; }
  friend MD operator-(const MD& a, const MD& b) { return MD(a) -= b; }
  friend MD operator*(const MD& a, const MD& b) { return MD(a) *= b; }
  friend MD operator/(const MD& a, const MD& b) { return MD(a) /= b; }
};

namespace {

const int mod = 1e9 + 7;

int inv(int a) {
  a %= mod;
  assert(a);
  return a == 1 ? 1 : int(mod - ll(inv(mod, a)) * ll(mod) / a);
}

void add(int& a, int b) {
  a += b;
  if (a >= mod) {
    a -= mod;
  }
}

void sub(int& a, int b) {
  a -= b;
  if (a < 0) {
    a += mod;
  }
}

int mul(int a, int b) { return (int)((ll)a * b % mod); }

int power(int a, ll b) {
  int res = 1;
  while (b > 0) {
    if (b & 1) {
      res = mul(res, a);
    }
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

}  // namespace
