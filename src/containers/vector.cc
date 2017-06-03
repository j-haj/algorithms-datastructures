#include "vector.h"
#include "tools/tools.h"

#include <memory>
namespace containers {

template <typename T>
Vector<T>::Vector(size_t n) : size_(n), capacity_(tools::capacity_for_size(n)) {
  data_ = std::make_unique<T[]>(new T[capacity_]);
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> elements) : size_(elements.size()),
  capacity_(tools::capacity_for_size(l.size())) {
  data_ = std::make_unique<T>(new T[capacity_]);
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = elements[i];
  }
}

template <typename T>
Vector<T>::Vector(const Vector& v) : size_(v.size()), capacity_(v.capacity()) {
  data_ = std::make_unique<T>(new T[capacity_]);
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = v[i];
  }
}

template <typename T>
Vector<T>::Vector(const Vector&& v) : size_(v.size()), capacity_(v.capacity()) {
  data_ = std::move(v.data_);
}

template <typename T>
~Vector<T>::Vector() {
  data_.release();
}

template <typename T>
size_t Vector<T>::size() const {
  return size_;
}

template <typename T>
size_t Vector<T>::capacity() {
  return capacity_;
}

} // namespace containers
