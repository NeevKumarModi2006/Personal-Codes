#include <bits/stdc++.h>
using namespace std;

void postGraph(int G[10][10],bool visited[10],vector<pair<int,int>>& nums,int st,int &x) {
	visited[st] = true;
	for(int j=0; j<10; j++) {
		if(G[st][j] && !visited[j]) {
			postGraph(G,visited,nums,j,x);
		}
	}
	nums[st]= {x,st+1};
	x++;
}

void postGraph2(int G[10][10],bool visited[10],vector<pair<int,int>>& nums,int st,int &x) {
	visited[st] = true;
		cout<<st+1<<" ";
	for(int j=0; j<10; j++) {
		if(G[st][j] && !visited[j]) {
			postGraph2(G,visited,nums,j,x);
		}
	}
}

static bool comp(pair<int,int> a, pair<int,int> b){
    return a.first>b.first;
}

void backtrack(int G[10][10],const int &N,int i,int j){
           if(i==N) return;
    if(j==N){
        backtrack(G,N,i+1,0);
        return;
    }
    bool k = G[i][j] ? true : false;
    backtrack(G,N,i,j+1);
    			if(k){
			    G[i][j] = 0;
                G[j][i] = 1;
			}
}

int main() {
	const int N = 10;
	int G[10][10]= {
		{0,1,0,1,0,0,0,0,0,0},
		{0,0,1,0,0,1,0,0,0,0},
		{1,0,0,1,1,0,0,0,0,0},
		{0,0,0,0,1,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,1,0,0,0,0,0,0,0},
		{0,0,0,0,0,1,0,1,0,0},
		{0,0,0,0,0,1,0,0,0,1},
		{0,0,0,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,0,1,0}
	};

	bool visited[10]= {false};
	std::vector<pair<int,int>>  nums(10);
	int x=1;

	postGraph(G,visited,nums,1,x);
	for(int i=0; i<N; i++) {
		if(!visited[i])  postGraph(G,visited,nums,i,x);
	}

backtrack(G,N,0,0);

	bool vis[10] = {false};
	std::vector<pair<int,int>>  nums2(10);
	x=1;
	
	sort(nums.begin(),nums.end(),comp);

	for(int i=0; i<N; i++) {
		if(!vis[nums[i].second-1]) {
			postGraph2(G,vis,nums2,nums[i].second-1,x);
			cout<< " /" <<endl;
		}
	}




	return 0;
}
