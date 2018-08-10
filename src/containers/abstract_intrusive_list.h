#ifndef JTL_ABSTRACT_INTRUSIVE_LIST_H__
#define JTL_ABSTRACT_INTRUSIVE_LIST_H__
#include <memory>
/**
 * Defines the interface for the intrusive linked list.
 */
class AbstractIntrusiveList {
  public:
    ~AbstractIntrusiveList() = default;

    /**
     * Returns a pointer to the next element in the list
     */
    virtual AbstractIntrusiveList*  Next() = 0;

    /**
     * Returns a pointer to the prior element in the list
     */
    virtual AbstractIntrusiveList* Previous() = 0;

    /**
     * Erases the element in the list
     */
    virtual void Erase() = 0;

}; // class AbstractIntrusiveList

#endif // JTL_ABSTRACT_INTRUSIVE_LIST_H__
