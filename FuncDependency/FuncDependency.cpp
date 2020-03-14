#include <iostream>
#include "FuncDependency.h"
using namespace std;
FuncDependency::FuncDependency(string x, string y){
  this->x = x;
  this->y = y;
}
string FuncDependency::getX(){
  return this->x;
}
string FuncDependency::getY(){
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
