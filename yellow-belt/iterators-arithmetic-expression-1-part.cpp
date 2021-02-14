#include <iostream>
#include <queue>
#include <string>
#include <sstream>

struct expression {
  int number;
  char operation;
};

std::istream& operator>>(std::istream& is, expression& ex) {
  is >> ex.operation >> ex.number;
  return is;
}

std::string MakeExpression(const int& start, std::queue<expression>& q) {
  std::stringstream ss;
  expression ex;

  if (q.empty()) {
    return std::to_string(start);
  }
  
  for (int i = 1; i < q.size(); i++) {
    ss << "(";
  }
  
  ss << "(" << start << ")";

  while (!q.empty()) {
    ex = q.front();
    q.pop();
    ss << " " << ex.operation << " " << ex.number;
    if (q.size() > 0) {
      ss << ")";
    }
  }

  return ss.str();
}

int main(void) {
  int start, N;
  expression ex;
  std::queue<expression> q;
  std::cin >> start >> N;

  for (int i = 0; i < N; i++) {
    std::cin >> ex;
    q.push(ex);
  }

  std::cout << MakeExpression(start, q) << std::endl;
}
