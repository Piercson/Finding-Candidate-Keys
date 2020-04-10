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

bool closure(string att_x, vector<FuncDependency> fd,string set_u){
  // Add trivial attributs to closure
  string closure_att = att_x;
  vector<FuncDependency>::iterator it = fd.begin();
  // check through all functional dependancy's
  while( it != fd.end() ){
    cout << *it << endl;
    //if the rhs of the fd is in the closure attributes
    if(closure_att.find(it->getX()) != string::npos){
      string lhs = it->getY();
      int size = lhs.size();
      cout << "LHS is " << lhs << endl;
      // Add all unique attributes
      for(int i = 0; i < size; i++){
        cout << closure_att << " " << lhs.at(i) << endl;
        if(att_x.find(lhs.at(i)) == string::npos){
          closure_att += lhs.at(i);
        }
      }
      //remove attribute since we no longer need it for closure
      fd.erase(it);
      // restart the search
      it = fd.begin();
      continue;
    }
    it++;
  }
  cout << "closure att " << closure_att  << " Set U " << set_u<< endl;
  return (set_u.compare(closure_att) == 0);
}
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
  // index[0] will be all the power set - 1 since
  //  powerset[0] is the largest set of all attributes
  // eg. ABC has subsets A B C AB AC BC
  dag[0] = new list<int>;
  for(int i = 1; i < ps_size; i++){
    dag[0]->push_back(i);
  }
  // Set up the rest of the adj. list
  for(int i = 1; i < ps_size; i++){
    string cur_set = P_SET->at(i);
    int cur_set_size = cur_set.size();
    dag[i] = new list<int>;
    for(int j = setSize[cur_set_size-1]; j < ps_size; j++){
      // checks jth set in Powerset is a subset of the current set
      if(cur_set.find(P_SET->at(j)) != string::npos && i != j){
        dag[i]->push_back(j);
      }
    }
    // sets the single attribute set to point to nothing
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
    if(dag[i] == nullptr){cout << "Empty" << endl; continue;}
    for(it = dag[i]->begin(); it != dag[i]->end(); it++){
      cout << P_SET->at(*it) << " ";
    }
    cout << endl;
  }
  // Clean up
  for(int i = 0; i < ps_size; i++){
    free(dag[i]);
  }
  closure("AB", dependencys, U_att);
  return 0;
}
