#include <bits/stdc++.h>
using namespace std;

/*
 * ALGORITHM: Shortest Path in Undirected Graph with Unit Weights
 * 
 * Purpose: 
 * Uses standard Breadth-First Search (BFS) to find the shortest path from a given source
 * to all other nodes. 
 * Because all edge weights are exactly 1, the first time we visit a node, we guarantee it's 
 * via the shortest path.
 * Time Complexity: O(V + E)
 * 
 * Common Use Cases:
 * 1. Finding minimum jumps/steps in an unweighted grid (e.g., Minimum Knights moves, distance of nearest 1).
 * 2. Word Ladder problems (minimum transformation sequences).
 */

class Solution {
public:
    vector<int> shortestPath(vector<vector<int>>& edges, int N, int M, int src){
        vector<int> adj[N];
        for(auto it : edges) {
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }
        
        vector<int> dist(N, 1e9);
        dist[src] = 0;
        queue<int> q;
        q.push(src);
        
        while(!q.empty()) {
            int node = q.front();
            q.pop();
            
            for(auto it : adj[node]) {
                if(dist[node] + 1 < dist[it]) {
                    dist[it] = dist[node] + 1;
                    q.push(it);
                }
            }
        }
        
        vector<int> ans(N, -1);
        for(int i = 0; i < N; i++) {
            if(dist[i] != 1e9) {
                ans[i] = dist[i];
            }
        }
        return ans;
    }
};

int main() {
    cout << "--- Undirected Graph Unit Weights BFS Test Case ---" << endl;
    Solution sol;
    int N = 9, M = 10, src = 0;
    // edges: randomly connected graph
    vector<vector<int>> edges = {
        {0, 1}, {0, 3}, {3, 4}, {4, 5}, 
        {5, 6}, {1, 2}, {2, 6}, {6, 7}, {7, 8}, {6, 8}
    };
    
    vector<int> dist = sol.shortestPath(edges, N, M, src);
    
    cout << "Shortest distances from Source (" << src << "):" << endl;
    for (int i = 0; i < N; i++) {
        cout << "Node " << i << " : " << (dist[i] == -1 ? "INF" : to_string(dist[i])) << endl;
    }
    return 0;
}
