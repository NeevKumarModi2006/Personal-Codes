#include <bits/stdc++.h>
using namespace std;

// Algorithm: Shortest Path in Directed Acyclic Graph (DAG)
// Uses Topological Sorting to find the shortest path in O(V + E) time

class Solution {
private:
    void topoSort(int node, vector<pair<int, int>> adj[], int vis[], stack<int> &st) {
        vis[node] = 1;
        for (auto it : adj[node]) {
            int v = it.first;
            if (!vis[v]) {
                topoSort(v, adj, vis, st);
            }
        }
        st.push(node);
    }

public:
    vector<int> shortestPath(int N, int M, vector<vector<int>>& edges) {
        vector<pair<int, int>> adj[N];
        for (int i = 0; i < M; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            int wt = edges[i][2];
            adj[u].push_back({v, wt});
        }

        int vis[N] = {0};
        stack<int> st;

        // 1. Perform Topo Sort
        for (int i = 0; i < N; i++) {
            if (!vis[i]) {
                topoSort(i, adj, vis, st);
            }
        }

        // 2. Process nodes in Topological Order
        vector<int> dist(N, 1e9);
        dist[0] = 0; // Assuming source is 0

        while (!st.empty()) {
            int node = st.top();
            st.pop();

            if (dist[node] != 1e9) {
                for (auto it : adj[node]) {
                    int v = it.first;
                    int wt = it.second;

                    if (dist[node] + wt < dist[v]) {
                        dist[v] = dist[node] + wt;
                    }
                }
            }
        }

        for (int i = 0; i < N; i++) {
            if (dist[i] == 1e9) dist[i] = -1; // Unreachable
        }

        return dist;
    }
};
