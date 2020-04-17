#include <iostream>
#include <vector>
#include <algorithm>
#include "Powerset.h"
#include <typeinfo>
using namespace std;

Powerset::Powerset(vector<string> u){
  powerset = createPS(u);
}
// bool Powerset::myfunction(const vector<vector<string>>& i,const vector<vector<string>>& j){
//   cout << i << " " << j << endl;
//   return i.size() < j.size();
// }
struct Compare {
  bool operator() (vector<string> i,vector<string> j) {
     return (i.size()>j.size());
   }
} comp;
vector<vector<string>>* Powerset::createPS(vector<string> u){
  int size = u.size();
  vector<string> t;
  vector<vector<string>>* ps;
  ps = new vector<vector<string>>;
  createPS(t,u,size,ps);
  ps->pop_back(); // the last set is the empty set
  sort(ps->begin(), ps->end(), comp); // decreasing order based on string size
  return ps;
}
/*
  Creates a powerset by either including the n-1 element or no include
  this will find 2^n sets including the empty set
*/
void Powerset::createPS(vector<string> temp, vector<string> u, int n, vector<vector<string>>* ps){
  if(n == 0){
    
    ps->push_back(temp);
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
    int j_size = ps.powerset->at(i).size();
    cout << "(";
    for(int j = 0; j < j_size; j++){
      os << ps.powerset->at(i)[j] << " ";
    }
    cout << ")" <<endl;
  }
  return os;
}
