struct Discreter {
  vector<int> e;
  vector<int> a;
  unordered_map<int, int> t;
  int mx = 0;
  bool one_index = true;

  Discreter(vector<int>& v) {
    a = v;
    e = v;
    sort(all(e));
    e.erase(unique(all(e)), e.end());
    for (const auto& x : v) {
      int p = lower_bound(all(e), x) - e.begin() + one_index;
      mx = max(mx, p);
      t[x] = p;
    }
  }

  int at(int x) { return a[x]; }

  int size() { return mx; }

  // Given a raw value, returns the discreted value.
  int get_dis(int x) { return t[x]; }

  // Given a discreted value, return the raw value.
  int get_raw(int x) { return e[x - one_index]; }
};
