#include <bits/stdc++.h>
using namespace std;

int timer = 0;

inline void makeEdge(vector<vector<int>>& G, int u, int v) {
    G[u].push_back(v);
}

void DFT(int v, vector<vector<int>>& G, vector<int>& at, vector<int>& dt, vector<bool>& visited, vector<vector<char>>& edgeType) {
    visited[v] = true;
    at[v] = timer++;

    for (int u : G[v]) {
        if (!visited[u]) {
            edgeType[v][u] = 'T';
            DFT(u, G, at, dt, visited, edgeType);
        }
    }

    dt[v] = timer++;
}

void classifyEdges(vector<vector<int>>& G, vector<int>& at, vector<int>& dt, vector<vector<char>>& edgeType) {
    int n = G.size();
    for (int i = 0; i < n; i++) {
        for (int u : G[i]) {
            if (edgeType[i][u] == '#') {
                if (at[u] < at[i] && dt[i] < dt[u]) edgeType[i][u] = 'B';
                else if (at[i] < at[u] && dt[u] < dt[i]) edgeType[i][u] = 'F';
                else edgeType[i][u] = 'C';
            }
        }
    }
}

void printTimes(vector<int>& at, vector<int>& dt) {
    for (int i = 0; i < at.size(); i++) {
        if (at[i] != 0 || dt[i] != 0) 
            cout << i << " " << at[i] << " " << dt[i] << endl;
    }
}

void printEdges(vector<vector<int>>& G, vector<vector<char>>& edgeType) {
    for (int i = 0; i < G.size(); i++) {
        for (int u : G[i]) {
            if (edgeType[i][u] != '#')
                cout << i << " " << u << " " << edgeType[i][u] << endl;
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> G(n);
    vector<int> at(n, 0), dt(n, 0);
    vector<bool> visited(n, false);
    vector<vector<char>> edgeType(n, vector<char>(n, '#'));

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        makeEdge(G, u, v);
    }

    for (int i = 0; i < n; i++) 
        if (!visited[i]) DFT(i, G, at, dt, visited, edgeType);

    classifyEdges(G, at, dt, edgeType);
    printTimes(at, dt);
    printEdges(G, edgeType);

    return 0;
}
