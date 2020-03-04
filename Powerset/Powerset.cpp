#include <iostream>
#include <vector>
#include "Powerset.h"
using namespace std;

Powerset::Powerset(string u){
  powerset = createPS(u);
}
vector<string>* Powerset::createPS(string u){
  int size = u.size();
  vector<char> t;
  vector<string>* ps;
  ps = new vector<string>;
  createPS(t,u,size,ps);
  ps->pop_back(); // the last set is the empty set
  return ps;
}
/*
  Creates a powerset by either including the n-1 element or no include
  this will find 2^n sets including the empty set
*/
void Powerset::createPS(vector<char> temp, string u, int n, vector<string>* ps){
  if(n == 0){
    int size = temp.size();
    string s = "";
    for(int i = 0; i < size; i++){
      s += temp[i];
    }
    ps->push_back(s);
    return;
  }
  //include
  temp.push_back(u[n-1]);
  createPS(temp,u,n-1,ps);
  // or not include
  temp.pop_back();
  createPS(temp,u,n-1,ps);
}
ostream& operator <<(ostream& os, const Powerset& ps){
  int size = ps.powerset->size();
  for(int i = 0; i < size; i++){
    os << "(" << ps.powerset->at(i) << ") ";
  }
  return os;
}
