#include <bits/stdc++.h>
using namespace std;

set<vector<int>>ans;

void recur( vector<vector<int>> &arr,int i, int j, int &m, int &n,int curr,int &sum, vector<int>a) {
	if(curr>sum) return;
	if(i==arr.size()) {
		if(sum==curr) {
			ans.insert(a);
		}
		return;
	}
	if(i>=0){	
	    curr+=arr[i][j];
		a.push_back(arr[i][j]);
	}
	for(int k=0; k<n; k++) {
		recur(arr,i+1,k,m,n,curr,sum,a);
	}
}


int main() {
	int m,n;
	cin>>m>>n;
	vector<vector<int>>arr(m,vector<int>(n));

	for(int i=0; i<m; i++) {
		for(int j=0; j<n; j++) {
			int k;
			cin>>k;
			arr[i][j]=k;
		}
	}

	int s;
	cin>>s;

	recur(arr,-1,0,m,n,0,s, vector<int>());

	for(auto& i : ans) {
		for(int j : i) cout<<j<<" ";
		cout<<endl;
	}

	return 0;
}