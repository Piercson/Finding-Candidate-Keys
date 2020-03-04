
#pragma once
#include <vector>
#include <string>
using namespace std;
class Powerset{
  private:
    vector<string>* powerset;
    vector<string>* createPS(string u);
    bool myfunction(const string& i,const string& j);
    void createPS(vector<char> temp, string u, int n, vector<string>* ps);
  public:
    Powerset(string u);
    friend ostream& operator <<(ostream& os, const Powerset& ps);
    int getSize() { return powerset->size(); };
    const vector<string>* getPowerset(){ return powerset; }
};
