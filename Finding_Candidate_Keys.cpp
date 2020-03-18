#include <iostream>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include "Powerset.h"
#include <string.h>
#include <list>
#include "FuncDependency.h"
#include <bits/stdc++.h>
using namespace std;



int main(){
  // Start with a Given input
  /*  R(ABCDE)   Sigma = {AB-:C, B-:D, C-:E, D-:A}
      Candidate Key = B
  */
  int num_FD = 4;
  vector<FuncDependency> dependencys;
  dependencys.push_back(FuncDependency("AB","C"));
  dependencys.push_back(FuncDependency("B","D"));
  dependencys.push_back(FuncDependency("C","E"));
  dependencys.push_back(FuncDependency("D","A"));
  //create powerset from u_att
  string U_att = "ABCDE";
  Powerset set = Powerset(U_att);
  int ps_size = set.getSize();
  const std::vector<string>* P_SET;
  P_SET = set.getPowerset();
  // The powerset is organized from larger set at [0]
  //  to smaller sets [2^U]
  int amt_att = U_att.size();
  // setSize[0] translates to set size of 1 is from ps_size - setSize[0]
  // setSize[1] translates tp set size of 2 is from setSize[0] - setSize[1]
  int setSize[amt_att];
  int setSize_i = 0;
  int cur_set_size = P_SET->at(ps_size-1).size();
  for(int i = ps_size-1; i >= 0; i--){
    if(P_SET->at(i).size() != cur_set_size){
      setSize[setSize_i++] = i + 1;
      cur_set_size = P_SET->at(i).size();
    }
  }
  cout << "CREATE\n";
  // create adjacency list
  list<int>* dag[ps_size];
  for(int i = 0; i < ps_size; i++){
    dag[i] = nullptr;
  }
  dag[0] = new list<int>;
  for(int i = 1; i < ps_size; i++){
    dag[0]->push_back(i);
  }
  cout << "SET UP\n";
  for(int i = 1; i < ps_size; i++){
    string cur_set = P_SET->at(i);
    int cur_set_size = cur_set.size();
    dag[i] = new list<int>;
    for(int j = setSize[cur_set_size-1]; j < ps_size; j++){
      if(cur_set.find(P_SET->at(j)) != string::npos && i != j){
        dag[i]->push_back(j);
      }
    }
    if(dag[i]->size() == 0){
      cout << "Delete " << i << endl;
      delete dag[i];
      dag[i] = nullptr;
    }
  }
  // PRINT
  cout << "ITERATE\n";
  list<int>::iterator it;
  for(int i = 0; i < ps_size; i++){
        cout << "Set: " << P_SET->at(i) << " contains ";
    if(dag[i] == nullptr){cout << endl; continue;}
    for(it = dag[i]->begin(); it != dag[i]->end(); it++){
      cout << P_SET->at(*it) << " ";
    }
    cout << endl;
  }
  cout << "nullptr ch:\n";
  if(dag[30] == nullptr){
    cout << "tru\n";
  }
  // for(int i = 0; i<ps_size;i++){
  //   cout << dag[i].size() << endl;
  // }
  // list<int>::iterator it;
  // for(it = dag->begin(); it != dag->end(); it++){
  //   cout << *it << " ";
  // }
  //Delete pointers
  for(int i = 0; i < ps_size; i++){
    free(dag[i]);
  }
  return 0;
}
