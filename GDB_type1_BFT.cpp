#include<bits/stdc++.h>
using namespace std;

const int N = 9;
int G[N][N] = {0};

inline void makeEdge(int i, int j) {
	G[i][j] = 1;
}

void BFT(int st) {
	queue<int> q;
	bool visit[N] = {false};

	visit[st] = true;
	q.push(st);
	int i = 0;

	while (!q.empty() || i<N) {
		int v = q.front();
		q.pop();
		cout << v << " ";
		for (int j = 0; j < N; j++) {
			if (G[v][j] && !visit[j]) {
				visit[j] = true;
				q.push(j);
			}
		}
		if(q.empty()){
			for(; i<N; i++){
				if(!visit[i]){ 
				    q.push(i);
				    visit[i]=true; 
				    break;
				}
			}
	}
}
}

void printG(void) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << G[i][j] << " ";
        cout << endl;
    }
}

int main() {
    
	makeEdge(0,1);
	makeEdge(0,3);
	makeEdge(0,4);  //3
	makeEdge(1,4);
	makeEdge(1,2);
	makeEdge(3,4);  //6
	makeEdge(3,6);
	makeEdge(6,4);
	makeEdge(6,7);  //9
	makeEdge(4,5);
	makeEdge(4,7);
	makeEdge(7,5);  //12
	makeEdge(7,8);
	makeEdge(2,5);
	BFT(0);

	return 0;
}

