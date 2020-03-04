#include <iostream>
#include <vector>
#include <string>
#include "Powerset.h"

using namespace std;
int main() {
  string s = "ABC";
  Powerset ps = Powerset(s);
  cout << "Size: " << ps.getSize() << endl;
  cout << ps << endl;
  return 0;
}
