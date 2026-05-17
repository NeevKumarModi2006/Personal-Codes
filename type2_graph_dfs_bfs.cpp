//type 2
#include <iostream>
#include <vector>
using namespace std;

class Graph {
public:
    vector<int> adj[100];

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // Remove for directed graph
    }

    void printGraph(int V) {
        for (int i = 0; i < V; i++) {
            cout << i << " -> ";
            for (int v : adj[i])
                cout << v << " ";
            cout << endl;
        }
    }
};

void BFS(int start) {
    vector<bool> visited(100, false);
    queue<int> q;
    
    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

void DFS_helper(int node, vector<bool> &visited) {
    visited[node] = true;
    cout << node << " ";

    for (int neighbor : adj[node]) {
        if (!visited[neighbor])
            DFS_helper(neighbor, visited);
    }
}

void DFS(int start) {
    vector<bool> visited(100, false);
    DFSUtil(start, visited);
}

int main() {
    Graph g;
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.printGraph(4);
    return 0;
}
