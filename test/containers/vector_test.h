#include "containers/vector.h"

namespace vector_test {
  const int kRepeatNum = 100;
}
TEST(VectorTest, EmptyConstruction) {
  auto v = containers::Vector<int>();
  ASSERT_EQ(v.size(), 0);
  ASSERT_EQ(v.capacity(), 2);
}

TEST(VectorTest, SizeConstructor) {
  for (int i = 0; i < vector_test::kRepeatNum; ++i) {
    auto v = containers::Vector<int>(i);
    ASSERT_EQ(v.size(), i);
  }
}
