#include <bits/stdc++.h>
using namespace std;

// String processing algortihms:
// KMP
// Rabin-Barp
// z_function
// Boyer-Morre
// Aho-Corasick
// Suffix tree
// Suffix array
// Skew
namespace string_func {
struct kmp_t {
  vector<int> fail_table(const string& pat) {
    int n = pat.size();
    vector<int> fail(n, 0);
    int k = 0;
    for (int i = 1; i < n; i++) {
      while (k > 0 && !(pat[i] == pat[k])) {
        k = fail[k - 1];
      }
      if (pat[i] == pat[k]) {
        k++;
      }
      fail[i] = k;
    }
    return fail;
  }

  vector<int> search(const string& text, const string& pat) {
  // returns 0-indexed positions of occurrences of s in w
    int n = pat.size();
    int m = text.size();
    vector<int> fail = fail_table(pat);
    assert(n >= 1 && (int) fail.size() == n);
    vector<int> res;
    int k = 0;
    for (int i = 0; i < m; i++) {
      while (k > 0 && (k == n || !(text[i] == pat[k]))) {
        k = fail[k - 1];
      }
      if (text[i] == pat[k]) {
        k++;
      }
      if (k == n) {
        res.push_back(i - n + 1);
      }
    }
    return res;
  }
};

vector<int> search(const string& text, const string& pat) {
  kmp_t kmp;
  return kmp.search(text, pat);
}

// Ref: https://cp-algorithms.com/string/z-function.html
vector<int> z_function(string s) {
  int n = (int) s.length();
  vector<int> z(n);
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r) {
      z[i] = min(r - i + 1, z[i - l]);
    }
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      ++z[i];
    }
    if (i + z[i] - 1 > r) {
      l = i, r = i + z[i] - 1;
    }
  }
  return z;
}
} // namespace string_func

