#include <bits/stdc++.h>
using namespace std;

const int N = 6;
vector<vector<int>> G(N, vector<int>(N, INT_MAX));

inline void makeEdge(int i, int j, int w) {
	G[i][j] = w;
	G[j][i] = w;
}

void prims(int st) {
	vector<vector<int>> arr;   // v1 v2 weight
	vector<bool>vis(N,false);
	vis[st] = true;
	arr.push_back({st,st,0});
	while(arr.size()<N) {
		vector<int>A(3,INT_MAX);
		for(int j = 0; j < arr.size(); j++)     // visit visited
			for(int q=0; q<2; q++) {        // q=0 and q=1
				int v1 = arr[j][q];
				for(int k=0; k<N; k++)      // visit non visted
					if(!vis[k] && G[v1][k] != INT_MAX && A[2]>G[v1][k]) {
						A[0] = v1;
						A[1] = k;
						A[2] = G[v1][k];
					}
			}
		if(A[2] == INT_MAX) break;
		vis[A[1]] = true;
		arr.push_back(A);
	}


	int sum = 0;
	for(int i = 1; i<arr.size(); i++) {
		cout<< arr[i][0]+1 <<" " << arr[i][1]+1;
		sum+=arr[i][2];
		cout<<endl;
	}
	cout<<sum;

}

int main(){
    
makeEdge(0,1,13);
makeEdge(0,2,27);
makeEdge(0,3,39);
makeEdge(1,2,28);
makeEdge(2,3,34); //5    
makeEdge(1,4,7);
makeEdge(2,4,2);
makeEdge(2,5,14);
makeEdge(3,5,36);
makeEdge(4,5,7); //5

    
    return 0;
}