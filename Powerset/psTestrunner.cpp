#include <iostream>
#include <vector>
#include <string.h>
#include <algorithm>
#include "Powerset.h"

using namespace std;
int cstring_cmp(const void *a, const void *b)
{
    const char **ia = (const char **)a;
    const char **ib = (const char **)b;
    return strcmp(*ia, *ib);
	/* strcmp functions works exactly as expected from
	comparison function */
}
int main() {
  string s = "ABC";
  Powerset ps = Powerset(s);
  cout << "Size: " << ps.getSize() << endl;
  cout << ps << endl;

  return 0;
}
