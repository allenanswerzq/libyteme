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

// -------------------------------------------------------------------------
// Ref: Kactl codebase.
struct H {
  using ull = unsigned long long;
  ull x = 0;

  H() {}

  H(ull x_) : x(x_) {}

  // equivalent: (a + b) % ((2^64)-1)
  H operator+(H o) {
    // rax = r
    // rdx = o.x
    // add  rdx rax -> rax
    // adcq   0 rax -> rax
    ull r = x;
    asm("addq %%rdx, %0\n"
        "adcq $0,%0\n"
        : "+a"(r)    // %0, output operand
        : "d"(o.x)); // %1, input operand
    return r;
  }

  // equivalent: (a * b) % ((2^64)-1)
  H operator*(H o) {
    // rax = r
    // rcx = o.x
    // mul  rcx rax -> rax
    // add  rdx rax -> rax
    // adcq   0 rax -> rax
    ull r = x;
    asm("mul %1\n"
        "addq %%rdx, %0\n"
        "adcq $0,%0\n"      // add with carry quad (8 bytes)
        : "+a"(r)
        : "r"(o.x)
        : "rdx");
    return r;
  }

  H operator-(H o) { return *this + ~o.x; }
  ull get() const { return x + !~x; }
  bool operator==(H o) const { return get() == o.get(); }
  bool operator<(H o) const { return get() < o.get(); }
};

struct HashString {
  const H C = (ll)1e11 + 3;  // (order ~ 3e9; random also ok)

  vector<H> ha, pw;

  HashString(string& str) {
    int n = str.size();
    ha.resize(n + 1);
    pw.resize(n + 1);
    pw[0] = 1;
    for (int i = 0; i < n; i++) {
      ha[i + 1] = ha[i] * C + str[i];
      pw[i + 1] = pw[i] * C;
    }
  }

  // Compute the hash for interval [a, b)
  H hash(int a, int b) {
    return ha[b] - ha[a] * pw[b - a];
  }
};

int lexicographically_minimal_string(const string& s) {
  int n = (int) s.size();
  int i = 0, j = 1, k = 0;
  while (k < n && i < n && j < n) {
    char a = s[(i + k) % n];
    char b = s[(j + k) % n];
    if (a == b) {
      k++;
    }
    else if (a > b) {
      i = i + k + 1;
      k = 0;
      if (i == j) i++;
    }
    else {
      j = j + k + 1;
      k = 0;
      if (i == j) i++;
    }
  }
  return min(i, j);
}

// -------------------------------------------------------------------------
void test() {
  // [0....255 0....255]
  uint8_t a = 128;
  for (uint8_t b = 128; b < 255; b++) {
    uint8_t c = a + b;
    int d = (a + b) % 256 + 1;
    int e = (a + b) % 255;
    trace((int)b, (int)c, d, e);
    assert(e == d);
  }
}
