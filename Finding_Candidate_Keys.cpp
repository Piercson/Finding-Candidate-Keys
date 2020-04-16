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
// PROBLEM CLOSURE, POWER SET
//Finds the closure of att_x with repect to functional dependancies fd
bool closure(string att_x, vector<FuncDependency> fd,string set_u){
  // Add trivial attributs to closure
  string closure_att = att_x;
  vector<FuncDependency>::iterator it = fd.begin();
  // check through all functional dependancy's
  while( it != fd.end() ){
    //if the rhs of the fd is in the closure attributes
    string rhs = it->getX();
    int rhs_size = rhs.size();
    bool isSubset = true;
    for(int i = 0; i < rhs_size; i++){
      if(closure_att.find(rhs[i]) == string::npos){
        isSubset = false;
        break;
      }
    }
    if(isSubset){
      string lhs = it->getY();
      int size = lhs.size();
      // Add all unique attributes
      for(int i = 0; i < size; i++){
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
  int sum_u = 0;
  int sum_closure = 0;
  int u_size = set_u.size();
  int closure_size = closure_att.size();
  for(int i = 0; i < u_size; i++){
    sum_u += (int)set_u[i];
  }
  for(int i = 0; i < closure_size; i++){
    sum_closure += (int)closure_att[i];
  }
  return (sum_closure == sum_u);
}
//Finds the node in the graph that is a leaf/sink
// *if there is an issue, try loading stack backwards*
int search(list<int>* graph[], int ps_size){
  // create stack for a "DFS" like search
  vector<int> stack;
  int size = ps_size;
  list<int>::iterator it;
  //look for a starting place to do the search
  for(int i = 0; i < size; i++){
    if(graph[i]->empty()){continue;}
    for(it = graph[i]->begin(); it != graph[i]->end(); it++){
      stack.push_back(*it);
    }
    break;
  }
  //start search
  int node;
  while(!stack.empty()){
    node = stack.back();
    stack.pop_back();
    if(graph[node]->empty()){return node;}
    else{
      list<int>::iterator it;
      for(it = graph[node]->begin(); it != graph[node]->end(); it++){
        stack.push_back(*it);
      }
    }

  }
  // if the stack is empty at this point
  //    the graph has no edges
  return -1;
}
void delete_x_ancestors(list<int>* graph[], int node, int ps_size){
  int size = ps_size;
  free(graph[node]);
  graph[node] = new list<int>;
  for(int i = 0; i < size; i++){
    list<int>::iterator it;
    if(graph[i]->empty()){continue;}
    for(it = graph[i]->begin(); it != graph[i]->end(); it++){
      if(*it == node){
        free(graph[i]);
        graph[i] = new list<int>;
        break;
      }
    }
  }
}
void delete_x(list<int>* graph[], int node, int ps_size){
  int size = ps_size;
  free(graph[node]);
  graph[node] = new list<int>;
  for(int i = 0; i < size; i++){
    list<int>::iterator it;
    if(graph[i]->empty()){continue;}
    for(it = graph[i]->begin(); it != graph[i]->end(); it++){
      if(*it == node){
        graph[i]->erase(it);
        break;
      }
    }
  }
}
bool is_graph_empty(list<int>* graph[], int ps_size){
  int size = ps_size;
  for(int i = 0; i < size; i++){
    list<int>::iterator it;
    if(!graph[i]->empty()){return false;}
    }
    return true;
  }
int main(){
  // Start with a Given input
  /*  R(ABCDE)   Sigma = {AB-:C, B-:D, C-:E, D-:A}
      Candidate Key = B
  */
  int num_FD = 4;
  vector<FuncDependency> dependencys;
  dependencys.push_back(FuncDependency("D","A"));
  dependencys.push_back(FuncDependency("F","B"));
  dependencys.push_back(FuncDependency("DF","E"));
  dependencys.push_back(FuncDependency("D","C"));
  //create powerset from u_att
  string U_att = "ABCDEF";
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
  // for(int i = 0; i < ps_size; i++){
  //   dag[i] = nullptr;
  // }
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
      string subset = P_SET->at(j);
      int subset_size = subset.size();
      bool isSubset = true;
      if(i == j){continue;}
      for(int k = 0; k < subset_size; k++){
        if(cur_set.find(subset[k]) == string::npos){
          isSubset = false;
          break;
        }
      }
      if(isSubset){dag[i]->push_back(j);}
    }
    // sets the single attribute set to point to nothing
  }
  // PRINT
  cout << "ITERATE\n";
  list<int>::iterator it;
  for(int i = 0; i < ps_size; i++){
    if(dag[i]->empty()){continue;}
    for(it = dag[i]->begin(); it != dag[i]->end(); it++){
    }
  }
  // THE WHOLE THING TOGETHER!
  cout << "START!\n";
  vector<int> can_key;
  while(!is_graph_empty(dag, ps_size)){
    int index = search(dag, ps_size);
    if(index == -1){break;}
    if(!closure(P_SET->at(index), dependencys, U_att)){
      delete_x(dag, index, ps_size);
    }else{
      delete_x_ancestors(dag, index, ps_size);
      can_key.push_back(index);
    }
  }
  int c_size = can_key.size();
  cout << "Candidate Key: ";
  for(int i = 0; i < c_size; i++){
    cout << P_SET->at(can_key[i]) << " ";
  }
  cout << endl;
  // Clean up
  for(int i = 0; i < ps_size; i++){
    free(dag[i]);
  }
  //closure("AB", dependencys, U_att);
  return 0;
}
