/* created   : 2020-08-23 20:58:09
 * accepted  : 2020-09-22 22:41:12
 */
#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
#define all(x) (x).begin(), (x).end()
#define ll long long

int func_array(vector<int>& A, int S, int M) {
  int n = A.size();
  vector<int> use(n);
  int ans = -1;
  for (int i = 0; i < n; i++) {
    int p = S;
    for (int j = 0; j < M - 1; j++) {
      // trace(j, use[p]);
      while (use[p]) {
        p = (p + 1) % n;
      }
      p = (p + 1) % n;
      while (use[p]) {
        p = (p + 1) % n;
      }
    }
    // trace(i, S, p, use);
    assert(!use[p]);
    use[p] = true;
    S = (p + 1) % n;
    ans = p;
  }
  return ans;
}

int func_list(list<int>& A, int S, int M) {
  // trace(A, S, M);
  int n = A.size();
  auto start = A.begin();
  int ans = 0;
  for (int i = 0; i < n; i++) {
    auto it = start;
    for (int j = 0; j < M - 1; j++) {
      if (++it == A.end()) {
        it = A.begin();
      }
    }
    // trace(i, *it);
    start = it;
    ans = *start;
    if (++start == A.end()) {
      start = A.begin();
    }
    assert(it != A.end());
    A.erase(it);
  }
  assert(A.empty());
  return (S + ans) % n;
}

// f(n, m) = (f(n - 1, m) + m) % n;
// Get the final postion(zero-index) if we have n people starts at 0 index,
// and jump m steps every time.
int josephus(int n, int m) {
  int p = 0;
  for (int i = 2; i <= n; i++) {
    p = (p + m) % i;
  }
  return p;
}

int func_josephus(int N, int S, int p) {
  return (p + S) % N;
}

#define EXPECT_TRUE(a) assert(a)
#define EXPECT_FALSE(a) assert(!a)
#define EXPECT(a, b) assert(a == b)

void solve() {
  int N = 100;
  vector<int> A(N);
  iota(all(A), 0);
  for (int s = 0; s < N; s++) {
    for (int m = 1; m <= N; m++) {
      int right = func_josephus(N, s, josephus(N, m));
      EXPECT(func_array(A, s, m), right);
      list<int> li(A.begin(), A.end());
      EXPECT(func_list(li, s, m), right);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  solve();
  return 0;
}
