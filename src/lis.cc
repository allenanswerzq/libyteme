#include <bits/stdc++.h>
using namespace std;
// Longest strictly increase sequence
// O(n * logn)
vector<int> lis(vector<int>& a) {
  int n = (int) a.size();
  // The smallest value index for a sequence with length `i`
  vector<int> dp(n);
  vector<int> pr(n);
  vector<int> lis(n);
  int len = 0;
  for (int i = 0; i < n; ++i) {
    auto ix = lower_bound(lis.begin(), lis.begin() + len, a[i]) - lis.begin();
    lis[ix] = a[i];
    dp[ix] = i;
    pr[i] = ix ? dp[ix - 1] : -1;
    if (ix == len) {
      len++;
    }
  }
  trace(len, a, dp, pr);
  vector<int> ans;
  int cur = dp[len - 1];
  while (cur != -1) {
    ans.push_back(a[cur]);
    cur = pr[cur];
  }
  reverse(ans.begin(), ans.end());
  return ans;
}

void test(vector<int> a) {
  vector<int> r = lis(a);
  for (int i = 0; i < (int) r.size(); ++i) {
    if (i > 0) {
      cout << " ";
    }
    cout << r[i];
  }
  cout << "\n";
}

int main() {
  test({1, 6, 2, 3, 5});
  test({6, 7, 2, 3, 5});
  return 0;
}
