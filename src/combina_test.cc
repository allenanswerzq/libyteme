#include "combina.h"
#include "modular.h"
#include "gtest/gtest.h"

namespace {

class SmallRange : public ::testing::Test {
 protected:
  const int kMaxRange = 1e3;
  typedef modnum_t<int(1e9) + 7> modnum;
};

class LargeRange : public ::testing::Test {
 protected:
  const long long kMaxRange = 1e6;
  typedef modnum_t<int(1e9) + 7> modnum;
};

TEST_F(SmallRange, SmallNumber) {
  combina_t combina(kMaxRange);
  EXPECT_EQ(combina(5, 1), 5);
  EXPECT_EQ(combina(5, 3), 10);
}

// TEST_F(SmallRange, SmallNumberMod) {
//   combina_large_t<modnum> combina(kMaxRange);
//   EXPECT_EQ(combina(5, 1), 5);
//   EXPECT_EQ(combina(5, 3), 10);
//   EXPECT_EQ(combina.npk(5, 1), 5);
//   EXPECT_EQ(combina.npk(5, 3), 60);
// }

TEST_F(LargeRange, LargeMod) {
  combina_large_t<modnum> combina(kMaxRange);
  EXPECT_EQ(combina(144, 6), 785899217);
  EXPECT_EQ(combina(12349, 789), 324396141);
  EXPECT_EQ(combina(100000, 1000), 893088409);
}

TEST_F(LargeRange, LargeModPermutation) {
  combina_large_t<modnum> combina(kMaxRange);
  EXPECT_EQ(combina.npk(144, 6), 847432285);
  EXPECT_EQ(combina.npk(12349, 789), 917462664);
  EXPECT_EQ(combina.npk(100000, 1000), 509053058);
}

}  // namespace