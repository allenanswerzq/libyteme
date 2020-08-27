struct RangeSegment {
  vector<int> L;
  vector<int> R;
  // which segment the index `i` locates.
  vector<int> pos;
  int seg_num = 0;

  RangeSegment(int n, int seg_num_) : seg_num(seg_num_) {
    assert(seg_num);
    int t = n / seg_num;
    if (seg_num * t < n) {
      seg_num++;
    }
    trace(seg_num, t, n);
    L.resize(seg_num + 1);
    R.resize(seg_num + 1);
    pos.resize(n + 1);
    // [1...t][t + 1...2 * t]
    for (int i = 1; i <= seg_num; i++) {
      L[i] = (i - 1) * t + 1;
      R[i] = min(i * t, n);
    }
    for (int i = 1; i <= seg_num; i++) {
      for (int j = L[i]; j <= R[i]; j++) {
        pos[j] = i;
      }
    }
  }

  int segment_id(int x) {
    assert(x < pos.size());
    return pos[x];
  }
};
