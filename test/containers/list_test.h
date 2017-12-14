#include "containers/list.h"


TEST(NodeTest, ConstructNode) {
  auto node = Node<int>(5);
  ASSERT_EQ(5, node.value);
  ASSERT_EQ(nullptr, node.next);
}

TEST(ForwardListTest, ConstructList) {
  auto list = ForwardList<int>();
  ASSERT_EQ(0, list.size());
}

TEST(ForwardListTest, InsertElementCheckSize) {
  auto list = ForwardList<int>();
  list.insert(5);
  ASSERT_EQ(1, list.size());
}
