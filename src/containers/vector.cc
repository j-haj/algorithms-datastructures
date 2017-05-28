#include "vector.h"

namespace containers {

template <typename T>
Vector::Vector() : size_(0), capacity_(2) {
  data_ = std::make_unique<T>(new T[2]);
}

template <typename T>
Vector::Vector(size_t n) : size_(n), capacity_(tools::capacity_for_size(n)) {
  data_ = std::make_unique<T>(new T[capacity_]);
}

template <typename T>
Vector::Vector(std::initializer_list<T> elements) : size_(elements.size()),
  capacity_(tools::capacity_for_size(l.size())) {
  data_ = std::make_unique<T>(new T[capacity_]);
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = elements[i];
  }
}

template <typename T>
Vector::Vector(const Vector& v) : size_(v.size()), capacity_(v.capacity()) {
  data_ = std::make_unique<T>(new T[capacity_]);
  for (size_t i = 0; i < size_; ++i) {
    data_[i] = v[i];
  }
}



template <typename T>
~Vector::Vector() {
  data_.release();
}

} // namespace containers
