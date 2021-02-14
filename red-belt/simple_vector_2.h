#include <cstdint>
#include <algorithm>
#include <iterator>

using namespace std;

// Реализуйте SimpleVector в этом файле
// и отправьте его на проверку

template <typename T>
class SimpleVector {
public:
  SimpleVector()
    : data_(nullptr)
    , size_(0u)
    , capacity_(0u)
  {}
  explicit SimpleVector(size_t size)
    : data_(new T[size])
    , size_(size)
    , capacity_(size)
  {}
  ~SimpleVector();

  T& operator[](size_t index);

  T* begin();
  T* end();
  const T* begin() const;
  const T* end() const;

  size_t Size() const;
  size_t Capacity() const;
  void PushBack(T value);

  // При необходимости перегрузите
  // существующие публичные методы

private:
  T* data_ = nullptr;
  size_t size_;
  size_t capacity_;
};

template <typename T>
SimpleVector<T>::~SimpleVector() {
  delete[] data_;
}

template <typename T>
T& SimpleVector<T>::operator[](size_t index) {
  return data_[index];
}

template <typename T>
T* SimpleVector<T>::begin() {
  return data_;
}

template <typename T>
T* SimpleVector<T>::end() {
  return data_ + size_;
}

template <typename T>
const T* SimpleVector<T>::begin() const {
  return data_;
}

template <typename T>
const T* SimpleVector<T>::end() const {
  return data_ + size_;
}

template <typename T>
size_t SimpleVector<T>::Size() const {
  return size_;
}

template <typename T>
size_t SimpleVector<T>::Capacity() const {
  return capacity_;
}

template <typename T>
void SimpleVector<T>::PushBack(T value) {
  if (size_ == capacity_) {
    size_t new_cap = (capacity_ == 0) ? 1 : capacity_ * 2;
    T* new_data = new T[new_cap];
    std::move(begin(), end(), new_data);
    delete[] data_;
    data_ = new_data;
    capacity_ = new_cap;
  }
  data_[size_++] = std::move(value);
}


