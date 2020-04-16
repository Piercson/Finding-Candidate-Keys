#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include "Powerset.h"

using namespace std;
int main() {
  vector<string> s;
  s.push_back("A");
  s.push_back("B");
  s.push_back("C");
  s.push_back("D");
  s.push_back("E");

  Powerset ps = Powerset(s);
  const std::vector<vector<string>>* v;
  v = ps.getPowerset();
  cout << "Size: " << ps.getSize() << endl;
  cout << ps << endl;

  return 0;
}
