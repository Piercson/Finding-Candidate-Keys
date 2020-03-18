// Want form X determines Y
#pragma once

#include <string>
using namespace std;
class FuncDependency{
  private:
    string x;
    string y;
  public:
    FuncDependency(string x, string y);
    string getX();
    string getY();
    friend ostream& operator <<(ostream& os, const FuncDependency& fd);
};
