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
// If child i of v cannot reach any ancestor of v without going through v, then v is a critical point. 
// Removing v would disconnect i’s subtree from the rest of the graph.			
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
	for(int i : ans) cout << i <<" ";
}

int main() {
	int N, e;
	cin >> N >> e;

	vector<vector<bool>> G(N, vector<bool>(N, false));

	for (int i = 0; i < e; i++) {
		int x, y;
		cin >> x >> y;
		G[x][y] = 1;
		G[y][x] = 1;
	}

	articulationPoints(G, N);
	return 0;
}
    