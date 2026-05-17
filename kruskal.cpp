// Kruskal’s Algorithm finds the Minimum Spanning Tree (MST).
// Uses Disjoint Set Union (DSU)
// Greedy Algorithm:
// Sort edges by weight.
// Pick the smallest edge that doesn’t create a cycle.
// Use DSU to check cycles.
// Stop when MST has (V-1) edges.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, weight;
};

// Comparator function for sorting edges
bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

// Disjoint Set functions
int findParent(int node, vector<int> &parent) {
    if (parent[node] != node)
        parent[node] = findParent(parent[node], parent); // Path compression
    return parent[node];
}

void unionSet(int u, int v, vector<int> &parent, vector<int> &rank) {
    int rootU = findParent(u, parent);
    int rootV = findParent(v, parent);

    if (rootU != rootV) {
        if (rank[rootU] > rank[rootV])
            parent[rootV] = rootU;
        else if (rank[rootU] < rank[rootV])
            parent[rootU] = rootV;
        else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

// Kruskal’s Algorithm
void kruskal(int V, vector<Edge> &edges) {
    sort(edges.begin(), edges.end(), compare); // Step 1: Sort edges by weight

    vector<int> parent(V);
    vector<int> rank(V, 0);

    for (int i = 0; i < V; i++)
        parent[i] = i; // Initialize DSU parent array

    vector<Edge> mst;
    int mstWeight = 0;

    for (Edge edge : edges) {
        // Step 2: Check if edge creates a cycle
        if (findParent(edge.u, parent) != findParent(edge.v, parent)) {
            unionSet(edge.u, edge.v, parent, rank);
            mst.push_back(edge);
            mstWeight += edge.weight;
        }
    }

    // Print the MST
    cout << "Minimum Spanning Tree (MST) edges:\n";
    for (Edge edge : mst)
        cout << edge.u << " -- " << edge.v << " (Weight: " << edge.weight << ")\n";
    cout << "Total weight of MST: " << mstWeight << endl;
}

int main() {
    int V = 5; // Number of vertices
    vector<Edge> edges;

    // Graph edges {u, v, weight}
    edges.push_back({0, 1, 2});
    edges.push_back({0, 3, 3});
    edges.push_back({1, 2, 1});
    edges.push_back({1, 3, 4});
    edges.push_back({2, 3, 5});
    edges.push_back({2, 4, 6});
    edges.push_back({3, 4, 7});

    kruskal(V, edges);

    return 0;
}
