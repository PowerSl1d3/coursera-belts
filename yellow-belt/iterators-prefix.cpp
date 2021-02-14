#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
    const std::string prefix) {
  std::string s = prefix;
  auto lower = lower_bound(range_begin, range_end, s,
			   [] (const std::string& lhs, const std::string& rhs) {
		return lhs < rhs;
	});
  s[s.size() - 1]++;
  auto upper = lower_bound(range_begin, range_end, s);

  return make_pair(lower, upper);
}

int main() {
  using namespace std;
  const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};
  
  const auto mo_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
  for (auto it = mo_result.first; it != mo_result.second; ++it) {
    cout << *it << " ";
  }
  cout << endl;
  
  const auto mt_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
  cout << (mt_result.first - begin(sorted_strings)) << " " <<
      (mt_result.second - begin(sorted_strings)) << endl;
  
  const auto na_result =
      FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
  cout << (na_result.first - begin(sorted_strings)) << " " <<
      (na_result.second - begin(sorted_strings)) << endl;
  
  return 0;
}
