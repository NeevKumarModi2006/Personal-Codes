#include<bits/stdc++.h>
using namespace std;

struct mnode {
	char data;
	vector<mnode*>mptr;
	mnode *p,*ls,*rs;
};

mnode* create(char k) {
	mnode* M = new mnode{k};
	while(cin>>k && k!='.') M->mptr.push_back(create(k));
		int i=M->mptr.size();
	for(int j=0;j<i;j++)  M->mptr[j]->p=M;
	return M;
}
void dft(mnode* M){
    cout<<M->data;
    for(auto i : M->mptr) dft(i);
}

void level(mnode* M){
    std::queue<mnode*>Q ;
    Q.push(M);
    int cnt=0;
    mnode* prev = NULL;
    while(!Q.empty()){
        bool k = true;
        if(cnt==0){ k=false; cnt=Q.size();}
    mnode* T = Q.front(); Q.pop();  
    if(k){
        prev->rs=T;
        T->ls=prev;
    }
        for(auto i : T->mptr) Q.push(i);
        prev = T;
        cnt--;
    }
    
}

mnode* find(mnode* M,char k){
  if(M->data==k)  return M;
  for(auto i : M->mptr){
      mnode* L = find(i, k);
      if(L!=NULL) return L;
  }
  
  return NULL;
}

void print(mnode* M,mnode* K){
    if(K->p) cout<<K->p->data<<endl;
    if(K->p && K->p->p)  cout<<K->p->p->data<<endl;
    mnode* L = K->ls;
while(L) {cout<<L->data; L=L->ls;} cout<<endl; L=K->rs;
while(L) {cout<<L->data; L=L->rs;} cout<<endl;
    for(auto i : K->mptr) cout<<i->data; 
    cout<<endl;
}
int main() {

	char p,k;
	cin>>p;
	mnode* M = create(p);
	level(M);
	cin>>k; 
		cin>>k;  print(M,find(M,k));
		cin>>k;  print(M,find(M,k));
		cin>>k;  print(M,find(M,k));
	return 0;
}