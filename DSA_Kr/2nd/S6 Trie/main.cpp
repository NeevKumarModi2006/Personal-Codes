#include<bits/stdc++.h>
using namespace std;

struct trie{
  bool eow = false;
  trie* ptr[26] = {NULL};
};

void create(trie* &T,string &s, int i=0){
    if(!T) T = new trie;
    if(i==s.size()){
        T->eow = true;
        return;
    }
    create(T->ptr[s[i]-'a'], s, i+1);
}

unordered_map<string, int>mpp;

void print(trie* T, string s = ""){
    if(!T) return;
    if(T->eow){
        cout<<s<<" ";

    }
    for(int i=0; i<26; i++) if(T->ptr[i]) print(T->ptr[i],s + char(i+'a'));
}

bool find(trie* T, string &s, int i=0){
    if(!T) return false;
    if(T->eow && i==s.size()) return true;
    for(int i=0; i<26; i++) if(find(T->ptr[s[i]-'a'],s, i+1)) return true;
}

void s6(trie* TR,trie* T, string s = ""){
    if(!T) return;
    if(T->eow){
        
        
        
        // string p = s;
        // reverse(p.begin(),p.end());
        
    // if(p!=s && find(TR,p)) cout << mpp[s] << " " << mpp[p] << "\n";
    // p = p.substr(1);
    // if(p!=s && find(TR,p)) cout << mpp[s] << " " << mpp[p] << "\n";
    }
    for(int i=0; i<26; i++) if(T->ptr[i]) s6(TR,T->ptr[i],s + char(i+'a'));
}

int main(){
    
    trie* T1 = NULL, *T2 = NULL;
    string s;
    int index = 0;
    while(cin>>s && s!="#"){
        mpp[s] = index++;
        create(T1,s);
        reverse(s.begin(),s.end());
        create(T2,s);
    }
    print(T1); cout<<endl;
    print(T2);
    // s6(T,T);
    
    return 0;
}