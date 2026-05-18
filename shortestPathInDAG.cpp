#include <bits/stdc++.h>
using namespace std;

/*
 * UNIQUE ALGORITHM: Shortest Path in Directed Acyclic Graph (DAG)
 * 
 * Purpose: 
 * Finds the shortest path in a DAG in O(V + E) time, which is strictly faster 
 * than Dijkstra's O(E log V). It does this by flattening the graph into a Topological Sort
 * and simply relaxing edges left-to-right.
 * 
 * Common Use Cases:
 * 1. Build Systems/Job Scheduling: Evaluating minimal time required to complete stages (PERT/CPM charts).
 * 2. Evaluating optimal paths in state-spaces where no cycles can possibly exist.
 */

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

int main() {
    cout << "--- Shortest Path in DAG Test Case ---" << endl;
    Solution sol;
    int N = 6, M = 7;
    // edges: {u, v, weight}
    vector<vector<int>> edges = {
        {0, 1, 2}, {0, 4, 1}, {4, 2, 2}, 
        {4, 5, 4}, {1, 2, 3}, {2, 3, 6}, {5, 3, 1}
    };
    
    vector<int> dist = sol.shortestPath(N, M, edges);
    
    cout << "Shortest distances from Source (0):" << endl;
    for (int i = 0; i < N; i++) {
        cout << "Node " << i << " : " << (dist[i] == -1 ? "INF" : to_string(dist[i])) << endl;
    }
    return 0;
}
