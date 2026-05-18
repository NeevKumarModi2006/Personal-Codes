#include <bits/stdc++.h>
using namespace std;

/*
 * UNIQUE ALGORITHM: Hierholzer's Algorithm
 * 
 * Purpose: 
 * Used to find an Eulerian Path or Eulerian Circuit in a directed or undirected graph.
 * An Eulerian Path visits every edge in a graph exactly once.
 * 
 * Common Use Cases:
 * 1. Itinerary Reconstruction: Given a list of flights (edges), reconstruct the path visiting all flights.
 * 2. DNA Sequencing: Genome assembly using De Bruijn graphs where overlapping kmers form edges.
 * 3. Routing problems: Finding paths that must perfectly traverse every distinct road/route once.
 */

vector<string> nodeList;
vector<string> ans;

void dfs(int u, vector<vector<int>>& arr, vector<int>& index) {
    while(index[u] < arr[u].size()) {
        int v = arr[u][index[u]++];
        dfs(v, arr, index);
    }
    ans.push_back(nodeList[u]);
}

vector<string> findEulerianPath(vector<vector<string>>& edges, string startNode) {
    ans.clear();
    set<string> st;

    for(auto &ss : edges) {
        for(auto &s : ss) {
            st.insert(s);
        }
    }

    nodeList = vector<string>(st.begin(), st.end());
    vector<vector<int>> arr(nodeList.size());

    for(auto &ss : edges) {
        int u = lower_bound(nodeList.begin(), nodeList.end(), ss[0]) - nodeList.begin();
        int v = lower_bound(nodeList.begin(), nodeList.end(), ss[1]) - nodeList.begin();
        arr[u].push_back(v);
    }

    // Sort to handle lexical ordering (e.g., JFK -> smallest lexical destination first)
    for(auto &v : arr) {
        sort(v.begin(), v.end());
    }

    vector<int> index(nodeList.size(), 0);
    int start = lower_bound(nodeList.begin(), nodeList.end(), startNode) - nodeList.begin();

    dfs(start, arr, index);
    reverse(ans.begin(), ans.end());

    return ans;
}

int main() {
    cout << "--- Hierholzer's Algorithm Test Case ---" << endl;
    vector<vector<string>> tickets = {
        {"JFK","SFO"}, {"JFK","ATL"}, {"SFO","ATL"}, {"ATL","JFK"}, {"ATL","SFO"}
    };
    
    vector<string> itinerary = findEulerianPath(tickets, "JFK");
    
    cout << "Reconstructed Itinerary: ";
    for(int i = 0; i < itinerary.size(); i++) {
        cout << itinerary[i] << (i == itinerary.size()-1 ? "" : " -> ");
    }
    cout << endl;
    return 0;
}
