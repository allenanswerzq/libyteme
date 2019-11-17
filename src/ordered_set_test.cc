#include "ordered_set.h"
#include "gtest/gtest.h"

namespace {

TEST(OrderedMap, OrderedMapTest) {
  OrderedMap<int, vector<int>> omp;
  omp[9] = {2};
  omp[8] = {1};
  omp[3] = {0};
  EXPECT_EQ(omp.at(0), make_pair(3, vector<int>{0}));
  EXPECT_EQ(omp.at(1), make_pair(8, vector<int>{1}));
  EXPECT_EQ(omp.at(2), make_pair(9, vector<int>{2}));
  EXPECT_EQ(omp.index(3), 0);
  EXPECT_EQ(omp.index(8), 1);
}

TEST(OrderedSet, OrderedSetTest) {
  OrderedSet<int> ost;
  // Insert
  ost.insert(1);
  ost.insert(2);
  ost.insert(3);
  ost.insert(4);
  ost.insert(5);
  // Erase
  ost.erase(5);
  EXPECT_EQ(ost.size(), 4);
  // Access
  for (int i = 0; i < 4; i++) {
    EXPECT_EQ(ost.at(i), i + 1);
  }
  // Index
  int k = 0;
  for (auto v : ost) {
    EXPECT_EQ(ost.index(v), k++);
  }
  EXPECT_EQ(ost.index(18), -1);
  // Count
  EXPECT_EQ(ost.count(2), 1);
}

TEST(OrderedMultiSet, OrderedMultiSetTest) {
  OrderedMultiSet<int> omst;
  // Insert
  omst.insert(1);
  omst.insert(2);
  omst.insert(3);
  omst.insert(1);
  omst.insert(5);
  omst.insert(1);
  // Access
  EXPECT_EQ(omst.at(0), 1);
  EXPECT_EQ(omst.at(1), 1);
  EXPECT_EQ(omst.at(2), 1);
  EXPECT_EQ(omst.at(3), 2);
  EXPECT_EQ(omst.at(4), 3);
  EXPECT_EQ(omst.at(5), 5);
  // Erase a single key
  omst.erase(omst.att(1));
  EXPECT_EQ(omst.count(1), 2);
  // Erase all values for a key
  omst.erase_all(1);
  omst.insert(3);
  omst.insert(3);
  omst.insert(3);
  EXPECT_EQ(omst.count(3), 4);
  omst.erase_all(3);
  EXPECT_EQ(omst.count(3), 0);
  // lower_bound
  EXPECT_EQ(omst.lower_bound(2), 0);
  EXPECT_EQ(omst.lower_bound(1), 0);
  EXPECT_EQ(omst.lower_bound(10), 2);
  // upper_bound
  EXPECT_EQ(omst.upper_bound(2), 1);
  EXPECT_EQ(omst.upper_bound(1), 0);
  EXPECT_EQ(omst.upper_bound(10), 2);
}

}  // namespace
