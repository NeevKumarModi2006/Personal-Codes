// Bipartite Graph → Can be colored using two colors.

// Graph Coloring → Assigning colors such that no two adjacent nodes have the same color.

// Algorithms Used:

// BFS for Bipartite Check
// DFS for Graph Coloring
// Used in:

// Scheduling problems
// Sudoku solver
// Map coloring
// DFS-Based Graph Coloring
// Uses recursion to assign colors.
// Ensures adjacent nodes have different colors.

#include <iostream>
#include <vector>
using namespace std;

bool dfs(int node, int color[], vector<int> adj[], int currentColor) {
    color[node] = currentColor;

    for (int neighbor : adj[node]) {
        if (color[neighbor] == -1) { // If not colored, color it
            if (!dfs(neighbor, color, adj, 1 - currentColor))
                return false;
        } else if (color[neighbor] == color[node]) { // If same color, not bipartite
            return false;
        }
    }
    return true;
}

bool isBipartiteDFS(int V, vector<int> adj[]) {
    int color[V];
    fill(color, color + V, -1); // Initialize all nodes as uncolored

    for (int i = 0; i < V; i++) {
        if (color[i] == -1) {
            if (!dfs(i, color, adj, 0))
                return false;
        }
    }
    return true;
}

int main() {
    int V = 4;
    vector<int> adj[V];

    // Bipartite Graph Edges
    adj[0].push_back(1);
    adj[1].push_back(0);
    adj[1].push_back(2);
    adj[2].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(2);

    if (isBipartiteDFS(V, adj))
        cout << "Graph is Bipartite (DFS)\n";
    else
        cout << "Graph is NOT Bipartite (DFS)\n";

    return 0;
}
