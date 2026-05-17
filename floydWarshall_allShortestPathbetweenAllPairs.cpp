// The Floyd-Warshall Algorithm finds the shortest paths between all pairs of vertices in a graph.
// Works on both directed and undirected graphs.
// Handles negative weights, but not negative cycles.
// Uses Dynamic Programming (DP) approach.

#include <iostream>
#include <vector>
using namespace std;

const int INF = 1e9; // A large value representing "infinity"

void floydWarshall(int V, vector<vector<int>> &graph) {
    vector<vector<int>> dist = graph; // Copy the adjacency matrix

    // Algorithm: Try using every node as an intermediate node
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                // Relaxation: Check if a shorter path exists through vertex k
                if (dist[i][k] != INF && dist[k][j] != INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }

    // Print the shortest path matrix
    cout << "Shortest distance matrix (All-Pairs Shortest Paths):\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int V = 4; // Number of vertices
    vector<vector<int>> graph = {
        {0, 3, INF, 7},
        {8, 0, 2, INF},
        {5, INF, 0, 1},
        {2, INF, INF, 0}
    };

    floydWarshall(V, graph);

    return 0;
}
