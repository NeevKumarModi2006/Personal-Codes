#include<bits/stdc++.h>
using namespace std;

const int N = 5;
vector<vector<bool>>G(N,vector<bool>(N,false));

inline void makeEdge(int i, int j) {
	G[i-1][j-1] = true;
}
vector<int> topologicalSort() {
	vector<bool> visited(N);;
	vector<int>T, inDegree(N);
	queue<int>Q ;

	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			if(G[i][j]) inDegree[j]++;

	for(int i=0; i<N; i++)
		if(inDegree[i]==0) {
			Q.push(i);
			visited[i]=true;
		}

	while(!Q.empty()) {
		int v = Q.front();
		Q.pop();
		T.push_back(v);
		for(int i=0; i<N; i++)
			if(G[v][i] && !visited[i]) {
				inDegree[i]--;
				if(inDegree[i]==0) {
					Q.push(i);
					visited[i] = true;
				}
			}
	}

	return T;
}


int main() {

	makeEdge(1,2);
	makeEdge(2,3);
	makeEdge(1,3);
	makeEdge(2,4);
	makeEdge(3,4);
	makeEdge(3,5);

	vector<int> T = topologicalSort();

	for(int i : T) cout<<i<<" ";

	return 0;
}

