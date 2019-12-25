#include "base.h"

struct MonotonicQueue {
  vector<int> get_max(const vector<int>& v, int k) {
    int n = v.size();
    deque<int> dq;
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
      while (dq.front() <= i - k) {
        dq.pop_front();
      }
      // Monotonicly decreasing from front to back.
      while (!dq.empty() && v[dq.back()] <= v[i]) {
        dq.pop_back();
      }
      dq.push_back(i);
      ans[i] = v[dq.front()];
    }
    return ans;
  }
};


