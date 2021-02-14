#pragma once

#include <stdexcept>
using namespace std;

template <typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0) {
    if (a_size > N) {
      throw std::invalid_argument("");
    }
    size_ = a_size;
    capacity_ = N;
  }

  T& operator[](size_t index) {
    return data_[index];
  }
  const T& operator[](size_t index) const {
    return data_[index];
  }

  auto begin() {
    return data_;
  }
  auto end() {
    return data_ + size_;
  }
  auto begin() const {
    return data_;
  }
  auto end() const {
    return data_ + size_;
  }

  size_t Size() const {
    return size_;
  }
  size_t Capacity() const {
    return capacity_;
  }

  void PushBack(const T& value) {
    if (size_ < capacity_) {
      data_[size_++] = value;
    } else {
      throw std::overflow_error("");
    }
  }
  T PopBack() {
    if (size_ > 0) {
      return data_[--size_];
    } else {
      throw std::underflow_error("");
    }
  }

private:
  size_t size_;
  size_t capacity_;
  T data_[N];
};

