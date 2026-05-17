// Bipartite Graph → Can be colored using two colors.

// Graph Coloring → Assigning colors such that no two adjacent nodes have the same color.

// Algorithms Used:

// BFS for Bipartite Check
// DFS for Graph Coloring
// Used in:

// Scheduling problems
// Sudoku solver
// Map coloring
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool isBipartite(int V, vector<int> adj[]) {
    vector<int> color(V, -1); // -1 means uncolored

    for (int start = 0; start < V; start++) {
        if (color[start] == -1) {
            queue<int> q;
            q.push(start);
            color[start] = 0; // Start coloring with 0

            while (!q.empty()) {
                int node = q.front();
                q.pop();

                for (int neighbor : adj[node]) {
                    if (color[neighbor] == -1) { // If uncolored, color with opposite
                        color[neighbor] = 1 - color[node];
                        q.push(neighbor);
                    } else if (color[neighbor] == color[node]) { // If same color, not bipartite
                        return false;
                    }
                }
            }
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

    if (isBipartite(V, adj))
        cout << "Graph is Bipartite\n";
    else
        cout << "Graph is NOT Bipartite\n";

    return 0;
}
