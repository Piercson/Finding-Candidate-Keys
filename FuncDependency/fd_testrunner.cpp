#include <iostream>
#include <vector>
#include <string>
#include "FuncDependency.h"

using namespace std;
int main() {
  vector<string> words1;
  words1.push_back("C");
  vector<string> words2;
  words2.push_back("A");
  words2.push_back("B");
  FuncDependency fd = FuncDependency(words1,words2);
  cout << fd << endl;
  return 0;
}
