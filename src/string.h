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
    assert(n >= 1 && (int)fail.size() == n);
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
vector<int> z_function(const string& s) {
  int n = (int) s.size();
  vector<int> z(n);
  int x = 0, y = 0;
  for (int i = 1; i < n; ++i) {
    z[i] = max(0, min(z[i - x], y - i + 1));
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      x = i;
      y = i + z[i];
      z[i]++;
    }
  }
  return z;
}

vector<int> prefix_function(const string& s) {
  //           -----....-----
  //           [-j-]
  // [-j-]
  // -----j....-----i
  // -----.....-----++++++++++++++++++++
  int n = (int) s.size();
  vector<int> next(n);
  for (int i = 1; i < n; i++) {
    int j = next[i - 1];
    while (j > 0 && s[i] != s[j]) {
      j = next[j - 1];
    }
    if (s[i] == s[j]) j++;
    next[i] = j;
  }
  return next;
}
