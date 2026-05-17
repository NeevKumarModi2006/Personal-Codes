#include<bits/stdc++.h>
using namespace std;

struct trnode{
    int eow = 0;
    trnode* ptr[26];
};


void create(trnode* &T, string &s, int i=0){
  if(T==NULL) T = new trnode;
      if(i==s.size()) {
        T->eow = 1;
      return;
      }
  
  create(T->ptr[s[i]-'a'], s,i+1);
}

void print(trnode* T, string s = ""){
    if(!T) return;
    
    if(T->eow==1){
        cout<<s<<" ";
        return;
    }
    
    for(int i = 0; i<26; i++)  print(T->ptr[i], s+char(i+'a'));
  
}

int main(){

trnode* T = NULL;
string s;

while(cin>>s && s!="#")  create(T,s);
print(T);
    
    return 0;
}