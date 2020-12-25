#include <bits/stdc++.h>
using namespace std;

// Taken from https://codeforces.com/contest/1151/submission/52973403
template <int mod_>
struct Modnum {
  static constexpr int mod = mod_;
  static_assert(mod_ > 0, "mod must be positive");

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

  friend std::ostream& operator<<(std::ostream& out, const Modnum& n) {
    return out << int(n);
  }

  friend std::istream& operator>>(std::istream& in, Modnum& n) {
    ll x;
    in >> x;
    n = Modnum(x);
    return in;
  }

  friend bool operator==(const Modnum& a, const Modnum& b) { return a.v == b.v; }
  friend bool operator!=(const Modnum& a, const Modnum& b) { return a.v != b.v; }

  Modnum inv() const {
    Modnum res;
    res.v = inv(v, mod);
    return res;
  }

  Modnum neg() const {
    Modnum res;
    res.v = v ? mod - v : 0;
    return res;
  }

  Modnum operator-() const { return neg(); }

  Modnum operator+() const { return Modnum(*this); }

  Modnum& operator++() {
    v++;
    if (v == mod) v = 0;
    return *this;
  }

  Modnum& operator--() {
    if (v == 0) v = mod;
    v--;
    return *this;
  }

  Modnum& operator+=(const Modnum& o) {
    v += o.v;
    if (v >= mod) v -= mod;
    return *this;
  }

  Modnum& operator-=(const Modnum& o) {
    v -= o.v;
    if (v < 0) v += mod;
    return *this;
  }

  Modnum& operator*=(const Modnum& o) {
    v = int(ll(v) * ll(o.v) % mod);
    return *this;
  }

  Modnum& operator/=(const Modnum& o) { return *this *= o.inv(); }

  friend Modnum operator++(Modnum& a, int) {
    Modnum r = a;
    ++a;
    return r;
  }
  friend Modnum operator--(Modnum& a, int) {
    Modnum r = a;
    --a;
    return r;
  }
  friend Modnum operator+(const Modnum& a, const Modnum& b) { return Modnum(a) += b; }
  friend Modnum operator-(const Modnum& a, const Modnum& b) { return Modnum(a) -= b; }
  friend Modnum operator*(const Modnum& a, const Modnum& b) { return Modnum(a) *= b; }
  friend Modnum operator/(const Modnum& a, const Modnum& b) { return Modnum(a) /= b; }
};

namespace {

const int mod = 1e9 + 7;

int inv(int a, int m) {
  a %= m;
  assert(a);
  return a == 1 ? 1 : int(m - ll(inv(m, a)) * ll(m) / a);
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
