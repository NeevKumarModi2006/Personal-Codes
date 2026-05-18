#include<bits/stdc++.h>
using namespace std;

struct mnode {
	bool vis=true;
	vector<mnode*> mptr;
};

mnode* create(vector<bool> &v, int &i) {
	mnode* M = new mnode;
	while(v[i++]) M->mptr.push_back(create(v,i));
	return M;
}
int ans = 0;

bool visit(mnode* M, int curr,int &k) {
    // if(curr>k) return false;
	M->vis = false;
	curr++;
	if(curr==k) {
		ans++;                      // ans increment 
		return true;
	}
	for(auto i : M->mptr) if(visit(i, curr, k)) return true;
	M->vis = true;     // back tracking set 0 if visit  not true
	return false;
}
void count(mnode* M, int &k) {
	if(M->vis) 	visit(M,0,k);
	for(auto i : M->mptr) count(i, k);
}

int main() {
	int k = 3;  // number of disjoints
	k++;        // number of nodes
	vector<bool> v = {true,true,true,true,true,false,true,true,true,false,true,true,true,false,true,false,true,false,true, true, false,false,true,false,
	                  false,false,false,true,false,true,true,false,false,false,false,true,false,false,
	                  true,true,false,true,true,true,true,false,true,true, false, false,false,false,
	                  true,true,true,false,true,false,true,true,true,false,false,true,false,false,false,false,true,false,
	                  true,true,true,false, true,true,true,true,false,false,true,false,false,false,true,false,false,
	                  true,true,false,true,true,true,false,true,false,false,false,false,false,false, true,true,false,false,false,false,false
	                 };
	int i = 0;
	mnode* M = create(v, i);
	count(M,k);

	cout<<ans;  // globally declared variable

	return 0;
}
