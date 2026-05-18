#include <bits/stdc++.h>
using namespace std;

const int N = 12;
int G[N][N] = {0};

inline void makeEdge(int u, int v)
{
	G[u-1][v-1] = 1;
	G[v-1][u-1] = 1;
}

void DFS( vector<int> &arr, int c) {
	arr.push_back(c);
	for(int i = 0; i<N; i++) 
		if(G[c][i]){
		    G[c][i] = 0;G[i][c] = 0;
		    DFS( arr, i);
		    break;
		}
}

pair<int,int> check(vector<int> &arr){
    for(int i=0;i<arr.size();i++)
        for(int j=0;j<N;j++) if(G[arr[i]][j]) return {i,arr[i]};
    
    return {-1,-1};
}


void eulerPath(int st) {
	st--;
	vector<int>arr;
			DFS(arr,st);
	while(true) {
	    auto [ind,newSt] = check(arr);
	    if(newSt==-1) break;
	    vector<int>v;
	    DFS(v,newSt);
	    arr.insert(arr.begin()+ind+1,v.begin()+1,v.end());
	}
	for(int i : arr) cout<<i+1<<" ";
}


int main()
{

	makeEdge(1,3);
	makeEdge(1,4);
	makeEdge(3,4);
	makeEdge(9,10);
	makeEdge(9,12);
	makeEdge(10,12);//6
	makeEdge(7,4);
	makeEdge(7,3);
	makeEdge(7,9);
	makeEdge(7,10);
	makeEdge(3,9);
	makeEdge(4,10);//12
	makeEdge(6,3);
	makeEdge(6,9);
	makeEdge(2,3);
	makeEdge(2,8);
	makeEdge(8,9);
	makeEdge(4,5);//18
	makeEdge(4,11);
	makeEdge(10,5);
	makeEdge(10,11);

	eulerPath(1);


	return 0;
}