#ifndef JTL_FLAT_HASH_MAP_H__
#define JTL_FLAT_HASH_MAP_H__
#include <memory>
#include <cctype>

namespace jtl {

template <typename Key>
struct Hash {
  using argument_type = Key;
  using result_type = std::size_t;

  result_type operator()(const Key& k);
}; // struct Hash

template <typename Key,
          typename Value>
class FlatHashMap {
  public:
    FlatHashMap() : bins_(), hash_() {}
  struct MapNode {
    MapNode(Key k, Value v) : key(k), value(v) {}

    Key key;
    Value value;
  }; // struct MapNode

  private:
  std::vector<std::vector<MapNode>> bins_;
  Hash<Key> hash_;  
}; // class HashMap
} // namespace jtl
#endif // JTL_FLAT_HASH_MAP__
