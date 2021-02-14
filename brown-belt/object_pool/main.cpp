#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
#include <list>
using namespace std;

template <class T>
class ObjectPool {
public:
    T* Allocate() {
        if (!free_objects.empty()) {
            T* item = free_objects.front();
            corrupted_objects.insert(item);
            free_objects.pop();
            return item;
        }

        T* item = new T;
        corrupted_objects.insert(item);

        return item;
    }

    T* TryAllocate() {
        if (!free_objects.empty()) {
            T* item = free_objects.front();
            corrupted_objects.insert(item);
            free_objects.pop();
            return item;
        }

        return nullptr;
    }

    void Deallocate(T* object) {
        auto node = corrupted_objects.extract(object);
        if (node.empty()) {
            throw std::invalid_argument("");
        }
        free_objects.push(node.value());
    }

    ~ObjectPool() {
        while (!free_objects.empty()) {
            delete free_objects.front();
            free_objects.pop();
        }

        while (!corrupted_objects.empty()) {
            delete *corrupted_objects.begin();
            corrupted_objects.erase(corrupted_objects.begin());
        }
    }

private:
    std::set<T*> corrupted_objects;
    std::queue<T*> free_objects;
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
