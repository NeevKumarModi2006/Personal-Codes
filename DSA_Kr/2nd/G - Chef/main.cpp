#include <bits/stdc++.h>
using namespace std;

map<char,int> m = {{'A',0},{'B',1},{'C',2},{'D',3},{'E',4},{'F',5},{'H',6},{'I',7}};
vector<char> mm = {'A','B','C','D','E','F','H','I'};

const int N = 8;
vector<vector<bool>> G(N, vector<bool>(N, false));

inline void makeEdge(int i, int j) {
	G[i][j] = true;
}

void recur(vector<int> &T, vector<bool> &visited, vector<int> &inDegree, vector<vector<int>> &ans) {
	bool check = false;

	for (int i = 0; i < N; i++) {
		if (!visited[i] && inDegree[i] == 0) {
			visited[i] = true;
			T.push_back(i);

			vector<int> changed;
			for (int j = 0; j < N; j++) {
				if (G[i][j]) {
					inDegree[j]--;
					changed.push_back(j);
				}
			}

			recur(T, visited, inDegree, ans);

			for (int j : changed) inDegree[j]++;
			T.pop_back();
			visited[i] = false;

			check = true;
		}
	}

	if (!check && T.size() == N) ans.push_back(T);
    
}

void allTopologicalSort() {
	vector<bool> visited(N, false);
	vector<int> inDegree(N, 0);
	vector<int> T;
    vector<vector<int>> ans;
    
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			if (G[i][j]) inDegree[j]++;

	recur(T, visited, inDegree, ans);
	
	for(auto &T : ans) reverse(T.begin(),T.end());
	sort(ans.begin(),ans.end());
	for(auto &T : ans){
	    for(int i : T) cout << mm[i] << " ";
	    cout<<endl;
	}

}



int main() {
	vector<char> arr = {
		'A','B','B','C','C','D','D','E','I','C','H','I','F','H'
	};

	for (int i = 0; i < arr.size(); )
		makeEdge(m[arr[i++]], m[arr[i++]]);

	allTopologicalSort();

	return 0;
}
