#include<bits/stdc++.h>
using namespace std;

struct tnode{
	int eow=0;
	tnode* ptr[26] = {NULL};
};

void create(tnode* &T,string &s, int i=0){
	if(i>s.size()) return;
	if(T==NULL)	T = new tnode;	
	if(i==s.size()){
		T->eow = 1;
		return;
	}
	 create(T->ptr[s[i]-'a'], s, i+1);
}

void print(tnode* T, string s=""){
	if(T==NULL) return;
	if(T->eow==1) cout << s <<endl;
	for(int i=0; i<26; i++) print(T->ptr[i],s+char(i+'a'));
}

void findAndPrint(tnode* T, string g, int i=0){
	if(T==NULL) return;
	if(i==g.size()){
		if(T->eow) cout<<g<<" ";
	for(int j=0; j<26; j++) if(T->ptr[j]) findAndPrint(T->ptr[j],g+char(j+'a'),i+1);		
	}
	else{
		findAndPrint(T->ptr[g[i]-'a'],g,i+1);
	}
}


int main(){


tnode* T = NULL;
string s;
while(cin>>s && s!="#") create(T,s);
while(cin>>s && s!="#"){
	findAndPrint(T,s);
	cout<<endl;
}
// vector<string> arr = {"integer", "nitwarangal", "intern", "coder", "nitsurathkal","interview",
//  "nittrichy", "nitsurat", "interest", "conqueror"};
// for(string &s: arr){
// 	create(T,s);
// }

// vector<string>findA = {"int", "nit", "nitw", "co"};

// for(string &s: findA){
// 	findAndPrint(T,s);
// 	cout<<endl;
// }



    return 0;
}