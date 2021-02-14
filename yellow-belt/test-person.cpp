#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
      os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};


void CheckFullNameHistory() {
  {
    Person p;
    p.ChangeFirstName(1800, "Maria");
    AssertEqual(p.GetFullName(1800), "Maria with unknown last name");
    AssertEqual(p.GetFullName(1799), "Incognito");
    AssertEqual(p.GetFullName(1801), "Maria with unknown last name");
  }
  {
    Person p;
    p.ChangeLastName(1800, "Shildt");
    AssertEqual(p.GetFullName(1800), "Shildt with unknown first name");
    AssertEqual(p.GetFullName(1799), "Incognito");
    AssertEqual(p.GetFullName(1801), "Shildt with unknown first name");
  }
  {
    Person p;
    p.ChangeFirstName(1800, "Maria");
    p.ChangeFirstName(1805, "Helen");
    p.ChangeFirstName(1806, "Gracy");
    p.ChangeLastName(1801, "Broke");
    p.ChangeLastName(1805, "Green");
    AssertEqual(p.GetFullName(1800), "Maria with unknown last name");
    AssertEqual(p.GetFullName(1801), "Maria Broke");
    AssertEqual(p.GetFullName(1805), "Helen Green");
    AssertEqual(p.GetFullName(1807), "Gracy Green");
  }
  {
    Person p;
    p.ChangeFirstName(1800, "Maria");
    p.ChangeLastName(1799, "Broke");
    p.ChangeLastName(1805, "Green");
    AssertEqual(p.GetFullName(1799), "Broke with unknown first name");
    AssertEqual(p.GetFullName(1800), "Maria Broke");
    AssertEqual(p.GetFullName(1806), "Maria Green");
  }
}

void CheckIncognito() {
  Person p;
  AssertEqual(p.GetFullName(1800), "Incognito");
}

int main() {
  TestRunner runner;
  runner.RunTest(CheckIncognito, "CheckIncognito");
  runner.RunTest(CheckFullNameHistory, "FullNameHistory");
  // добавьте сюда свои тесты
  return 0;
}
