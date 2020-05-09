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
//Print for vectors<T>
template <class T>
void print(vector<T> list){
  int size = list.size();
  for(int i = 0; i < size; i++){
    cout << list[i] << " ";
  }
}
//Finds the closure of att_x with repect to functional dependancies fd
bool closure(vector<string> closure_att, vector<FuncDependency> fd, vector<string> set_u){
  vector<FuncDependency>::iterator it = fd.begin();
  // check through all functional dependancy's
  while( it != fd.end() ){
    //if the rhs of the fd is in the closure attributes
    //std::find(x.begin(), x.end(), y[0]) != x.end()
    vector<string> rhs = it->getX();
    int rhs_size = rhs.size();
    bool isSubset = true;
    for(int i = 0; i < rhs_size; i++){
      if(std::find(closure_att.begin(), closure_att.end(), rhs[i]) == closure_att.end()){
        isSubset = false;
        break;
      }
    }
    if(isSubset){
      vector<string> lhs = it->getY();
      int size = lhs.size();
      // Add all unique attributes
      for(int i = 0; i < size; i++){
        if(std::find(closure_att.begin(), closure_att.end(), lhs[i]) == closure_att.end()){
          closure_att.push_back(lhs.at(i));
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
  return (closure_att.size() == set_u.size());
}
//Finds the node in the graph that is a leaf/sink
// *if there is an issue, try loading stack backwards*
int search(list<long>* graph[], long ps_size){
  // create stack for a "DFS" like search
  vector<long> stack;
  list<long>::iterator it;
  //look for a starting place to do the search
  for(long i = 0; i < ps_size; i++){
    if(graph[i]->empty()){continue;}
    for(it = graph[i]->begin(); it != graph[i]->end(); it++){
      stack.push_back(*it);
    }
    break;
  }
  //start search
  long node;
  while(!stack.empty()){
    node = stack.back();
    stack.pop_back();
    if(graph[node]->empty()){return node;}
    else{
      list<long>::iterator it;
      for(it = graph[node]->begin(); it != graph[node]->end(); it++){
        stack.push_back(*it);
      }
    }

  }
  // if the stack is empty at this point
  //    the graph has no edges
  return -1;
}
void delete_x_ancestors(list<long>* graph[], long node, long ps_size){
  free(graph[node]);
  graph[node] = new list<long>;
  for(long i = 0; i < ps_size; i++){
    list<long>::iterator it;
    if(graph[i]->empty()){continue;}
    for(it = graph[i]->begin(); it != graph[i]->end(); it++){
      if(*it == node){
        free(graph[i]);
        graph[i] = new list<long>;
        break;
      }
    }
  }
}
void delete_x(list<long>* graph[], long node, long ps_size){
  free(graph[node]);
  graph[node] = new list<long>;
  for(long i = 0; i < ps_size; i++){
    list<long>::iterator it;
    if(graph[i]->empty()){continue;}
    for(it = graph[i]->begin(); it != graph[i]->end(); it++){
      if(*it == node){
        graph[i]->erase(it);
        break;
      }
    }
  }
}
bool is_graph_empty(list<long>* graph[], long ps_size){
  for(long i = 0; i < ps_size; i++){
    list<long>::iterator it;
    if(!graph[i]->empty()){return false;}
    }
    return true;
  }
vector<string> preset_att(){
  vector<string> U_att;
  U_att.push_back("A");
  U_att.push_back("B");
  U_att.push_back("C");
  U_att.push_back("D");
  U_att.push_back("E");
  cout << "Attributes\n";
  print(U_att);
  cout << endl;
  return U_att;
}
vector<FuncDependency> preset_fd(){
  vector<FuncDependency> dependencys;
  vector<string> rhs;
  vector<string> lhs;
  rhs.push_back("A");
  lhs.push_back("C");
  dependencys.push_back(FuncDependency(rhs,lhs));
  rhs.pop_back();
  lhs.pop_back();

  rhs.push_back("E");
  lhs.push_back("D");
  dependencys.push_back(FuncDependency(rhs,lhs));
  rhs.pop_back();
  lhs.pop_back();

  rhs.push_back("B");
  lhs.push_back("C");
  dependencys.push_back(FuncDependency(rhs,lhs));
  rhs.pop_back();
  lhs.pop_back();
  cout << "Functional Dependencies\n";
  print(dependencys);
  cout << endl;
  return dependencys;
}
vector<string> input_att(){
  // the input for the Attributes
  // attributes are inputted one at a time
  // ; is chosen to stop input because ; is illegal for attribute names
  cout << "Please input unique attributes From your Table\n";
  vector<string> att;
  string inp;
  while(1){
    cout << "Enter attribute\nEnter ; to Finish\n>> ";
    cin >> inp;
    if(inp[0] == ';'){
      if(att.empty()){
        cout << "No attributes";
        continue;
      }else{
        break;
      }
    }
    att.push_back(inp);
  }
  cout << "Attribute are:\n";
  vector<string>::iterator it;
  for(it = att.begin(); it != att.end(); it++){
    cout << *it << endl;
  }
  return att;
}
vector<FuncDependency> input_fd(){
  // input for the functional dependancies
  // , and ; are not allowed in attribute names so they are used to break up the string
  // , are equavilaent to 'and' ex. Title and Date -> Title,Date
  // ; are equavilaent to 'determines' ex. Theater Determines Time -> Theater;Time
  // a ; at the start of the input indicates finishing entering functional dependencies
  vector<FuncDependency> fd;
  cout << "Enter Functional Dependencies using Attribues From your Table\n";
  while(1){
    string inp;
    cout << "Enter Functional Dependencies\nEnter ; to Finish\nFormat[rhs,rhs,..;lhs,lhs,..]\n>> ";
    cin >> inp;
    if(inp[0] == ';'){
      break;
    }
    int size = inp.size();
    vector<string> rhs;
    vector<string> lhs;
    string str = "";
    int i;
    for(i = 0; i < size; i++){
      if(inp[i] == ','){
        rhs.push_back(str);
        str = "";
      }else if(inp[i] == ';'){
        rhs.push_back(str);
        str = "";
        break;
      }else{
        str += inp[i];
      }
    } // for
    // move past ;
    for(i = i + 1; i < size; i++){
      if(inp[i] == ','){
        lhs.push_back(str);
        str = "";
      }else{
        str += inp[i];
      }
    }// for
    lhs.push_back(str);
    fd.push_back(FuncDependency(rhs,lhs));
  }//while
  cout << "Printing Functional Dependencies\n";
  vector<FuncDependency>::iterator it;
  for(it = fd.begin(); it != fd.end(); it++){
    cout << *it << endl;
  }
  return fd;
}
int main(){
  // Start with a Given input
  char input;
  vector<string> U_att;
  vector<FuncDependency> dependencys;
  while(input != '3'){
    cout << "This program finds the set of attributes that are in the candidate key\n";
    cout << "[1]: Input a set of attributes along with dependancies\n";
    cout << "[2]: A preset input\n";
    cout << "[3]: Exit\n";
    cout << "Select an option >> ";
    cin >> input;
    switch(input){
      case '1':
        U_att = input_att();
        dependencys = input_fd();
        break;
      case '2':
        U_att = preset_att();
        dependencys = preset_fd();
        break;
      case '3':
        return 0;
      default:
        continue;
    }
    //Start!
    cout << "Finding Candidate Keys...\n";
    Powerset set = Powerset(U_att);
    long ps_size = set.getSize();
    vector<vector<string>>* P_SET;
    P_SET = set.getPowerset();
    // The powerset is organized from larger set at [0]
    //  to smaller sets [2^U]
    int amt_att = U_att.size();
    // setSize[0] translates to set size of 1 is from ps_size - setSize[0]
    // setSize[1] translates tp set size of 2 is from setSize[0] - setSize[1]
    long setSize[amt_att];
    long setSize_i = 0;
    long cur_set_size = P_SET->at(ps_size-1).size();
    for(long i = ps_size-1; i >= 0; i--){
      if(P_SET->at(i).size() != cur_set_size){
        setSize[setSize_i++] = i + 1;
        cur_set_size = P_SET->at(i).size();
      }
    }
    setSize[amt_att-1] = 0;
    // create adjacency list
    list<long>* dag[ps_size];
    // index[0] will be all the power set - 1 since
    //  powerset[0] is the largest set of all attributes
    // eg. ABC has subsets A B C AB AC BC
    dag[0] = new list<long>;
    for(long i = 1; i < ps_size; i++){
      dag[0]->push_back(i);
    }
    // Set up the rest of the adj. list
    for(long i = 0; i < ps_size; i++){
      vector<string> cur_set = P_SET->at(i);
      long cur_set_size = cur_set.size();
      dag[i] = new list<long>;
      //cout << "i: " << i << endl;
      for(long j = setSize[cur_set_size-1]; j < ps_size; j++){
        //cout << "j: " << j << endl;
        vector<string> subset = P_SET->at(j);
        int subset_size = subset.size();
        bool isSubset = true;
        if(i == j){continue;}
        for(int k = 0; k < subset_size; k++){
          if(std::find(cur_set.begin(), cur_set.end(), subset[k]) == cur_set.end()){
            isSubset = false;
            break;
          }
        }
        if(isSubset){dag[i]->push_back(j);}
      }
    }
    // THE WHOLE THING TOGETHER!
    vector<long> can_key;
    while(!is_graph_empty(dag, ps_size)){
      long index = search(dag, ps_size);
      if(index == -1){break;}
      if(!closure(P_SET->at(index), dependencys, U_att)){
        delete_x(dag, index, ps_size);
      }else{
        delete_x_ancestors(dag, index, ps_size);
        can_key.push_back(index);
      }
    }
    // Print Candidate key
    int c_size = can_key.size();
    cout << "Size: " << c_size << endl;
    cout << "Candidate Key: ";
    for(int i = 0; i < c_size; i++){
      cout << "{";
      print(P_SET->at(can_key[i]));
      cout << "}";
    }
    cout << endl;
    // Clean up
    for(int i = 0; i < ps_size; i++){
      free(dag[i]);
    }
    free(dag);
  }// WHILE
  return 0;
}
