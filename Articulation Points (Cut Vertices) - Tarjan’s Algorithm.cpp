// Bridges and Articulation Points (also known as cut vertices) help in identifying critical connections in a graph.

// Articulation Points (Cut Vertices)
// Removing an articulation point increases the number of connected components.
// Used in road networks, communication networks, and cluster identification.

// Uses DFS traversal.
// Maintains Discovery Time and Lowest Reachable Vertex for each node.
#include <iostream>
#include <vector>
using namespace std;

void dfs(int node, int parent, vector<int> adj[], vector<bool> &visited, vector<int> &disc, vector<int> &low, vector<bool> &isAP, int &timer) {
    visited[node] = true;
    disc[node] = low[node] = timer++;
    int children = 0;

    for (int neighbor : adj[node]) {
        if (neighbor == parent) continue;

        if (!visited[neighbor]) {
            dfs(neighbor, node, adj, visited, disc, low, isAP, timer);
            low[node] = min(low[node], low[neighbor]);

            if (low[neighbor] >= disc[node] && parent != -1)
                isAP[node] = true;

            children++;
        } else {
            low[node] = min(low[node], disc[neighbor]);
        }
    }

    if (parent == -1 && children > 1)
        isAP[node] = true;
}

void findArticulationPoints(int V, vector<int> adj[]) {
    vector<bool> visited(V, false);
    vector<int> disc(V, -1), low(V, -1);
    vector<bool> isAP(V, false);
    int timer = 0;

    for (int i = 0; i < V; i++) {
        if (!visited[i])
            dfs(i, -1, adj, visited, disc, low, isAP, timer);
    }

    cout << "Articulation Points: ";
    for (int i = 0; i < V; i++) {
        if (isAP[i]) cout << i << " ";
    }
    cout << endl;
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

    findArticulationPoints(V, adj);

    return 0;
}
