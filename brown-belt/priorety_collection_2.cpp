#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template <typename T>
class PriorityCollection {
public:
      
  using Id = int;

  struct Object {
    T value;
    int priority = 0;
  };

    // Добавить объект с нулевым приоритетом
    // с помощью перемещения и вернуть его идентификатор
  Id Add(T object);

  // Добавить все элементы диапазона [range_begin, range_end)
  // с помощью перемещения, записав выданные им идентификаторы
  // в диапазон [ids_begin, ...)
    template <typename ObjInputIt, typename IdOutputIt>
    void Add(ObjInputIt range_begin, ObjInputIt range_end,
	     IdOutputIt ids_begin);

  // Определить, принадлежит ли идентификатор какому-либо
  // хранящемуся в контейнере объекту
  bool IsValid(Id id) const;

  // Получить объект по идентификатору
  const T& Get(Id id) const;

  // Увеличить приоритет объекта на 1
  void Promote(Id id);

  // Получить объект с максимальным приоритетом и его приоритет
  pair<const T&, int> GetMax() const;

  // Аналогично GetMax, но удаляет элемент из контейнера
  pair<T, int> PopMax();

private:
  std::vector<Object> objects;
  std::set<std::pair<int, Id>> sorted_objects;
};

template <typename T>
typename PriorityCollection<T>::Id PriorityCollection<T>::Add(T object) {
  objects.push_back({std::move(object)});
  sorted_objects.insert({0, objects.size() - 1});
  return objects.size() - 1;
}

template <typename T>
template <typename ObjInputIt, typename IdOutputIt>
void PriorityCollection<T>::Add(ObjInputIt range_begin, ObjInputIt range_end,
				IdOutputIt ids_begin) {
  while (range_begin != range_end) {
      *ids_begin++ = Add(move(*range_begin++));
    }
}

template <typename T>
bool PriorityCollection<T>::IsValid(Id id) const {
  return (objects[id].priority > -1) ? true : false;
}

// Получить объект по идентификатору
template <typename T>
const T& PriorityCollection<T>::Get(Id id) const {
  return objects[id].value;
}

// Увеличить приоритет объекта на 1
template <typename T>
void PriorityCollection<T>::Promote(Id id) {
  int old_priority = objects[id].priority++;
  sorted_objects.erase({old_priority++, id});
  sorted_objects.insert({old_priority, id});
}

// Получить объект с максимальным приоритетом и его приоритет
template <typename T>
pair<const T&, int> PriorityCollection<T>::GetMax() const {
  for (auto it = sorted_objects.rbegin(); it != sorted_objects.rend(); it++) {
    if (objects[it->second].priority != -1) {
      return {objects[it->second].value, it->first};
    }
  }
}

// Аналогично GetMax, но удаляет элемент из контейнера
template <typename T>
pair<T, int> PriorityCollection<T>::PopMax() {
  for (auto it = sorted_objects.rbegin(); it != sorted_objects.rend(); it++) {
    if (objects[it->second].priority != -1) {
      int old_priority = objects[it->second].priority;
      Id old_id = it->second;
      objects[it->second].priority = -1;
      sorted_objects.erase({old_priority, it->second});
      return {std::move(objects[old_id].value), old_priority};
    }
  }
  return {};
}


class StringNonCopyable : public string {
public:
  using string::string;  // Позволяет использовать конструкторы строки
  StringNonCopyable(const StringNonCopyable&) = delete;
  StringNonCopyable(StringNonCopyable&&) = default;
  StringNonCopyable& operator=(const StringNonCopyable&) = delete;
  StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
  PriorityCollection<StringNonCopyable> strings;
  const auto white_id = strings.Add("white");
  const auto yellow_id = strings.Add("yellow");
  const auto red_id = strings.Add("red");

  strings.Promote(yellow_id);
  for (int i = 0; i < 2; ++i) {
    strings.Promote(red_id);
  }
  strings.Promote(yellow_id);
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "red");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "yellow");
    ASSERT_EQUAL(item.second, 2);
  }
  {
    const auto item = strings.PopMax();
    ASSERT_EQUAL(item.first, "white");
    ASSERT_EQUAL(item.second, 0);
  }
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestNoCopy);
  return 0;
}
