#include "src/dsu.h"
#include "gmock/gmock.h"

namespace {

class BuildDsu : public ::testing::Test {
 protected:
  shared_ptr<Dsu> dsu;
  void SetUp() override {
    dsu = make_shared<Dsu>(5);
    dsu->join(0, 1);
    dsu->join(1, 2);
  }
};

TEST_F(BuildDsu, Join) {
  EXPECT_EQ(dsu->n, 5);
  EXPECT_EQ(dsu->m, 3);
  EXPECT_EQ(dsu->gid, 0);
  EXPECT_TRUE(dsu->join(3, 4));
  EXPECT_FALSE(dsu->join(2, 0));
  EXPECT_EQ(dsu->find(0), 0);
  EXPECT_EQ(dsu->find(3), 3);
}

TEST_F(BuildDsu, Group) {
  dsu->join(3, 4);
  vector<vector<int>> g = dsu->groups();
  EXPECT_EQ(dsu->m, 2);
  sort(g[0].begin(), g[0].end());
  sort(g[1].begin(), g[1].end());
  EXPECT_EQ(g[0][0], 0);
  EXPECT_EQ(g[0][1], 1);
  EXPECT_EQ(g[0][2], 2);
  EXPECT_EQ(g[1][0], 3);
  EXPECT_EQ(g[1][1], 4);
  EXPECT_EQ(dsu->get_groot(0), 0);
  EXPECT_EQ(dsu->get_groot(1), 3);
  EXPECT_EQ(dsu->get_gid(3), 1);
  EXPECT_EQ(dsu->get_gid(0), 0);
}

}  // namespace

