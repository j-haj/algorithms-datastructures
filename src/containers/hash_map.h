#ifndef JTL_HASH_MAP_H__
#define JTL_HASH_MAP_H__
#include <memory>

namespace jtl {

template <typename Key,
          typename Value>
class HashMap {

  struct MapNode {
    MapNode(Key k, Value v) : key(k), value(v) {}
    ~MapNode() {
      delete key;
      delete value;
    }

    Key key;
    Value value;
  }; // struct MapNode

  class HashMapBase_ {
    private:
      // bins is an array of pointers to arrays of key-value nodes
      MapNode** bins_;       

  }; // class HashMapBase_
  public:
  private:
    Key* bins_;
}; // class HashMap
} // namespace jtl
#endif
