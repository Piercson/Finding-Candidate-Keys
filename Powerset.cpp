#include <iostream>
#include <vector>
#include <algorithm>
#include "Powerset.h"
#include <typeinfo>
using namespace std;

Powerset::Powerset(string u){
  powerset = createPS(u);
}
bool Powerset::myfunction(const string& i,const string& j){
  cout << i << " " << j << endl;
  return i.size() < j.size();
}
struct Compare {
  bool operator() (string i,string j) {
     return (i.size()>j.size());
   }
} comp;
vector<string>* Powerset::createPS(string u){
  int size = u.size();
  vector<char> t;
  vector<string>* ps;
  ps = new vector<string>;
  createPS(t,u,size,ps);
  ps->pop_back(); // the last set is the empty set
  sort(ps->begin(), ps->end(), comp); // decreasing order based on string size
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
  //not include
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
