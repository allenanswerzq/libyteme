#include "segtree.h"

#include "random.h"
#include "benchmark.h"
#include "gtest/gtest.h"

namespace {

TEST(Segtree, Sum) {
  Segtree sg(10);
  sg.modify(0, 2, 1);
  EXPECT_EQ(sg.get(0, 2).sum, 2);
  sg.modify(1, 3, 2);
  EXPECT_EQ(sg.get(0, 3).sum, 6);
}

TEST(Segtree, Vector) {
  const int kMax = 1e9 + 7;
  const int n = 1e5;
  vector<int> v(n);
  for (int i = 0; i < n; i++) {
    v[i] = New64() % kMax;
  }
  vector<int64> pr(n + 1);
  for (int i = 0; i < n; i++) {
    pr[i + 1] = pr[i] + v[i];
  }
  Segtree sg(v);
  for (int i = 0; i < 10000; i++) {
    int lo = New64() % n;
    int hi = New64() % n;
    if (lo > hi) {
      swap(lo, hi);
    }
    EXPECT_EQ(sg.get(lo, hi).sum, pr[hi + 1] - pr[lo]);
  }
}

static void BM_SegtreeSum(int iter, int arg) {
  int n = arg;
  Segtree sg(n);
  for (int i = 0; i < iter; i++) {
    int lo = New64() % n;
    int hi = New64() % n;
    int val = New64() % n;
    if (lo > hi) {
      swap(lo, hi);
    }
    sg.modify(lo, hi, val);
  }
}

BENCHMARK(BM_SegtreeSum)->Range(10000, 1000000);

static void BM_SegtreeVector(int iter, int arg) {
  for (int it = 0; it < iter; it++) {
    vector<int64> v(arg);
    for (int i = 0; i < arg; i++) {
      v[i] = New64();
    }
    Segtree sg(v);
  }
}

BENCHMARK(BM_SegtreeVector)->Range(10000, 100000);

}  // namespace
