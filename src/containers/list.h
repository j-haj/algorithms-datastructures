#ifndef __LIST_H
#define __LIST_H

namespace containers {

/**
 * The @p ListNode class is essentially a wrapper for the data stored by the @p
 * List class.
 */
template <typename T>
class ListNode {
public:
  // TODO: Add constructors
  
  /// Returns the value of the node
  T value() { return *value_; }

private:

  /// Holds the node data
  std::unique_ptr<T> value_;

  /// Points to the next node
  std::shared_ptr<ListNode<T>> next_;

  /// Points to the previous node
  std::shared_ptr<ListNode<T>> previous_;
};  
 
/**
 * The @p List class provides a doubly linked list implementation and supports
 * basic operations such as @p insert, @p append, @p remove, and element access
 * via @p get, which uses @p std::optional<T>, or via @p operator[].
 */
template <typename T>
class List {

public:
  // TODO: Add constructors

  /**
   * Access the object at @p index. Will throw a runtime error if @p index is
   * out of range.
   *
   * @param index index of the object being accessed within the list
   *
   * @return object located at @p index
   */
  T& operator[](size_t index);
 
  /**
   * Attempts to get and return the object at @p index. If @p index is not a
   * valid index, then the optional returned will be empty. This method will not
   * throw an exception.
   *
   * @param index location of the object attempting to be accessed
   *
   * @return @p std::optional<T> possibly containing the object at @p index
   */ 
  std::experimental::optional<T> get(size_t index) noexcept;

  /**
   * Inserts an object at the head of the list, giving the list a new root node
   *
   * @param o object to be inserted into the new root node
   */
  void insert(T& o);

  /**
   * Appends an element to the list, giving the list a new tail node
   *
   * @param v the object to be appended to the list
   */
  void append(T& v);

  /**
   * Removes the element at @p index without returning it to the caller.
   *
   * @param index index of the element to be removed from the list
   */
  void remove(size_t index);

  /**
   * Removes the element at @p index in the list and returns it to the caller.
   * The default @p index is 0, so calling @p pop without and argument will
   * return the root, and set the root's pointed to element as the new root.
   *
   * @param index the index of the element to remove and return (default value
   * is 0)
   *
   * @return Returns the element located at @p index in the list.
   */
  void pop(size_t index = 0);

  /**
   * Returns the number of elements in the list.
   *
   * @return Number of elements in the list
   */
  size_t size() { return size_; }
private:

  /// Reference to the root node
  std::shared_ptr<ListNode<T>> root_;

  /// Reference to the tail node
  std::shared_ptr<ListNode<T>> tail_;

  /// The number of elements stored in the list
  size_t size_;

};
} // namespace containers
#endif // __LIST_H
