// Unlike Dijkstra’s Algorithm, it handles negative weights.
// Detects negative weight cycles.
// Uses Relaxation: Repeatedly updates the shortest path estimate.
#include <iostream>
#include <vector>
using namespace std;

struct Edge {
    int u, v, weight;
};

void bellmanFord(int V, int E, vector<Edge> &edges, int src) {
    vector<int> dist(V, 1e9); // Initialize distances to "infinity"
    dist[src] = 0; // Distance to source is 0

    // Relax all edges (V-1) times
    for (int i = 0; i < V - 1; i++) {
        for (auto edge : edges) {
            if (dist[edge.u] != 1e9 && dist[edge.u] + edge.weight < dist[edge.v]) {
                dist[edge.v] = dist[edge.u] + edge.weight;
            }
        }
    }

    // Check for negative weight cycles
    for (auto edge : edges) {
        if (dist[edge.u] != 1e9 && dist[edge.u] + edge.weight < dist[edge.v]) {
            cout << "Graph contains a negative weight cycle!\n";
            return;
        }
    }

    // Print the shortest distances
    cout << "Shortest distances from source " << src << ":\n";
    for (int i = 0; i < V; i++)
        cout << "Node " << i << " -> " << dist[i] << "\n";
}

int main() {
    int V = 5, E = 8; // Number of vertices and edges
    vector<Edge> edges = {
        {0, 1, -1}, {0, 2, 4}, {1, 2, 3}, {1, 3, 2},
        {1, 4, 2}, {3, 2, 5}, {3, 1, 1}, {4, 3, -3}
    };

    bellmanFord(V, E, edges, 0); // Start from node 0

    return 0;
}
