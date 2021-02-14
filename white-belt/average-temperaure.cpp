#include <iostream>
#include <vector>
#include <cstdlib>

double average_temp(const std::vector<int>& v) {
  double sum = 0;
  int i = 0;
  for (; i < v.size(); i++) {
    sum += v[i];
  }
  if (i == 0)
    exit(0);
  return sum / i;
}

int main(void) {

  int n;
  std::cin >> n;

  std::vector<int> temperature(n);

  for (auto& t : temperature) {
    std::cin >> t;
  }
  
  double average =  average_temp(temperature);
  std::vector<int> answer;
  
  for (int i = 0; i < temperature.size(); i++) {
    if (temperature[i] > average) {
      answer.push_back(i);
    }
  }

  std::cout << answer.size() << std::endl;

  for (int i = 0; i < answer.size(); i++) {
    std::cout << answer[i];
    if (i + 1 < answer.size()) {
      putchar(' ');
    }
  }
  
  return 0;
}
