#include <iostream>
#include "FuncDependency.h"
using namespace std;
FuncDependency::FuncDependency(vector<string> x, vector<string> y){
  this->x = x;
  this->y = y;
}
vector<string> FuncDependency::getX(){
  return this->x;
}
vector<string> FuncDependency::getY(){
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
