#include<bits/stdc++.h>
using namespace std;

const int N = 5;    // 4+1
vector<vector<int>>G(N,vector<int>(N,INT_MAX));

inline void makeEdge(int i, int j, int w) {
	G[i][j] = w;
	G[j][i] = w;
}

struct myStr {
	int d;
	bool vis;
	int prev;
};

void prims(int st) {
	vector<vector<int>> arr;   // v1 v2 weight
	vector<bool>vis(N,false);
	vis[st] = true;
	arr.push_back({st,st,0});
	while(arr.size()<N) {
		vector<int>A(3,INT_MAX);
		for(int j = 0; j < arr.size(); j++)
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
	for(auto i : arr) {
		 cout<< char(i[0] + 'a') <<" " << char(i[1] + 'a') << " " << i[2];
		cout<<endl;
	}
}

vector<vector<int>> getEdges(){
    vector<vector<int>>arr;
    for(int i = 0; i<N; i++) 
        for(int j=i;j<N;j++) 
            if(G[i][j]!=INT_MAX)
                    arr.push_back({G[i][j],i,j});
return arr;
}

void kruskal(){     // works only for undirected
   vector<vector<int>> arr = getEdges();
   sort(arr.begin(),arr.end());    // sorted according to edge weights
   vector<bool>visited(N,false);
   
   for(int i=0; i<arr.size();i++){
       if(!visited[arr[i][1]] || !visited[arr[i][2]]){
       visited[arr[i][1]] = true;
       visited[arr[i][2]] = true;
       }
       else arr.erase(arr.begin()+i--);
   }
   
   	for(auto i : arr) {
		 cout<< char(i[1] + 'a') <<" " << char(i[2] + 'a') << " " << i[0];
		cout<<endl;
	}
}

int dijkstra(int st, int end) {

	vector<myStr> arr(N, myStr{INT_MAX,false,st});
	arr[st].d = 0;
	int min = st;
	
	while(true) {
		int x = min;
		arr[x].vis = true;

		for(int i=0; i<N; i++) {
			if(G[x][i]!=INT_MAX && arr[i].d > arr[x].d + G[x][i]) {
				arr[i].d = arr[x].d +  G[x][i];
				arr[i].prev = x;
			}
		}

		min = -1;
		int k  = INT_MAX;       // k is min distance
		for (int i = 0; i < N; i++) {
			if (!arr[i].vis && arr[i].d < k) {
				k = arr[i].d;
				min = i;
			}
		}
		if (min == -1) break;
	}
	return arr[end].d;
}

int main() {

	makeEdge( 'a' - 'a', 'd' - 'a', 5 );
	makeEdge( 'a' - 'a', 'c' - 'a', 8 );
	makeEdge( 'd' - 'a', 'e' - 'a', 4 );
	makeEdge( 'a' - 'a', 'b' - 'a', 2 );
	makeEdge( 'b' - 'a', 'c' - 'a', 1 );
	makeEdge( 'c' - 'a', 'e' - 'a', 3 );

	cout << dijkstra( 'a' - 'a', 'e' - 'a') << endl;
	prims(0);  cout<<endl<<endl;
	kruskal();

	return 0;
}