// Topological Sorting is used in Directed Acyclic Graphs (DAGs) to order 
// the vertices such that for every directed edge u → v, vertex u comes before v in the ordering
// Works only on DAGs (Directed Acyclic Graphs).
// Two Methods:
// Kahn’s Algorithm (BFS-based, using In-degree)
// DFS-based (Using Stack)
// Used in:
// Task scheduling
// Dependency resolution
// Course prerequisites


#include <iostream>
#include <vector>
#include <queue>
using namespace std;

void topologicalSort(int V, vector<int> adj[]) {
    vector<int> inDegree(V, 0);
    queue<int> q;
    vector<int> topoOrder;

    // Compute in-degree of each vertex
    for (int i = 0; i < V; i++)
        for (int v : adj[i])
            inDegree[v]++;

    // Enqueue all nodes with in-degree 0
    for (int i = 0; i < V; i++)
        if (inDegree[i] == 0)
            q.push(i);

    // Process nodes
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topoOrder.push_back(node);

        // Reduce in-degree of neighbors
        for (int neighbor : adj[node]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0)
                q.push(neighbor);
        }
    }

    // Print Topological Order
    cout << "Topological Sort Order: ";
    for (int node : topoOrder)
        cout << node << " ";
    cout << endl;
}

int main() {
    int V = 6;
    vector<int> adj[V];

    // DAG edges
    adj[5].push_back(2);
    adj[5].push_back(0);
    adj[4].push_back(0);
    adj[4].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(1);

    topologicalSort(V, adj);

    return 0;
}
