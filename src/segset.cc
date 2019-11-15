struct segset {
  set<pair<int, int>> st;
  // Set a maxn value so that we only compare
  // two pairs using the first value.
  const int HI = 1e6 + 7;

  // Finds the neareast position that less than x
  // and not occpuied by any interval.
  int getpre(int x) {
    auto it = st.upper_bound({x, HI});
    if (it == st.begin()) {
      return x - 1;
    }
    return (--it)->x - 1;
  }

  // Finds the neareast position that greater than x
  // and not occpuied by any interval.
  int getnxt(int x) {
    auto it = st.upper_bound({x, HI});
    if (it == st.begin()) {
      return x + 1;
    }
    return (--it)->y + 1;
  }

  void insert(int x) {
    int lo = x;
    int hi = x;
    auto it = st.lower_bound({x, HI});
    if (it != st.end()) {
      if (it->x == x + 1) {
        hi = it->y;
        st.erase(it);
      }
    }
    it = st.lower_bound({x, HI});
    if (it != st.begin()) {
      it--;
      if (it->y == x - 1) {
        lo = it->x;
        st.erase(it);
      }
    }
    st.insert({lo, hi});
  }
};

void test() {
  segset t;
  t.st.insert({4, 9});
  int x = t.getnxt(3);
  int y = t.getnxt(4);
  assert(x == 4);
  assert(y == 10);
  exit(0);
}
