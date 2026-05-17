#include <bits/stdc++.h>
using namespace std;

const int N = 6;    // 0 to 5
vector<vector<int>> G1(N, vector<int>(N, 0));
vector<vector<int>> G2(N);

inline void makeEdge(int i, int j, int w) {
	G2[i].push_back(j);
	G2[j].push_back(i);
	G1[i][j] = w;
}

int BFT(int s, int t, vector<int>& parent) {
	for(int& i : parent) i = -1;
	queue<pair<int, int>> Q;
	Q.push({s, 9999});
	parent[s] = -2;
	while (!Q.empty()) {
		int curr = Q.front().first;
		int f = Q.front().second;
		Q.pop();
		for (int nxt : G2[curr]) {
			if (parent[nxt] == -1 && G1[curr][nxt] > 0) {
				parent[nxt] = curr;
				int x = min(f, G1[curr][nxt]);
				if (nxt==t)  return x;
				Q.push({nxt, x});
			}
		}
	}
	return 0;
}

int maxflow(int s, int t) {
	int ans = 0;
	vector<int> parent(N);
	int x = 0;
	while (true) {
		x = BFT(s, t, parent);      // BFT
		if(x<1) break;
		ans += x;
		int curr = t;
		while (curr!=s) {
			int prev = parent[curr];
			G1[curr][prev] += x;
			G1[prev][curr] -= x;
			curr = prev;
		}
	}
	return ans;
}

int main() {

	makeEdge(0,1,10);
	makeEdge(3,5,10);
	makeEdge(0,2,10);
	makeEdge(4,3,6);    // 4
	makeEdge(1,2,2);
	makeEdge(4,5,10);
	makeEdge(2,4,9);
	makeEdge(1,3,4);    // 8
	makeEdge(1,4,8);

	cout << maxflow(0, 5) << endl;

	return 0;
}