#include <string>
#include <vector>
using namespace std;

#define UNIQ_ID f(__LINE__)

#define f(a) g(a)

#define g(a) _variable##a 

int main() {
  int UNIQ_ID = 0;
  string UNIQ_ID = "hello";
  vector<string> UNIQ_ID = {"hello", "world"};
  vector<int> UNIQ_ID = {1, 2, 3, 4};
}
