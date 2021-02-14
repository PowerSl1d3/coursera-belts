#include <iostream>
#include <vector>
#include <exception>
#include <stdexcept>
#include <iterator>
#include <algorithm>

template <typename T>
class Deque {
private:
  std::vector<T> front;
  std::vector<T> tail;
  size_t size = 0;
public:
  Deque() {}
  bool Empty(void) const {
    if (size == 0) {
      return true;
    }
    return false;
  }
  size_t Size(void) const {
    return size;
  }
  const T& operator[](size_t index) const {
    if (index < front.size()) {
      return front[front.size() - index - 1];
    } else if (index - front.size() < tail.size()) {
      return tail[index - front.size()];
    }
    throw std::out_of_range("");
  }
  T& operator[](size_t index) {
    return const_cast<T&>(static_cast<const Deque&>(*this)[index]);
  }
  const T& At(size_t index) const {
    if (index >= size) {
      throw std::out_of_range("");
    }
    if (index < front.size()) {
      return front[front.size() - index - 1];
    } else if (index - front.size() < tail.size()) {
      return tail[index - front.size()];
    }
    throw std::out_of_range("");
  }
  T& At(size_t index) {
    return const_cast<T&>(static_cast<const Deque&>(*this)[index]);
  }
  const T& Front(void) const {
    if (!front.empty()) {
      return front[front.size() - 1];
    } else if (!tail.empty()) {
      return tail[0];
    }
    throw std::out_of_range("");
  }
  T& Front(void) {
    return const_cast<T&>(static_cast<const Deque&>(*this).Front());
  }
  const T& Back(void) const {
    if (!tail.empty()) {
      return tail[tail.size() - 1];
    } else if (!front.empty()) {
      return front[0];
    }
    throw std::out_of_range("");
  }
  T& Back(void) {
    return const_cast<T&>(static_cast<const Deque&>(*this).Back());
  }
  void PushFront(const T& e) {
    front.push_back(e);
    size++;
  }
  void PushBack(const T& e) {
    tail.push_back(e);
    size++;
  }
};

int main(void) {
  Deque<int> d;

  d.PushFront(1);
  d.PushBack(2);

  std::cout << d.Back() << " " << d.Front() << " " << d[0] << " " << d[1] <<std::endl;
  std::cout << d.Empty() << " " << d.At(0) << " " << d.At(1);
  //std::cout << d.At(2);

  d[0] = 5;
  std::cout << std::endl << d[0] << std::endl;
  
  return 0;
}
