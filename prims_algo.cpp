// Prim’s Algorithm is used to find the Minimum Spanning Tree (MST).
// Unlike Kruskal's Algorithm, Prim’s Algorithm grows the MST one vertex at a time.
// Uses a Priority Queue (Min Heap) to pick the smallest edge connecting the MST to a new node.

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge {
    int weight, node;
};

// Custom comparator for Min Heap
struct Compare {
    bool operator()(Edge a, Edge b) {
        return a.weight > b.weight; // Min Heap (Priority Queue)
    }
};

void prims(int V, vector<pair<int, int>> adj[]) {
    vector<bool> inMST(V, false); // Track included vertices
    priority_queue<Edge, vector<Edge>, Compare> pq;

    vector<int> parent(V, -1); // Store MST structure
    vector<int> key(V, 1e9); // Store minimum weight edge to a node

    pq.push({0, 0}); // Start from node 0
    key[0] = 0;

    while (!pq.empty()) {
        int node = pq.top().node;
        pq.pop();

        if (inMST[node]) continue; // Skip if already in MST
        inMST[node] = true;

        // Process all adjacent edges
        for (auto it : adj[node]) {
            int adjNode = it.first;
            int weight = it.second;

            if (!inMST[adjNode] && weight < key[adjNode]) {
                key[adjNode] = weight;
                parent[adjNode] = node;
                pq.push({weight, adjNode});
            }
        }
    }

    // Print the MST
    cout << "Minimum Spanning Tree (MST) edges:\n";
    int mstWeight = 0;
    for (int i = 1; i < V; i++) {
        cout << parent[i] << " -- " << i << " (Weight: " << key[i] << ")\n";
        mstWeight += key[i];
    }
    cout << "Total weight of MST: " << mstWeight << endl;
}

int main() {
    int V = 5; // Number of vertices
    vector<pair<int, int>> adj[V];

    // Graph edges (u, v, weight)
    adj[0].push_back({1, 2});
    adj[0].push_back({3, 3});
    adj[1].push_back({0, 2});
    adj[1].push_back({2, 1});
    adj[1].push_back({3, 4});
    adj[2].push_back({1, 1});
    adj[2].push_back({3, 5});
    adj[2].push_back({4, 6});
    adj[3].push_back({0, 3});
    adj[3].push_back({1, 4});
    adj[3].push_back({2, 5});
    adj[3].push_back({4, 7});
    adj[4].push_back({2, 6});
    adj[4].push_back({3, 7});

    prims(V, adj);

    return 0;
}
