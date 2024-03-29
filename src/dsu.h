#include <bits/stdc++.h>
using namespace std;

// A Dsu class implements a common disjoint union set data structure.
//
// Note: After applying join operation, the whole data will be
// splited into different set groups.

// this class also supports:
// * get the number of set groups `m` after join, each group
//   will have a `gid` starting at 0
//
// * for a specific set group, we can get the root via get_groot call
//
// * also for a root, we can get the group id `gid` to which it belongs
//

struct Dsu {
  int n;
  int m;
  int gid;
  vector<int> e;
  vector<int> root_hash;
  vector<int> gid_hash;

  Dsu(int n_) : n(n_) {
    m = n;
    gid = 0;
    e.resize(n, -1);
    root_hash.resize(n, -1);
    gid_hash.resize(n, -1);
  }

  int size(int x) { return -e[find(x)]; }

  int find_rec(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }

  int find(int u) {
    int root = u;
    while (e[root] >= 0) {
      root = e[root];
    }
    while (u != root) {
      int t = e[u];
      e[u] = root;
      u = t;
    }
    return root;
  }

  bool same(int a, int b) { return find(a) == find(b); }

  bool join(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) {
      return false;
    }
    if (-e[a] < -e[b]) {
      swap(a, b);
    }
    // the tree with fewer nodes been added.
    e[a] += e[b];
    e[b] = a;
    m--;
    return true;
  }

  // Given a gid, finds the root of that group
  int get_groot(int ix) {
    assert(0 <= ix && ix < n);
    assert(root_hash[ix] != -1);
    return root_hash[ix];
  }

  // Given a root, finds the gid.
  int get_gid(int root) {
    assert(0 <= root && root < n);
    if (gid_hash[root] == -1) {
      gid_hash[root] = gid;
      root_hash[gid] = root;
      gid++;
    }
    return gid_hash[root];
  }

  vector<vector<int>> groups() {
    vector<vector<int>> ret(m);
    // Note: zero index based.
    for (int i = 0; i < n; i++) {
      int root = find(i);
      ret[get_gid(root)].push_back(i);
    }
    return ret;
  }
};
