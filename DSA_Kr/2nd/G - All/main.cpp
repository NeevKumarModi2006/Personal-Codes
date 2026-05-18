#include <bits/stdc++.h>
using namespace std;

const int N = 7;
vector<vector<bool>> G(N, vector<bool>(N, false));

inline void makeEdge(int i, int j) {
	G[i][j] = true;
}

void dft(int &x, int c, vector<bool> &visited, vector<int> &a) { // less space complexity
	visited[c] = true;
	if(x==c) {
		for(int& i : a) cout<<i<<" ";
		cout<<endl;
		visited[c] = false;
		    return;
	}
	for(int i=0; i<N; i++) {
		a.push_back(i);
		if(G[c][i]) dft(x,i,visited,a);
		a.pop_back();
	}
	visited[c] = false;
}

void cycle(int x) {
	vector<bool> visited(N,false) ;
	vector<int>a = {x};
	for(int i=0; i<N; i++)
		if(G[x][i]) {
			a.push_back(i);
			dft(x,i,visited,a);
			a.pop_back();
		}
}

int main() {

	int x,y;

	while(cin>>x>>y && x!=-1) makeEdge(x,y);

	cycle(0);

	return 0;
}
