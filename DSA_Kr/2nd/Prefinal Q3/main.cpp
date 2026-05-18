#include<bits/stdc++.h>
using namespace std;

const int N = 11;
vector<vector<int>>G(N,vector<int>(N,INT_MAX));
map<pair<int,int>,string>mpp;


inline void makeEdge(int i, int j, int w, string s){
	G[i][j] = w;
	mpp[{i,j}] = s;
}

struct str{
	int num=-1, p=-1, dist=INT_MAX;
};

static bool comp(str &a, str &b){
	return a.dist < b.dist;
}
	vector<str>arr(N);	
void backtrack(int curr,int s){
	if(curr==s) return;
	backtrack( arr[curr].p,s);
		cout << "From " << arr[curr].p << " move " << mpp[{arr[curr].p,curr}] << " by " <<G[arr[curr].p][curr] << " to reach " << curr <<endl ;
}


void djikstra(int s, int t){

vector<bool>vis(N,false);

for(int i=0;i<N;i++){
	arr[i].num = i;
}

arr[s].dist = 0; 
int curr = s;

while(true){

	vis[curr] = true;
	for(int i=0; i<N; i++){
		if( i!=curr && G[curr][i]!=INT_MAX && arr[i].dist > arr[curr].dist + G[curr][i]){
			arr[i].dist = arr[curr].dist + G[curr][i];
			arr[i].p = curr;
		}
	}
	
	int mini = INT_MAX;
	int x = curr;
	for(int i=0; i<N; i++){
		if(!vis[i] && arr[i].dist<mini){
			x=i;
			mini = arr[i].dist;
		}
	}

	if(mini==INT_MAX) break;
	curr = x;
}

backtrack(t,s);	
cout<<"Minimum cost is "<<arr[t].dist;
}

int main(){

makeEdge(0,1,4,"north-east");
makeEdge(1,4,1,"south");
makeEdge(4,0,2,"west");
makeEdge(4,8,8,"south");
makeEdge(0,8,4,"south-east");	//5
makeEdge(4,5,9,"east");
makeEdge(1,5,12,"south-east");
makeEdge(1,2,5,"east");
makeEdge(8,9,1,"east");//9
makeEdge(9,5,1,"north");
makeEdge(2,5,6,"south");
makeEdge(2,10,18,"north-east");
makeEdge(2,3,12,"east");
makeEdge(3,10,2,"north-west");
makeEdge(5,3,6,"north-east");
makeEdge(5,6,4,"east");
makeEdge(9,6,9,"north-east"); //17
makeEdge(6,7,1,"east");

int i=1,j=10;
cin>>i>>j;

djikstra(i,j);

    return 0;
}