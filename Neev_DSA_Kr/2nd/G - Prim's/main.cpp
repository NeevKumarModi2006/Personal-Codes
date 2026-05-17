#include<bits/stdc++.h>
using namespace std;

const int N = 7;
vector<vector<int>>G(N,vector<int>(N,INT_MAX));

inline void makeEdge(int i, int j, int w) {
	G[i-1][j-1] = w;
	G[j-1][i-1] = w;
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

int main() {

	makeEdge(1,2,2);
	makeEdge(1,4,1);
	makeEdge(1,3,4);
	makeEdge(2,5,10);
	makeEdge(2,4,3);        //5
	makeEdge(5,7,6);
	makeEdge(5,4,7);
	makeEdge(7,4,4);
	makeEdge(7,6,1);
	makeEdge(4,6,8);    //10
	makeEdge(3,4,2);
	makeEdge(3,6,5);

	prims(0);

	return 0;
}
