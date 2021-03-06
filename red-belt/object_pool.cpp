#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate() {
    
    if (objects_free.empty()) {
      T* obj = new T;
      corrupted_obj.insert(obj);
      return obj;
    } else {
      T* obj = objects_free.front();
      corrupted_obj.insert(obj);
      objects_free.pop();
      return obj;
    }
  }
  
  T* TryAllocate() {

    if (objects_free.empty()) {
      return nullptr;
    } else {
      T* obj = objects_free.front();
      corrupted_obj.insert(obj);
      objects_free.pop();
      return obj;
    }
  }

  void Deallocate(T* object) {
    auto it = corrupted_obj.find(object);
    if (it == corrupted_obj.end()) {
      throw std::invalid_argument("");
    } else {
      objects_free.push(object);
      corrupted_obj.erase(object);
    }
  }

  ~ObjectPool() {
    while (!objects_free.empty()) {
      delete objects_free.front();
      objects_free.pop();
    }

    while (!corrupted_obj.empty()) {
      delete *corrupted_obj.begin();
      corrupted_obj.erase(corrupted_obj.begin());
    }
  }

private:
  std::queue<T*> objects_free;
  std::set<T*> corrupted_obj;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
