// Want form X determines Y
#pragma once

#include <vector>
using namespace std;
class FuncDependency{
  private:
    vector<char> x;
    vector<char> y;
  public:
    FuncDependency(vector<char> x, vector<char> y);
    vector<char> getX();
    vector<char> getY();
    friend ostream& operator <<(ostream& os, const FuncDependency& fd);
};
