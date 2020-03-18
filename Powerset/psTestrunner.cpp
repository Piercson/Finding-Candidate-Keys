#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include "Powerset.h"

using namespace std;
int main() {
  string s = "ABCDE";
  Powerset ps = Powerset(s);
  const std::vector<string>* v;
  v = ps.getPowerset();
  cout << "Size: " << ps.getSize() << endl;
  cout << v->at(0) << endl;

  return 0;
}
