#include <random>

#include "containers/vector.h"

namespace vector_test {
  const int kRepeatNum = 100;
  const int kMaxRange = 100;

  std::random_device r;
  std::default_random_engine e(r());
  std::uniform_int_distribution<int> dist(1, kMaxRange);
}
TEST(VectorTest, EmptyConstruction) {
  auto v = containers::Vector<int>();
  ASSERT_EQ(v.size(), 0);
  ASSERT_EQ(v.capacity(), 2);
}

TEST(VectorTest, SizeConstructor) {
  for (int i = 0; i < vector_test::kRepeatNum; ++i) {
    int size = vector_test::dist(vector_test::e);
    auto v = containers::Vector<int>(size);
    ASSERT_EQ(v.size(), size);
  }
}

TEST(VectorTest, ListConstructor) {
  containers::Vector<int> v({1, 2, 3, 4});
  ASSERT_EQ(v.size(), 4);
  for (int i = 0; i < v.size(); ++i) {
    ASSERT_EQ(v[i], i+1);
  }
}

TEST(VectorTest, MoveConstructor) {
  auto v = containers::Vector<int> ({1, 2, 3, 4});
  ASSERT_EQ(v.size(), 4);
  for (int i = 0; i < v.size(); ++i) {
    ASSERT_EQ(v[i], i+1);
  }
}

TEST(VectorTest, CopyConstructor) {
  auto v1 = containers::Vector<int>({1, 2, 3, 4});
  auto v2 = v1;
  ASSERT_EQ(v1.size(), v2.size());
  ASSERT_EQ(v1.capacity(), v2.capacity());
  for (int i = 0; i < v1.size(); ++i) {
    ASSERT_EQ(v1[i], v2[i]);
  }
}
