#ifndef JTL_INTRUSIVE_LIST_H__
#define JTL_INTRUSIVE_LIST_H__
#include "abstract_intrusive_list.h"
namespace jtl {
template <typename T>
class IntrusiveList {
  class IntrusiveListBase : public AbstractIntrusiveList {
   public:
    AbstractIntrusiveList* Next() { return next_; }
    AbstractIntrusiveList* Previous() { return next_; }
    void Erase() {
      auto& tmp = prev_->Next();
      tmp = next_;
    }

   private:
    IntrusiveListBase* next_;
    IntrusiveListBase* prev_;
  };  // class IntrusiveListBase

};  // class IntrusiveList
}  // namespace jtl
#endif
