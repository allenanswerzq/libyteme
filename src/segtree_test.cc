#include "segtree.h"
#include "gtest/gtest.h"

namespace {

TEST(Segtree, IntervalSum) {
  Segtree sg(10);
  // 0 1 2 3
  // 1 1 0 0
  // 1 3 2 0
  sg.modify(0, 2, 1);
  EXPECT_EQ(sg.get(0, 2).sum, 2);
  sg.modify(1, 3, 2);
  EXPECT_EQ(sg.get(0, 3).sum, 6);
}

}  // namespace
