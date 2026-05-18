#include<bits/stdc++.h>
using namespace std;

struct trnode{
    int eow = 0;
    trnode* ptr[26] = {NULL};
};

void create(trnode* &T, string &s, int i=0){
  if(T==NULL) T = new trnode;
  if(i==s.size()) {
    T->eow = 1;
    return;
  }
    create(T->ptr[s[i]-'a'], s,i+1);
}

unordered_map<string, bool> dp;

bool find(trnode* T, string &s, int i=0){
    if(!T) return false;
    if(i == s.size()) return T->eow;
    return find(T->ptr[s[i] - 'a'], s, i+1);
}

bool wordBreak1(trnode* T, string s){
    if(s.empty()) return true;
    if(dp.find(s) != dp.end()) return dp[s];

    for(int i = 1; i <= s.size(); i++){
        string before = s.substr(0, i);     
        string after = s.substr(i, s.size()-i);
        if(find(T, before) && wordBreak1(T, after))  return dp[s] = true;
    }
    
    return dp[s] = false;
}

int main(){

trnode* T = NULL;
string s;

while(cin>>s && s!="#")  create(T,s);
cin>>s;

cout << (wordBreak1(T, s) ? "true" : "false") << endl;

    return 0;
}