// type 1
#include <bits/stdc++.h>
using namespace std;

const int N = 4;
int G[N][N] = {0}; // Initialize all to 0

void addEdge(int u, int v) {
    G[u][v] = 1; 
    G[v][u] = 1; // Remove this for directed G
}

void printG(void) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << G[i][j] << " ";
        cout << endl;
    }
}

void BFS(int st) {
    queue<int> q;
    bool visited[N] = {false};

    visited[st] = true;
    q.push(st);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        // Explore neighbors
        for (int i = 0; i < N; i++) {
            if (G[node][i] == 1 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
}



void DFS_helper(int node, bool visited[]) {
    visited[node] = true;
    cout << node << " ";

    // Explore neighbors
    for (int i = 0; i < N; i++) {
        if (G[node][i] == 1 && !visited[i]) {
            DFS_helper(i, visited);
        }
    }
}

void DFS(int st) {
    bool visited[N] = {false};
    DFS_helper(st, visited);
}

void dijkstra(int s, vector<pair<int, int>> adj[], int V) {
    vector<int> dist(V, INT_MAX); 
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[s] = 0; 
    pq.push({0, s});

    while (!pq.empty()) {
        auto [d,node] = pq.top();
        pq.pop();

        if (d > dist[node]) continue;

        // Traverse all adjacent nodes
        for (auto edge : G[node]) {
            int nextNode = edge.first;
            int weight = edge.second;

            // Relaxation step
            if (dist[node] + weight < dist[nextNode]) {
                dist[nextNode] = dist[node] + weight;
                pq.push({dist[nextNode], nextNode});
            }
        }
    }

    // Print shortest distances
    cout << "Shortest distances from source " << s << ":\n";
    for (int i = 0; i < V; i++)
        cout << "Node " << i << " -> " << dist[i] << "\n";
}


int main() {
    addEdge(0, 1);
    addEdge(1, 2);
    addEdge(2, 3);
    printG();
    return 0;
}
