#include <iostream>
#include <vector>
#include <string>
#include "FuncDependency.h"

using namespace std;
int main() {
  string words1 = "C";
  string words2 = "AB";
  FuncDependency fd = FuncDependency(words1,words2);
  cout << fd;
  return 0;
}
