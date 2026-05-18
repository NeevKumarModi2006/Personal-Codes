#include<bits/stdc++.h>
using namespace std;

/*
 * UNIQUE DATA STRUCTURE: Disjoint Set (Union-Find)
 * 
 * Purpose: 
 * Highly efficient data structure for tracking elements partitioned into disjoint (non-overlapping) subsets.
 * Allows near O(1) constant time dynamically querying if two elements are connected.
 * 
 * Common Use Cases:
 * 1. Kruskal's Algorithm: Used to quickly detect if adding an edge forms a cycle in a Spanning Tree.
 * 2. Dynamic Connectivity: Checking if a pathway exists constantly as new edges are inserted (e.g., Number of Islands II).
 * 3. Grouping/Clustering: Accounts Merge problem, grouping similar equations or strings.
 */

class DisjointSet {
    vector<int> rank, parent, size;
public:
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int findUPar(int node) {
        if (node == parent[node])
            return node;
        // Path Compression
        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        }
        else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

int main() {
    cout << "--- Disjoint Set Test Case ---" << endl;
    DisjointSet ds(7);
    
    // Connect some edges
    ds.unionBySize(1, 2);
    ds.unionBySize(2, 3);
    ds.unionBySize(4, 5);
    ds.unionBySize(6, 7);
    ds.unionBySize(5, 6);
    
    // Check if 3 and 7 are connected initially
    cout << "Are 3 and 7 connected? " << (ds.findUPar(3) == ds.findUPar(7) ? "Yes" : "No") << endl;
    
    // Connect component holding 3 with component holding 7
    ds.unionBySize(3, 7);
    cout << "Adding edge between 3 and 7..." << endl;
    
    cout << "Are 3 and 7 connected now? " << (ds.findUPar(3) == ds.findUPar(7) ? "Yes" : "No") << endl;

    return 0;
}
