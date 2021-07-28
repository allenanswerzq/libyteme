template <bool ONE = false>
struct Discreter {
  unordered_map<int, int> raw_dis_;
  vector<int> sorted_;

  Discreter(const vector<int> &val) {
    sorted_ = val;
    sort(all(sorted_));
    sorted_.erase(unique(all(sorted_)), sorted_.end());
    for (int &x : val) {
      int p = lower_bound(all(sorted_), x) - sorted_.begin() + ONE;
      raw_dis_[x] = p;
    }
  }

  // The maxinum value after discreting
  int max() { return sorted_.size(); }

  // Given a raw value, returns the discreted value.
  int get(int r) { return raw_dis_[r]; }

  // Given a discreted value, returns the raw value.
  int old(int d) { return sorted_[d - ONE]; }
};

