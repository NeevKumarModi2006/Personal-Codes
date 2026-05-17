#include<bits/stdc++.h>
using namespace std;

set<vector<int>> ans;

void hamiltonian_helper(vector<vector<int>> &G, int &N, vector<bool> &vis, vector<int> &arr, int c) {
	vis[c] = true;
	arr.push_back(c);
	if(arr.size()==N) {
		ans.insert(arr);
		vis[c] = false;
		arr.pop_back();
		return;
	}

	for(int i=0; i<G[c].size(); i++)
		if(!vis[G[c][i]]) hamiltonian_helper(G,N,vis,arr,G[c][i]);
	
	arr.pop_back();
	vis[c]= false;

}

void hamiltonian(vector<vector<int>> &G, int &N) {
	vector<bool> vis(N, false);
	vector<int>arr;
	for(int i = 0; i<N; i++) 
		hamiltonian_helper(G,N,vis,arr, i);
	
	for(auto &i: ans) {
		for(int j : i) cout<<j<<" ";
		cout<<endl;
	}
}

int main() {

	int N = 4;
	vector<vector<int>> G(N);

	G[0] = {1};
	G[1] = {0,2,3};
	G[2] = {1,3};
	G[3] = {1,2};

	hamiltonian(G,N);

	return 0;
}