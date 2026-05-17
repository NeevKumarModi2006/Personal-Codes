#include<bits/stdc++.h>
using namespace std;

const int N = 9;
vector<double>task = {0,3.1,2.0,4.6,1.8,0.3,4,3.7,0};
vector<vector<double>> G (N,vector<double>(N,-1));

double longest = 0;

void s2(int s,int t,double curr) {
	if(s==t) {
		longest = max(longest,curr);
		return;
	}
	for(int i=0; i<N; i++) 
		if(G[s][i]>-1) 
			s2(i,t,curr+G[s][i]);
}


int main() {

	G[0][1] = 0;
	G[0][2] = 0;
	G[1][3] = 0;
	G[1][5] = 0;
	G[2][5] = 0;
	G[5][6] = 0;
	G[6][7] = 0;
	G[3][6] = 0;
	G[3][4] = 0;
	G[4][7] = 0;
	G[7][8] = 0;

	for(int i=0; i<N; i++) 
		for(int j=0; j<N; j++) 
			if(G[i][j]==0) 
			    G[i][j]=task[i];

	s2(0,8,0);
	cout<<longest;
	
	return 0;
}