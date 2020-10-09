#include "ring_queue.h"

#include "benchmark.h"
#include "gtest/gtest.h"
#include "random.h"

namespace {

TEST(RingQueue, EmptyFull) {
  RingQueue<uint64, 3> rq;
  EXPECT_EQ(rq.size(), 0);
  EXPECT_EQ(rq.empty(), true);
  EXPECT_EQ(rq.full(), false);
  rq.push(New64());
  EXPECT_EQ(rq.size(), 1);
  rq.pop();
  EXPECT_EQ(rq.size(), 0);
  rq.push(New64());
  rq.push(New64());
  rq.push(New64());
  EXPECT_EQ(rq.size(), 3);
  EXPECT_EQ(rq.full(), true);
  rq.pop();
  EXPECT_EQ(rq.size(), 2);
  rq.pop();
  rq.pop();
  EXPECT_EQ(rq.empty(), true);
}

TEST(RingQueue, Push) {
  const int n = 10000;
  RingQueue<uint64, n> rq;
  vector<uint64> v(n);
  for (int i = 0; i < n; i++) {
    v[i] = New64();
  }
  for (int i = 0; i < n; i++) {
    rq.push(v[i]);
  }
  for (int i = 0; i < n; i++) {
    EXPECT_EQ(rq.front(), v[i]);
    rq.pop();
  }
}

TEST(RingQueue, Limit) {
  // test push exceeds the limit of the RingQueue
  const int n = 10000;
  RingQueue<uint64, n> rq;
  for (int i = 0; i < 10007; i++) {
    if (i >= n) {
      EXPECT_DEATH({ rq.push(New64()); }, "Assertion failed");
    } else {
      rq.push(New64());
    }
  }
}

TEST(RingQueue, Random) {
  // Random push and pop in the RingQueue
  const int n = 10000;
  RingQueue<uint64, n> rq;
  deque<uint64> dq;
  for (int i = 0; i < n; i++) {
    uint64 op = New64();
    uint64 x = New64();
    if (op % 2) {
      rq.push(x);
      dq.push_back(x);
    } else {
      EXPECT_EQ(dq.size(), rq.size());
      if (!dq.empty()) {
        EXPECT_EQ(rq.front(), dq.front());
        rq.pop();
        dq.pop_front();
      }
    }
  }
}

static void BM_RingQueue(int iter) {
  RingQueue<uint64, 100000> rq;
  for (int i = 0; i < iter; i++) {
    rq.push(New64());
    rq.pop();
  }
}

BENCHMARK(BM_RingQueue);

}  // namespace
