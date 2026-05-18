#include <bits/stdc++.h>
using namespace std;

const int N = 6;
vector<vector<int>> G(N, vector<int>(N, INT_MAX));

inline void makeEdge(int i, int j, int w) {
	G[i][j] = w;
	G[j][i] = w;
}


int secondBest(vector<vector<int>> &arr,int &sum1){
  vector<int>b(3);
    int diff = INT_MAX;
    int index = -1;
    for(int k=0; k<arr.size(); k++){
        int cnt0 = 0, cnt1 = 0;
        for(int x=0; x<arr.size();x++){
            if(arr[x][0] == arr[k][0] || arr[x][1] == arr[k][0]) cnt0++;
            if(arr[x][0] == arr[k][1] || arr[x][1] == arr[k][1]) cnt1++;
        }
    int w = arr[k][2];
        if(cnt0==1){   
                    int i = arr[k][0];
          for(int j=0; j<N; j++){
              if(G[i][j]!=INT_MAX && j!=arr[k][1] && abs(w-G[i][j]) < diff){
                    diff = abs(w-G[i][j]);
                    index = k;
                    b[0] = i; b[1] = j; b[2] = G[i][j];       
              }
          }  
        }
        if(cnt1==1){
                                int i = arr[k][1];
          for(int j=0; j<N; j++){
              if(G[i][j]!=INT_MAX && j!=arr[k][0] && abs(w-G[i][j]) < diff){
                    diff = abs(w-G[i][j]);
                    index = k;
                    b[0] = i; b[1] = j; b[2] = G[i][j];       
              }
          }  
        }
    }
 return sum1 - arr[index][2] + b[2] ;   
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
    arr.erase(arr.begin());
	int sum = 0;
	for(auto &a : arr){
	      if(a[0]>a[1]) swap(a[0],a[1]);
	      sum+=a[2];
	} 
	cout << sum << endl << secondBest(arr,sum);
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

	prims(0);
    
    return 0;
}
