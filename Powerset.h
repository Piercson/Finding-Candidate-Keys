
#pragma once
#include <vector>
#include <string>
using namespace std;
class Powerset{
  private:
    vector<vector<string>>* powerset;
    vector<vector<string>>* createPS(vector<string> u);
    //bool myfunction(const vector<string>& i,const vector<string>& j);
    void createPS(vector<string> temp, vector<string> u, int n, vector<vector<string>>* ps);
  public:
    Powerset(vector<string> u);
    friend ostream& operator <<(ostream& os, const Powerset& ps);
    int getSize() { return powerset->size(); };
    vector<vector<string>>* getPowerset(){ return powerset; }
};
