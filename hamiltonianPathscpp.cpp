#include <bits/stdc++.h>
using namespace std;

const int N = 5; // Nodes a-e
vector<vector<int>> G(N, vector<int>(N, 0)); // 0 = no edge, 1 = edge

inline void makeEdge(int i, int j) {
    G[i][j] = 1;
    G[j][i] = 1; // Undirected graph
}

bool isSafe(int node, int pos, vector<int> &path, vector<vector<int>> &G) {
    // Must be adjacent to previous node in path
    if (G[path[pos - 1]][node] == 0)
        return false;

    // Must not be already included in path
    for (int i = 0; i < pos; i++)
        if (path[i] == node)
            return false;

    return true;
}

bool hamiltonianUtil(vector<int> &path, int pos) {
    if (pos == N) {
        // Check for cycle: last node connects to first
        if (G[path[pos - 1]][path[0]] == 1) {
            cout << "Hamiltonian Cycle: ";
            for (int i = 0; i < N; i++) cout << char('a' + path[i]) << " ";
            cout << char('a' + path[0]) << endl; // complete cycle
        } else {
            cout << "Hamiltonian Path: ";
            for (int i = 0; i < N; i++) cout << char('a' + path[i]) << " ";
            cout << endl;
        }
        return true;
    }

    for (int v = 1; v < N; v++) {
        if (isSafe(v, pos, path, G)) {
            path[pos] = v;
            if (hamiltonianUtil(path, pos + 1))
                return true; // return for first solution only
            path[pos] = -1;
        }
    }

    return false;
}

bool hamiltonianPath() {
    vector<int> path(N, -1);
    path[0] = 0; // Start from node 0 ('a')

    if (!hamiltonianUtil(path, 1)) {
        cout << "No Hamiltonian Path or Cycle found.\n";
        return false;
    }
    return true;
}

int main() {
    makeEdge('a' - 'a', 'b' - 'a');
    makeEdge('a' - 'a', 'c' - 'a');
    makeEdge('b' - 'a', 'c' - 'a');
    makeEdge('b' - 'a', 'd' - 'a');
    makeEdge('c' - 'a', 'd' - 'a');
    makeEdge('d' - 'a', 'e' - 'a');
    makeEdge('e' - 'a', 'a' - 'a'); // to form a cycle

    hamiltonianPath();

    return 0;
}
