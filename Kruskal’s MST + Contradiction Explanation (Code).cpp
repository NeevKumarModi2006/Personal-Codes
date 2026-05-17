#include <bits/stdc++.h>
using namespace std;

const int N = 100;
int par[N], sz[N];

struct edge {
    int u, v, w;
};

vector<edge> edges;

void makeEdge(int u, int v, int w) {
    edges.push_back({u, v, w});
}

// DSU Setup
void init(int n) {
    for (int i = 0; i <= n; i++) {
        par[i] = i;
        sz[i] = 1;
    }
}

int find(int x) {
    if (x == par[x]) return x;
    return par[x] = find(par[x]);
}

bool merge(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;
    if (sz[a] < sz[b]) swap(a, b);
    par[b] = a;
    sz[a] += sz[b];
    return true;
}

int kruskal(int n) {
    sort(edges.begin(), edges.end(), [](edge a, edge b) {
        return a.w < b.w;
    });

    init(n);
    int cost = 0;

    for (auto &e : edges) {
        if (merge(e.u, e.v)) {
            cost += e.w;

            /*
                Contradiction Proof:
                We pick edge (e.u, e.v) because it's the smallest weight 
                that connects two different components.

                Suppose this edge is not in the real MST.
                Then we could replace a heavier edge in the MST's cycle
                with this one, giving us a better or equal MST.
                ⇒ contradiction.
                Hence, the edge is safe and part of some MST.
            */

            cout << "Edge added: " << e.u << " - " << e.v << " = " << e.w << "\n";
        }
    }

    return cost;
}

int main() {
    // Example: 0-based indexing
    makeEdge(0, 1, 10);
    makeEdge(0, 2, 6);
    makeEdge(0, 3, 5);
    makeEdge(1, 3, 15);
    makeEdge(2, 3, 4);

    int V = 4; // number of vertices
    int mst_cost = kruskal(V);

    cout << "Total cost of MST: " << mst_cost << "\n";

    return 0;
}
