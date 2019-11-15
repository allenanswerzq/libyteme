#include <bits/stdc++.h>
using namespace std;

// Taken from https://codeforces.com/contest/1151/submission/52973403
template <int mod_>
struct modnum_t {
  static constexpr int mod = mod_;
  static_assert(mod_ > 0, "mod must be positive");

 private:
  using ll = long long;
  int v;

  static int inv(int a, int m) {
    a %= m;
    assert(a);
    return a == 1 ? 1 : int(m - ll( inv(m, a) ) * ll(m) / a);
  }

 public:
  modnum_t() : v(0) {}

  modnum_t(ll v_) : v(int(v_ % mod)) {
    if (v < 0) {
      v += mod;
    }
  }

  explicit operator int() const { return v; }

  friend std::ostream& operator << (std::ostream& out, const modnum_t& n) {
    return out << int(n);
  }

  friend std::istream& operator >> (std::istream& in, modnum_t& n) {
    ll x; in >> x;
    n = modnum_t(x);
    return in;
  }

  friend bool operator == (const modnum_t& a, const modnum_t& b) { return a.v == b.v; }
  friend bool operator != (const modnum_t& a, const modnum_t& b) { return a.v != b.v; }

  modnum_t inv() const {
    modnum_t res;
    res.v = inv(v, mod);
    return res;
  }

  modnum_t neg() const {
    modnum_t res;
    res.v = v ? mod - v : 0;
    return res;
  }

  modnum_t operator- () const {
    return neg();
  }

  modnum_t operator+ () const {
    return modnum_t(*this);
  }

  modnum_t& operator ++ () {
    v++;
    if (v == mod) v = 0;
    return *this;
  }

  modnum_t& operator -- () {
    if (v == 0) v = mod;
    v--;
    return *this;
  }

  modnum_t& operator += (const modnum_t& o) {
    v += o.v;
    if (v >= mod) v -= mod;
    return *this;
  }

  modnum_t& operator -= (const modnum_t& o) {
    v -= o.v;
    if (v < 0) v += mod;
    return *this;
  }

  modnum_t& operator *= (const modnum_t& o) {
    v = int(ll(v) * ll(o.v) % mod);
    return *this;
  }

  modnum_t& operator /= (const modnum_t& o) {
    return *this *= o.inv();
  }

  friend modnum_t operator ++ (modnum_t& a, int) { modnum_t r = a; ++a; return r; }
  friend modnum_t operator -- (modnum_t& a, int) { modnum_t r = a; --a; return r; }
  friend modnum_t operator + (const modnum_t& a, const modnum_t& b) { return modnum_t(a) += b; }
  friend modnum_t operator - (const modnum_t& a, const modnum_t& b) { return modnum_t(a) -= b; }
  friend modnum_t operator * (const modnum_t& a, const modnum_t& b) { return modnum_t(a) *= b; }
  friend modnum_t operator / (const modnum_t& a, const modnum_t& b) { return modnum_t(a) /= b; }
};

namespace {

typedef long long ll;
const int mod = 1e9 + 7;

void add(int &a, int b) {
  a += b;
  if (a >= mod) {
    a -= mod;
  }
}

void sub(int &a, int b) {
  a -= b;
  if (a < 0) {
    a += mod;
  }
}

int mul(int a, int b) {
  return (int) ((ll) a * b % mod);
}

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
