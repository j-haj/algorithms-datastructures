#ifndef __VECTOR_H
#define __VECTOR_H

#include <cstddef>
#include <experimental/optional>
#include <memory>
#include <stdexcept>

#include "tools/tools.h"

namespace containers {
/**
 * Vector class
 * Vectors are dynmacially resized, generic containers. This vector
 * implmentation may differ somewhat from a standard implementation in that the
 * underlying data uses a unique pointer, meaning it can only have a single
 * owner at any given time.
 */
template <typename T>
class Vector {
  public:
    /**
     * Cosntruct a vector via list initialization.
     *
     * @param elements list of elements
     */
    Vector(std::initializer_list<T> elements) : size_(elements.size()),
      capacity_(tools::capacity_for_size(elements.size())),
      data_(std::unique_ptr<T[]>(new T[elements.size()])) {
        size_t idx(0);
        for (auto it = elements.begin(); it != elements.end(); ++it) {
          data_[idx] = *it;
          ++idx;
        }
      };

    /**
     * Contruct a vector that ``n`` elements
     *
     * @param number of elements to be insertedin vector
     */
    Vector(std::size_t n) : size_(n), capacity_(tools::capacity_for_size(n)), 
    data_(std::unique_ptr<T[]>(new T[capacity_])) {};

    /**
     * Construct an empty vector
     */
    Vector() : size_(0), capacity_(2), data_(std::unique_ptr<T[]>(new T[2])) {};

    /**
     * Copy constructor
     *
     * @param v vector whose elements will be copied to create new vector
     */
    Vector(const Vector& v) : size_(v.size()), capacity_(v.capacity()),
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
    Vector& operator=(const Vector& v) {
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
    Vector(Vector&& v) noexcept : size_(v.size()), capacity_(v.capacity()),
      data_(std::move(v.data_)) {}

    /**
     * Move assignment
     *
     * @param v vector whose data is being moved
     */
    Vector& operator=(Vector&& v) {
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
    
    /**
     * Destructor
     */
    ~Vector() {
      size_ = 0;
      capacity_ = 0;
      data_.release();
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
    T pop(size_t index=0) {
      if (size_ == 0) {
        throw std::runtime_error("Cannot pop from an empty vector");
      }
      T val = data_[index];
      for (size_t i = index; i < size_; ++i) {
        std::swap(data_[i], data_[i+1]);
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

}; // class Vector

} // namespace containers

#endif // __VECTOR_H
