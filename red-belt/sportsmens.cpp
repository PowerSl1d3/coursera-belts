#include <iostream>
#include <map>
#include <list>
#include <iterator>

int main(void) {

  int N;
  int first_n, second_n;
  std::list<int> players;
  std::map<int, std::list<int>::iterator> players_iterator;

  std::cin >> N;

  for (int i = 0; i < N; i++) {
    std::cin >> first_n >> second_n;

    auto it = players_iterator.find(second_n);
    if (it == players_iterator.end()) {
      players.push_back(first_n);
      players_iterator[first_n] = prev(players.end());
    } else {
      players.insert(it->second, first_n);
      players_iterator[first_n] = prev(it->second);
    }
  }

  for (int x : players) {
    std::cout << x << std::endl;
  }

  return 0;

}
