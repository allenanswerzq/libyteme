#include "binary_heap.h"
#include "gtest/gtest.h"

TEST(BinaryHeap, Insert) {
  vector<int> v = {4, 3, 1, 2, 5};
  BinaryHeap<100> binary_heap;
  for (int i = 0; i < 5; i++) {
    binary_heap.insert(v[i]);
  }
  EXPECT_EQ(binary_heap.hs, 5);
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(binary_heap.top(), i + 1);
  }
  EXPECT_EQ(binary_heap.hs, 0);
}

TEST(BinaryHeap, InitalizeVector) {
  vector<int> v = {4, 3, 1, 2, 5};
  BinaryHeap<100> binary_heap(v);
  EXPECT_EQ(binary_heap.hs, 5);
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(binary_heap.top(), i + 1);
  }
  EXPECT_EQ(binary_heap.hs, 0);
}
