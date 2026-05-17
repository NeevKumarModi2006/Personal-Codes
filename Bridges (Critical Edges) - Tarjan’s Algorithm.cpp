// Bridges and Articulation Points (also known as cut vertices) help in identifying critical connections in a graph.
// Bridges (Critical Edges)
// Removing a bridge increases the number of connected components.
// Used in network reliability analysis.

// Uses DFS traversal.
// Maintains Discovery Time and Lowest Reachable Vertex for each node.
#include <iostream>
#include <vector>
using namespace std;

void dfs(int node, int parent, vector<int> adj[], vector<bool> &visited, vector<int> &disc, vector<int> &low, int &timer) {
    visited[node] = true;
    disc[node] = low[node] = timer++;
    
    for (int neighbor : adj[node]) {
        if (neighbor == parent) continue;

        if (!visited[neighbor]) {
            dfs(neighbor, node, adj, visited, disc, low, timer);
            low[node] = min(low[node], low[neighbor]);

            if (low[neighbor] > disc[node]) {
                cout << "Bridge: " << node << " -- " << neighbor << endl;
            }
        } else {
            low[node] = min(low[node], disc[neighbor]);
        }
    }
}

void findBridges(int V, vector<int> adj[]) {
    vector<bool> visited(V, false);
    vector<int> disc(V, -1), low(V, -1);
    int timer = 0;

    for (int i = 0; i < V; i++) {
        if (!visited[i])
            dfs(i, -1, adj, visited, disc, low, timer);
    }
}

int main() {
    int V = 5;
    vector<int> adj[V];

    // Undirected graph edges
    adj[0].push_back(1);
    adj[1].push_back(0);
    adj[1].push_back(2);
    adj[2].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(2);
    adj[3].push_back(4);
    adj[4].push_back(3);

    findBridges(V, adj);

    return 0;
}
