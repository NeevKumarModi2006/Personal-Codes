// A Strongly Connected Component (SCC) is a maximal subgraph where every node is reachable from every other node.
// Works on Directed Graphs.
// Uses DFS Twice:
// First DFS (on the original graph) → Store finish order in a stack.
// Reverse the graph (transpose the edges).
// Second DFS (on transposed graph) → Find SCCs.

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void dfs(int node, vector<int> adj[], vector<bool> &visited, stack<int> &st) {
    visited[node] = true;

    for (int neighbor : adj[node]) {
        if (!visited[neighbor])
            dfs(neighbor, adj, visited, st);
    }
    
    st.push(node); // Store finish order
}

void reverseGraph(int V, vector<int> adj[], vector<int> transposed[]) {
    for (int i = 0; i < V; i++) {
        for (int neighbor : adj[i]) {
            transposed[neighbor].push_back(i);
        }
    }
}

void dfsTranspose(int node, vector<int> transposed[], vector<bool> &visited) {
    visited[node] = true;
    cout << node << " ";

    for (int neighbor : transposed[node]) {
        if (!visited[neighbor])
            dfsTranspose(neighbor, transposed, visited);
    }
}

void findSCCs(int V, vector<int> adj[]) {
    stack<int> st;
    vector<bool> visited(V, false);

    // Step 1: First DFS to store finish order
    for (int i = 0; i < V; i++) {
        if (!visited[i])
            dfs(i, adj, visited, st);
    }

    // Step 2: Reverse the graph
    vector<int> transposed[V];
    reverseGraph(V, adj, transposed);

    // Step 3: DFS on transposed graph in finish order
    fill(visited.begin(), visited.end(), false);

    cout << "Strongly Connected Components (SCCs):\n";
    while (!st.empty()) {
        int node = st.top();
        st.pop();
        
        if (!visited[node]) {
            dfsTranspose(node, transposed, visited);
            cout << endl;
        }
    }
}

int main() {
    int V = 5;
    vector<int> adj[V];

    // Directed graph edges
    adj[0].push_back(2);
    adj[2].push_back(1);
    adj[1].push_back(0);
    adj[1].push_back(3);
    adj[3].push_back(4);

    findSCCs(V, adj);

    return 0;
}
