#include<bits/stdc++.h>
using namespace std;

const int N = 6;    // 5+1
int G[N][N] = {0};

void makeEdge(int i, int j) {
	G[i][j] = 1;
}

void printG(void) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << G[i][j] << " ";
        cout << endl;
    }
}

void DFT_helper(vector<vector<bool>> &G, int &N, vector<bool> &visited, int v) {
    visited[v] = true;
    cout << v << " ";
    for (int i = 0 ; i < N; i++) {
        if (G[v][i] && !visited[i]) 
            DFT_helper(G,N,visited, i);
    }
}

void DFT(int st) {
   vector<bool>visited(N,false);
    DFT_helper(st, visited);

    for(bool i : visited) if(!i) DFT_helper(i, visited);
}

int main() {
    
	makeEdge(0,1);
	makeEdge(0,2);
	makeEdge(1,2);         //3
	makeEdge(1,3); 
	makeEdge(2,3);
	makeEdge(4,0);         //6
	makeEdge(4,1);
	makeEdge(3,4);
	makeEdge(4,5);         //9
    DFT(0);

	return 0;
}
