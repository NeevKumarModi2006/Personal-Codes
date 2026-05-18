#include<bits/stdc++.h>
using namespace std;

struct mnode {
	int data;
	vector<mnode*> mptr;
};

mnode* create(int k, vector<int> &v, int &i) {
	mnode* M = new mnode{k};
	while(v[i++]!=0) M->mptr.push_back(create(v[i-1],v,i));
	return M;
}

void path(mnode* M, int x, int y,  bool k,string s,string &ans) {
    if(x==M->data || k) {   s+=to_string(M->data)+" ";   k=true; }
    if(y==M->data){ ans = s;   k=false;  }
	for(int i=0; i<M->mptr.size(); i++)  path(M->mptr[i],x,y,k,s,ans);
}
void pathReal(mnode* M, int x,int y){
    string a,b;
   path(M,M->data,y,false,"",a); 
   path(M,M->data,y,false,"",b);
   cout<<a<<endl<<b<<endl;
   
}


int main() {
	vector<int> v = {1, 2, 3, 4, 5, 6, 7, 0, 0, 8, 9, 0, 0, 0, 0, 10, 11, 12, 0, 0,
	14, 15, 16, 0, 0, 0, 17, 18, 0, 0, 0, 0, 0, 0};
	int i = 0;
	mnode* M = create(v[i++], v, i);
	
	int x,y;
    
    cin>>x>>y;  pathReal(M,x,y); 
    cin>>x>>y;  pathReal(M,x,y);
    
	return 0;
}
