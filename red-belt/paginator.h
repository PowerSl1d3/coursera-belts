#pragma once

#include <numeric>
#include <iostream>
#include <vector>
#include <string>

template <typename Iterator>
class Page {
public:
  Page(const Iterator& begin, const Iterator& end)
    : begin_(begin)
    , end_(end)
    , size_(std::distance(begin,end))
  {}
  
  Iterator begin() {
    return begin_;
  }

  Iterator end() {
    return end_;
  }

  size_t size() {
    return size_;
  }

  const Iterator begin() const {
    return begin_;
  }

  const Iterator end() const {
    return end_;
  }

  const size_t size() const {
    return size_;
  }
  
private:
  Iterator begin_;
  Iterator end_;
  size_t size_;
};

template <typename Iterator>
class Paginator {
public:
  Paginator(Iterator begin,
	    Iterator end,
	    size_t page_size)
  {
    for (size_t left = std::distance(begin, end); left > 0;) {
      size_t current_page_size = std::min(page_size, left);
      Iterator current_page_end = std::next(begin, current_page_size);
      pages_.push_back({begin, current_page_end});
      begin = current_page_end;
      left -= current_page_size;
    }
  }

  auto begin() {
    return pages_.begin();
  }

  auto end() {
    return pages_.end();
  }
  
  size_t size() {
    return pages_.size();
  }

  const auto begin() const {
    return pages_.begin();
  }

  const auto end() const {
    return pages_.end();
  }
  
  const size_t size() const {
    return pages_.size();
  }
  
private:
  std::vector<Page<Iterator>> pages_;
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
  return Paginator(c.begin(), c.end(), page_size);
}
