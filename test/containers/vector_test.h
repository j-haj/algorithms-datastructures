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

TEST(VectorTest, PushBack) {
  auto v = containers::Vector<int>();
  ASSERT_EQ(v.size(), 0);
  ASSERT_EQ(v.capacity(), 2);
  v.push_back(1);
  ASSERT_EQ(v.size(), 1);
  ASSERT_EQ(v.capacity(), 2);
  v.push_back(2);
  ASSERT_EQ(v.size(), 2);
  ASSERT_EQ(v.capacity(), 2);
  v.push_back(3);
  ASSERT_EQ(v.size(), 3);
  ASSERT_EQ(v.capacity(), 4);
}

TEST(VectorTest, IndexingOperator) {
  auto v = containers::Vector<int>({1, 2, 3});
  for (size_t i = 0; i < v.size(); ++i) {
    ASSERT_EQ(i + 1, v[i]);
  }
}

TEST(VectorTest, PopBasic) {
  containers::Vector<int> v = containers::Vector<int>({1, 2});
  ASSERT_EQ(v.size(), 2);
  ASSERT_EQ(v.capacity(), 2);
  int x = v.pop();
  ASSERT_EQ(v.size(), 1);
  ASSERT_EQ(v.capacity(), 2);
  ASSERT_EQ(x, 1);
  int y = v.pop();
  ASSERT_EQ(v.size(), 0);
  ASSERT_EQ(v.capacity(), 2);
  ASSERT_EQ(y, 2);
}

TEST(VectorTest, GetValid) {
  auto v = containers::Vector<int>({1});
  std::experimental::optional<int> x = v.get(0);
  ASSERT_EQ(x.value_or(2), 1);
}

TEST(VectorTest, GetInvalid) {
  auto v = containers::Vector<int>();
  std::experimental::optional<int> x = v.get(1);
  ASSERT_EQ(x.value_or(2), 2);
}
