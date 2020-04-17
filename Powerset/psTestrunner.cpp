#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include "Powerset.h"

using namespace std;
int main() {
  vector<string> s;
  s.push_back("Title");
  s.push_back("Actor");
  s.push_back("Release");
  s.push_back("Theater");
  s.push_back("Time");

  Powerset ps = Powerset(s);
  const std::vector<vector<string>>* v;
  v = ps.getPowerset();
  cout << "Size: " << v->size() << endl;
  cout << ps << endl;

  return 0;
}
