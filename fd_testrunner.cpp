#include <iostream>
#include <vector>
#include <string>
#include "FuncDependency.h"

using namespace std;
int main() {
  std::vector<char> words1 {'C'};
  std::vector<char> words2 {'A','B'};
  FuncDependency fd = FuncDependency(words1,words2);
  cout << fd;
  return 0;
}
