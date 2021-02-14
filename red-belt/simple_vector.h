#pragma once

#include <cstdlib>
#include <algorithm>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector() = default;
  
  explicit SimpleVector(size_t size) {
    data = new T[size];
    size_ = size;
    capacity_ = size;
  }
  
  ~SimpleVector() {
    if (capacity_ == 1) {
      delete data;
    } else  if (capacity_ > 1) {
      delete[] data;
    }
  }

  SimpleVector(const SimpleVector& other)
    : data(new T[other.capacity_])
    , size_(other.size_)
    , capacity_(other.capacity_)
  {}

  //rvalue reference
  SimpleVector(SimpleVector&& other)
    : data(other.data)
    , size_(other.size_)
    , capacity_(other.capacity_)
  {
    other.data = nullptr;
    other.size_ = 0;
    other.capcacity_ = 0;
  }
  
  void operator=(const SimpleVector& other);
  void operator=(SimpleVector&& other);

  T& operator[](size_t index) {
    return data[index];
  }

  const T& operator[](size_t index) const {
    return data[index];
  }

  T* begin() {
    return data;
  }
  
  T* end() {
    return data + size_;
  }

  const T* begin() const {
    return data;
  }
  
  const T* end() const {
    return data + size_;
  }

  size_t Size() const {
    return size_;
  }
  size_t Capacity() const {
    return capacity_;
  }
  void PushBack(const T& value) {
    if (size_ >= capacity_) {
      auto new_cap = capacity_ == 0 ? 1 : 2 * capacity_;
      T* new_data = new T[new_cap];
      for (int i = 0; i < size_; i++) {
		new_data[i] = data[i];
      }
      delete[] data;
      data = new_data;
      capacity_ = new_cap;
    }
    data[size_++] = value;
  }

private:
  T* data = nullptr;
  size_t size_ = 0;
  size_t capacity_ = 0;
};

template <typename T>
void SimpleVector<T>::operator=(const SimpleVector<T>& other) {
  this->~SimpleVector();
  data = new T[other.capacity_];
  std::copy(other.begin(), other.end(), begin());
  size_ = other.size_;
  capacity_ = other.capacity_;
}

template <typename T>
void SimpleVector<T>::operator=(SimpleVector<T>&& other) {
  this->~SimpleVector();
  data = other.data;
  size_ = other.size_;
  capacity_ = other.capacity_;
  other.data = nullptr;
  other.size_ = other.capacity_ = 0;
}
