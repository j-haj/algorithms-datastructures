#include "gtest/gtest.h"
#include "list.h"

TEST(NodeTest, Constructor) {
  Node<int> n{5};
  EXPECT_EQ(n.value, 5);
}

TEST(ForwardListTest, ZeroSizeConstruction) {
  ForwardList<int> l{};
  EXPECT_EQ(l.size(), 0);
}

TEST(ForwardListTest, Insert) {
  ForwardList<int> l{};
  EXPECT_EQ(l.size(), 0);
  l.insert(1);
  EXPECT_EQ(l.size(), 1);
}
