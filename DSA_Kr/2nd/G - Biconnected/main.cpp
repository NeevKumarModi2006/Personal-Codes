#include <bits/stdc++.h>
using namespace std;

struct alpha {
	int num;
	int low = INT_MAX;
	int parent;
	bool vis = false;
};

set<int> ans;

void articulationDFT(vector<vector<bool>> &G, int &N, int v, vector<alpha> &mat, int &t) {
	mat[v].vis = true;
	mat[v].num = mat[v].low = ++t;
	int child = 0;

	for (int i = 0; i < N; i++)
		if (G[v][i]) {
			if (!mat[i].vis) {
				child++;
				mat[i].parent = v;
				articulationDFT(G, N, i, mat, t);
				mat[v].low = min(mat[v].low, mat[i].low);
				if(mat[v].parent == -1 && child > 1) ans.insert(v);
				if(mat[v].parent != -1 && mat[i].low >= mat[v].num) ans.insert(v);
			}
			else if (i != mat[v].parent) mat[v].low = min(mat[v].low, mat[i].num);
		}
}

void articulationPoints(vector<vector<bool>> &G, int &N) {
	int st = 0;
	int t = 0;
	vector<alpha> matrix(N);
	matrix[st].parent = -1;
	articulationDFT(G, N, st, matrix, t);
}

vector<vector<int>>answer;

void DFT(vector<vector<bool>> &G, int &N, vector<bool> &visited, int v,int &st) {
	if(v!=st) answer[answer.size()-1].push_back(v);
	visited[v] = true;
	bool k = false;
	for(int i = N-1 ; i >=0 ; i--) {
		if (G[v][i] && !visited[i]) {
			if(ans.count(v))  answer.push_back({v});
			DFT(G,N,visited,i,st);
		}
	}
}

void biconnected(vector<vector<bool>> &G, int &N) {
	articulationPoints(G,N);
	vector<bool>visited(N,false);
	for(int i : ans) G[i][i] = 1;
	int st = *ans.rbegin();
	DFT(G,N,visited,st,st);
    for(auto &i : answer){
        sort(i.begin(),i.end());
        cout<<"{ ";
        for(int j : i) cout << j << " ";
        cout<<"}\n";
    }
}

int main() {

	int N=10;

	vector<int>arr = {0,1,1,2,2,4,3,4,1,3,3,5,5,7,5,6,7,6,7,8,7,9};

	vector<vector<bool>> G(N, vector<bool>(N, false));
	int i=0;
	for (int i = 0; i < arr.size();) {
		int x=arr[i++], y=arr[i++];
		G[x][y] = 1;
		G[y][x] = 1;
	}

	biconnected(G,N);

	return 0;
}
