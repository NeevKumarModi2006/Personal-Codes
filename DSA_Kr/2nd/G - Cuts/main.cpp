#include <bits/stdc++.h>
using namespace std;

struct alpha {
	int num;
	int low = INT_MAX;
	int parent;
	bool vis = false;
};

const int N = 9;
int G[N][N] = {0};

inline void makeEdge(int u, int v) {
	G[u][v] = 1;
	G[v][u] = 1;
}

int check(vector<alpha> &mat, int v) {
	int ans = INT_MAX;
	for (int i = 0; i < N; i++)
		if (G[v][i] && mat[v].parent != i) {
			ans = min(ans, mat[i].num);
			ans = min(ans, mat[i].low);
		}
	return ans;
}

void DFS(int v, vector<alpha> &mat, int &x) {
	mat[v].vis = true;
	mat[v].num = x++;

	for (int i = 0; i < N; i++)
		if (G[v][i] && !mat[i].vis) {
			mat[i].parent = v;
			DFS(i, mat, x);
		}

	mat[v].low = min(mat[v].num, check(mat, v));
}

void printV(vector<alpha> &matrix, int st) {
	for (int i = 0; i < N; i++) 
		if (st == i) {
			int child = 0;
			for (int j = 0; j < N; j++)
				if (matrix[j].parent == st) child++;
			if (child > 1) cout << st << " ";
		} 
		else 
			for (int j = 0; j < N; j++)
				if (G[i][j] && matrix[j].parent == i && matrix[j].low >= matrix[i].num) {
					cout << i << " ";
					break;
				}

}

void printE(vector<alpha> &matrix){
  	for (int i = N-1; i>=0; i--)        // REVERSED FOR GETTING OUTPUT ORDER
			for (int j = 0; j < N; j++)
				if (G[i][j] && matrix[j].low > matrix[i].num) 
					cout << i << " " << j << endl;
}

void articulation(int st) {
	int x = 1;
	vector<alpha> matrix(N);
	matrix[st].parent = -1;
	DFS(st, matrix, x);
	printV(matrix, st);     cout<<endl;
	printE(matrix);
}

int main() {
    
	makeEdge(0,1);
	makeEdge(0,2);
	makeEdge(1,2);
	makeEdge(2,3);
	makeEdge(3,4);
	makeEdge(2,5);
	makeEdge(6,5);
	makeEdge(6,7);
	makeEdge(5,8);
	makeEdge(8,7);
	
	articulation(0);

	return 0;
}
