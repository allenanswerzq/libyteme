#include "src/bit.h"

#include "gtest/gtest.h"

namespace {

TEST(BitTest, Query) {
  vector<int> v = {1, 2, 3, 4, 5};
  Bit<int> bit(v);
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += v[i];
    EXPECT_EQ(bit.query(i), sum);
  }
}

TEST(BitTest, QueryInterval) {
  vector<int> v = {1, 2, 3, 4, 5};
  Bit<int> bit(v);
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += v[i];
  }
  int cur = 0;
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(bit.query(i, 4), sum - cur);
    cur += v[i];
  }
}

TEST(BitTest, QueryAdd) {
  vector<int> v = {1, 2, 3, 4, 5};
  Bit<int> bit(5);
  for (int i = 0; i < 5; i++) {
    bit.add(i, v[i]);
  }
  int sum = 0;
  for (int i = 0; i < 5; i++) {
    sum += v[i];
    EXPECT_EQ(bit.query(i), sum);
  }
}

}  // namespace
