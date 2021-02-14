#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

int main(void) {

  std::ifstream input("input.txt");
  std::vector<std::vector<int>> table;
  int N, M, input_value;
  
  if (input.is_open()) {
    input >> N >> M;
    table.resize(N, std::vector<int>(M));
    for (std::vector<int>& i : table) {
      for (int& j : i) {
	input >> j;
	input.ignore(1);
      }
    }
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      std::cout << std::setw(10) << table[i][j];
      if (j + 1 < M) {
	std::cout << ' ';
      }
    }
    if (i + 1 < N) {
      std::cout << std::endl;
    }
  }
  
  return 0;
}
