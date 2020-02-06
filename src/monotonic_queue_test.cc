#include "monotonic_queue.h"

#include "base.h"

namespace {

TEST(Max, TestQueue) {
  vector<int> v = {1, 10, 2, 8, 7, 3, 12};
  MonotonicQueue mq;
  vector<int> ans = mq.get_max(v, 3);
  vector<int> right = {1, 10, 10, 10, 8, 8, 12};
  EXPECT_EQ(ans, right);
}

TEST(LargestRectangle, TestStack) {
  vector<int> height = {2, 1, 5, 6, 2, 3};
  vector<int> ans = largest(height);
  EXPECT_EQ(ans, 10);
}

}  // namespace

}  // namespace
