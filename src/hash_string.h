template <int N>
struct HashString {
  using ull = unsigned long long;
  const int base = 131;
  vector<ull> hash;
  vector<ull> hsah;  // reverse hash
  vector<ull> mul;
  int n = 0;

  void init() {
    hash.resize(N);
    hsah.resize(N);
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
    assert(0 <= l && l <= r);
    int nl = reverse_index(r);
    int nr = reverse_index(l);
    return hsah[nr + 1] - hsah[nl] * mul[r - l + 1];
  }

  void append(const string& s) {
    int l = s.size();
    for (int i = 0; i < l; i++) {
      hash[n + 1 + i] = hash[n + i] * base + s[i] - 'a';
      hsah[n + 1 + i] = hsah[n + i] * base + s[l - i - 1] - 'a';
    }
    n += l;
  }
};

struct HashString {
  static const int base = 131;
  using ull = unsigned long long;

  static ull get(const string& s) {
    ull ans = 1;
    for (char c : s) {
      ans = ans * base + c - 'a';
    }
    return ans;
  }
};
