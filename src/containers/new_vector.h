#ifndef __VECTOR_H
#define __VECTOR_H

#include <cstddef>
#include <experimental/optional>
#include <memory>
#include <stdexcept>

#include "tools/tools.h"

namespace jtl {

  using optional = std::experimental::optional;

/**
 * Vector class
 * Vectors are dynmacially resized, generic containers. This vector
 * implmentation may differ somewhat from a standard implementation in that the
 * underlying data uses a unique pointer, meaning it can only have a single
 * owner at any given time.
 */
template <typename T, typename Allocator = std::allocator<T>>
class Vector {
 public:
  /**
   * Cosntruct a vector via list initialization.
   *
   * @param elements list of elements
   */
  Vector(std::initializer_list<T> elements) : {
    impl_(new VectorImpl<T, Allocator>(elements));
  }

  /**
   * Contruct a vector that ``n`` elements
   *
   * @param number of elements to be insertedin vector
   */
  Vector(size_t n) : { impl_(new VectorImpl<T, Allocator>(n)); }

  /**
   * Copy constructor
   *
   * Copy construction for the `Vector` class works by copying each of the
   * elements in the copied vector. This may or may not be copy by value
   * depending on the element type.
   *
   * @param v vector whose elements will be copied to create a new fector
   */
  Vector(const Vector& v) noexcept {
    const size_t size = v.size();
    impl_(new VectorImpl(size));
    for (size_t i = 0; i < size; ++i) {
      impl_[i] = v[i];
    }
  }

  /**
   * Copy assignement
   *
   * @param v vector whose elements are being copied
   *
   * @return this
   */
  Vector& operator=(const Vector& v) noexcept {
    const size_t isize = impl_->size();
    const size_t vsize = v.size();

    // Need to make sure there is enough room to copy the elements
    imply_->set_size(vsize);

    for (size_t i = 0; i < vsize; ++i) {
      impl_[i] = v[i];
    }

    return *this;
  }

  /**
   * Move constructor
   *
   * Moves the data of `v` to newly created vector by transferring `impl_`. 
   * `v`'s destructor is called at the end of the construction.
   */
  Vector(Vector&& v) : impl_(std::move(v.impl_)) {
    delete v;
  }

  /**
   * Move assignment
   *
   * Moves `v`' `impl_` to `this` and calls `v`'s destructor
   *
   * @param v vector whose data is being moved
   */
  Vector& operator=(Vector&& v) {
    impl_(std::move(v));
    delete v;
  }

  /**
   * Destructor
   */
  ~Vector() { delete impl_; }

  /**
   * Indexing
   */
  T operator[](const size_t i) const { return impl_[i]; }


  // --------------------------------------------------------------------------
  //
  // MEMBER FUNCTIONS
  //
  // --------------------------------------------------------------------------

  /**
   * Append data to the end of the vector
   *
   * @param x data being appended to the vector
   */
  void push_back(const T& x) noexcept {
    impl_->push_back(x);
  }

  /**
   * Returns the element at the specified index and removes it from the vector.
   * This operation has worst-case complexity of O(n), which occurs when the
   * first element is popped, since the remaining elements must be shifted
   * forward one position.
   *
   * @param i index of element being popped
   *
   * @return element at index `i`
   */
  T pop(size_t i = 0) {
    if (impl_->size() == 0) {
      throw std::runtime_error("cannot pop from an empty vector");
    }
    return impl_->pop(i);
  }
  
  /**
   * Attempts to get the element at `i`. If the given index is out of bounds,
   * then no value is returned via the optional type.
   *
   * @param i index of element being requested
   * 
   * @return `std::optional` type possibly containing the requested element
   */
  containers::optional<T> get(size_t i) noexcept {
    if (i >= impl_->size()) {
      return optional<T>();
    }
    return optional<T>(impl_->data_[i]);
  }

  /**
   * Returns the size of the vector (number of elements in the vector)
   *
   * @return the number of elements in the vector
   */
  size_t size() const noexcept { return impl_->size(); }

  /**
   * Returns the number of elements the vector can hold before needing to
   * allocate additional memory
   *
   * @return number of elements vector can hold without need to allocate
   * additional memory.
   */
  size_t capacity() const noexcept { return impl_->capacity(); }

 private:
  std::unique_ptr<VectorImpl> impl_;
}; // class Vector

}  
template <typename T, typename Allocator=std::allocator<T>>
class VectorImpl {

 public:
  VectorImpl(std::initializer_list<T> elements)
      : alloc_(Allocator<T>())
        size_(elements.size()),
        capacity_(tools::capacity_for_size(elements.size())),
        data_(std::unique_ptr<T[]>(new T[elements.size()])) {
    size_t idx(0);
    for (auto it = elements.begin(); it != elements.end(); ++it) {
      data_[idx] = *it;
      ++idx;
    }
  };

  VectorImpl(std::size_t n)
      : size_(n),
        capacity_(tools::capacity_for_size(n)),
        data_(std::unique_ptr<T[]>(new T[capacity_])){};

  ~VectorImpl() { delete[] data_; }

  /**
   * Construct an empty vector
   */
  VectorImpl()
      : size_(0), capacity_(2), data_(std::unique_ptr<T[]>(new T[2])){};

  /**
   * Copy constructor
   *
   * @param v vector whose elements will be copied to create new vector
   */
  VectorImpl(const Vector& v)
      : size_(v.size()),
        capacity_(v.capacity()),
        data_(std::unique_ptr<T[]>(new T[capacity_])) {
    for (std::size_t i = 0; i < size_; ++i) {
      data_[i] = v[i];
    }
  };

  /**
   * Copy assignment
   *
   * @param v vector whoe elements will be copied to create a new vector
   */
  VectorImpl& operator=(const VectorImpl& v) {
    if (size_ != v.size()) {
      throw std::runtime_error("Vectors must have same size when copying");
    }
    for (std::size_t i = 0; i < size_; ++i) {
      data_[i] = v.data_[i];
    }
    return *this;
  }

  /**
   * Move constructor - moves the data of ``v`` to newly created vector's
   * ``data_`` ptr. ``v``'s destructor will be called after its data is moved.
   *
   * @param v vector whose data is being moved
   */
  VectorImpl(VectorImpl&& v) noexcept
      : size_(v.size()), capacity_(v.capacity()), data_(std::move(v.data_)) {}

  /**
   * Move assignment
   *
   * @param v vector whose data is being moved
   */
  VectorImpl& operator=(VectorImpl&& v) {
    if (size_ != v.size()) {
      size_ = v.size();
      capacity_ = v.capacity_();
    }
    data_ = std::move(v.data_);
  }
  /**
   * Indexing
   *
   * @return value at index ``i``
   */
  T operator[](const std::size_t i) const { return data_[i]; }

  ~VectorImpl() {
    size_ = 0;
    capacity_ = 0;
    data_.release();
    alloc_;
  }

  //-------------------------------------------------------------------------
  //
  // Member functions
  //
  //-------------------------------------------------------------------------

  /**
   * Append data to end of vector
   *
   * @param x data that will be appended to vector
   */
  void push_back(const T& x) {
    if (size_ == capacity_) {
      // allocate more memory
      capacity_ *= growth_factor_;
      std::unique_ptr<T[]> tmp = std::unique_ptr<T[]>(new T[capacity_]);

      // move data to new memory
      for (size_t i = 0; i < size_; ++i) {
        std::swap(tmp[i], data_[i]);
      }
      data_.swap(tmp);
      data_[size_ + 1] = x;
      ++size_;
    } else {
      data_[size_ + 1] = x;
      ++size_;
    }
  }

  /**
   * Returns the element at the specified index and removes it from the
   * vector. This operation has worst-case complexity of O(n) (when the first
   * element is moved, due to the remaining elements being shifted forward a
   * position).
   *
   * @param index index of element being popped
   *
   * @return element at ``index``
   */
  T pop(size_t index = 0) {
    if (size_ == 0) {
      throw std::runtime_error("Cannot pop from an empty vector");
    }
    T val = data_[index];
    for (size_t i = index; i < size_; ++i) {
      std::swap(data_[i], data_[i + 1]);
    }
    --size_;
    return val;
  }

  /**
   * Attempts to get the element at ``index``. If the given index is out of
   * bounds, then no value is returned via the optional type.
   *
   * @param index index of element being requested
   *
   * @return ``std::optional`` type possibly containing the requested element
   */
  std::experimental::optional<T> get(size_t index) noexcept {
    if (index >= size_) {
      return std::experimental::optional<T>();
    }
    return std::experimental::optional<T>(data_[index]);
  }

  /**
   * Sets the size of the container, allocating additional space if necessary
   *
   * @param size the amount of space requested for the vector
   */
  void set_size(size_t size) {
    if (size == size_) {
      return;
    }

  }

  /**
   * Returns the size of the vector (number of elements in vector)
   *
   * @return the number of elements in the vector
   */
  std::size_t size() const { return size_; }

  /**
   * Returns the number of elements that can be added to the vector before
   * more memory will be allocated.
   *
   * @return number of elements the vector can hold before more memory is
   * allocated.
   */
  long capacity() const { return capacity_; }

 private:
  /// Size represents the number of elements stored in the vector
  std::size_t size_;

  /// Capacity is the number of elements that can be stored in the vector before
  /// more memory needs to be allocated
  long capacity_;

  /// The amount by which the capacity increases each time capacity is used up
  long growth_factor_ = 2;

  /// Pointer to the underlying data
  std::unique_ptr<T[]> data_;

  /// Allocated enough memory to hold `size`
  void allocate_size(size_t size) {
    if (size <= size_) {
      return;
    }
    size_t new_capacity = tools::capacity_for_size(size);

    // TODO: what's the best way to allocate memory for greater capacity and
    // move elements over?
  }

};  // class VectorImpl
// namespace containers

#endif  // __VECTOR_H
