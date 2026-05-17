#include <bits/stdc++.h>
using namespace std;

const int N = 5;
vector<vector<bool>> G(N, vector<bool>(N, false));

inline void makeEdge(int i, int j) {
    G[i][j] = true;
}

void recur(vector<int> &T, vector<bool> &visited, vector<int> &inDegree) {
    bool check = false; //

    for (int i = 0; i < N; i++) {
        if (!visited[i] && inDegree[i] == 0) {  // not visited and inDegree 0 
            visited[i] = true;
            T.push_back(i);

            vector<int> arr;
            for (int j = 0; j<N; j++) {
                if (G[i][j]) {
                    inDegree[j]--;
                    arr.push_back(j);
                }
            }

            recur(T, visited, inDegree);

            for (int j : arr) inDegree[j]++;    // back tracking + recursion due to for loop
            visited[i] = false;
            T.pop_back();

            check = true;
        }
    }

    if (!check) {
        for (int i : T) cout << i << " ";
        cout << endl;
    }
}

void allTopologicalSort() {
    vector<bool> visited(N, false);
    vector<int> T, inDegree(N, 0);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (G[i][j]) inDegree[j]++;

    recur(T, visited, inDegree);
}

int main() {
    
int x,y;

while(cin>>x>>y) makeEdge(x,y); 

    allTopologicalSort();

    return 0;
}
