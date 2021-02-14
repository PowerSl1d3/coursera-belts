#include <iostream>
#include <queue>
#include <string>
#include <stack>

enum class Priorety {
		     NUL,
		     ADD_SUB,
		     MUL_DIV
};

struct expression {
  int number;
  char operation;
  Priorety p;
};

std::istream& operator>>(std::istream& is, expression& ex) {
  is >> ex.operation >> ex.number;
  switch (ex.operation){
  case '+':
    ex.p = Priorety::ADD_SUB;
    break;
  case '-':
    ex.p = Priorety::ADD_SUB;
    break;
  case '*':
    ex.p = Priorety::MUL_DIV;
    break;
  case '/':
    ex.p = Priorety::MUL_DIV;
    break;
  default:
    ex.p = Priorety::NUL;
    break;
  }
  return is;
}

void IntToChar(int& n, std::deque<char>& d) {
  std::string s = std::to_string(n);
  for (char& c : s) {
    d.push_back(c);
  }
}

int main(void) {
  int start, N;
  expression ex;
  std::deque<char> q;
  Priorety prev_p = Priorety::NUL;
  std::cin >> start >> N;

  IntToChar(start, q);

  for (int i = 0; i < N; i++) {
    std::cin >> ex;

    if (ex.p > prev_p && prev_p != Priorety::NUL) {
      q.push_front('(');
      q.push_back(')');
      q.push_back(' ');
      q.push_back(ex.operation);
      q.push_back(' ');
      IntToChar(ex.number, q);
    } else {
      q.push_back(' ');
      q.push_back(ex.operation);
      q.push_back(' ');
      IntToChar(ex.number, q);
    }
    prev_p = ex.p;
    if (i + 1 == N && prev_p < ex.p) {
      q.pop_front();
      q.pop_back();
    }
  }

  for (auto& i : q) {
    std::cout << i;
  }
  std::cout << std::endl;
}
