// Want form X determines Y
#pragma once
#include <vector>
#include <string>
using namespace std;
class FuncDependency{
  private:
    vector<string> x;
    vector<string> y;
  public:
    FuncDependency(vector<string> x, vector<string> y);
    vector<string> getX();
    vector<string> getY();
    friend ostream& operator <<(ostream& os, const FuncDependency& fd);
};
