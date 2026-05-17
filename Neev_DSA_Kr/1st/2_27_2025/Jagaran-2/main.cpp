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

void DFT(mnode* M, vector<int> &arr, int prev,vector<int>& ans) {   // & in arr decreases space complexity
	if(M->data > prev) {
		arr.push_back(M->data);
		prev = M->data;
	}
	int k = arr.size();     // not necessary if no & in arr
	if( M->mptr.empty() && ans.size() < arr.size() ) ans = arr;
	for(int i=0; i<M->mptr.size(); i++) {
		DFT(M->mptr[i], arr, prev, ans);
	 arr.erase(arr.begin()+k,arr.end());    // same as above
	}
}

void traverse(mnode* M, vector<int> &arr,vector<int>& ans) {
    arr.clear();
	DFT(M,arr,0,ans);
	for(int i=0; i<M->mptr.size(); i++) traverse(M->mptr[i], arr, ans);
}

int main() {
	vector<int> v = { 3, 1, 9, 3, 2, 0, 3, 0, 0, 0, 0, 4, 2, 5, 0, 8, 8, 0, 4, 2, 0, 7, 0, 9, 0,
	                  0, 0, 9, 6, 0, 0, 0, 0, 1, 0, 5, 5, 7, 0, 9, 0, 3, 0, 0, 6, 0, 0, 0
	                };
	int i = 0;
	mnode* M = create(v[i++], v, i);

	vector<int>ans;
	vector<int>arr;
	traverse(M, arr,ans);

	for(auto i : ans) cout<<i<<" ";

	return 0;
}