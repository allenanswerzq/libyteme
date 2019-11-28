#include "segtree.h"

#include "random.h"
#include "benchmark.h"
#include "gtest/gtest.h"

namespace {

TEST(Segtree, IntervalSum) {
  Segtree sg(10);
  sg.modify(0, 2, 1);
  EXPECT_EQ(sg.get(0, 2).sum, 2);
  sg.modify(1, 3, 2);
  EXPECT_EQ(sg.get(0, 3).sum, 6);
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

BENCHMARK(BM_SegtreeSum)->Range(1000, 100000);

// static BM_SegtreeSumVector(int iter) {
//   Segtree
// }

}  // namespace
