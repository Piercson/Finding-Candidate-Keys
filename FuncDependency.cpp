#include <iostream>
#include <vector>
#include "FuncDependency.h"
using namespace std;
FuncDependency::FuncDependency(vector<char> x, vector<char> y){
  this->x = x;
  this->y = y;
}
vector<char> FuncDependency::getX(){
  return this->x;
}
vector<char> FuncDependency::getY(){
  return this->y;
}
ostream& operator <<(ostream& os, const FuncDependency& fd){
  int xSize = fd.x.size();
  int ySize = fd.y.size();
  for(int i = 0; i < xSize; i++){
    os << fd.x[i] << " ";
  }
  os << "Determines ";
  for(int i = 0; i < ySize; i++){
    os << fd.y[i] << " ";
  }
  return os;
}
