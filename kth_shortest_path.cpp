#include <algorithm>
#include <cstdint>
#include <functional>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

// KSPs - K Shortest Paths
// This file contains 4 implementations:
// 1) Yen's Algorithm (k shortest LOOPLESS/simple paths) for NON-NEGATIVE edges.
// 2) k-Dijkstra (k shortest WALKS; vertices may repeat) for NON-NEGATIVE edges.
// 3) Johnson Reweighting + Yen (k shortest LOOPLESS paths; supports NEGATIVE edges too)
//    Works if and only if there is NO negative cycle reachable in the graph.
// 4) Eppstein's Algorithm (k shortest paths; typically allows cycles) for NON-NEGATIVE edges.
//
// Complexity summary (high-level):
// - Yen (non-negative): about O(k * (E log V)) Dijkstra work + overhead.
//   Good practical choice for k shortest *simple* paths.
// - k-Dijkstra walks (non-negative): about O(k * E log (kV)) states.
//   Often faster/simpler, but allows revisiting nodes (not loopless).
// - Johnson+Yen (negative edges): O(VE) (Bellman-Ford) + Yen on reweighted graph.
//   This is a standard "optimal practical" way to handle negative edges while still using Dijkstra.
// - Eppstein (non-negative): O(E + V log V + k log k) after a single Dijkstra-to-target preprocessing.
//   Very efficient for large k, but it enumerates k shortest paths (can include cycles) in general.
//
// Input format:
// n                  // number of vertices
// m                  // number of edges
// k                  // how many shortest paths to print
// u v w              // m lines of directed weighted edges
// ...
// src dst            // find k shortest paths from src to dst
//
// Output format (for each path found, up to k):
// total_length
// path_vertices...
//
// Sample input (from your screenshot):
// 6
// 8
// 3
// 1 2 5
// 2 3 3
// 2 4 8
// 3 4 1
// 4 5 7
// 1 5 18
// 5 6 11
// 6 1 12
// 1 6

// Sample Output : 
// 27
// 1 2 3 4 5 6
// 29
// 1 5 6
// 31
// 1 2 4 5 6

struct Edge {
    int to;
    long long w;
};

static long long edgeKey(int u, int v) {
    return (static_cast<long long>(u) << 32) ^ static_cast<unsigned long long>(v);
}

struct DijkstraResult {
    bool ok = false;
    long long dist = (long long)4e18;
    vector<int> path;
};

// Dijkstra for non-negative edges, with optional bans used by Yen.
static DijkstraResult dijkstraNonNegative(
    int n,
    const vector<vector<Edge>> &adj,
    int src,
    int dst,
    const unordered_set<int> &bannedNodes,
    const unordered_set<long long> &bannedEdges
) {
    if (bannedNodes.count(src) || bannedNodes.count(dst)) return {};

    const long long INF = (long long)4e18;
    vector<long long> dist(n + 1, INF);
    vector<int> parent(n + 1, -1);

    using State = pair<long long, int>;
    priority_queue<State, vector<State>, greater<State>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        if (u == dst) break;
        if (bannedNodes.count(u)) continue;

        for (const auto &e : adj[u]) {
            int v = e.to;
            if (bannedNodes.count(v)) continue;
            if (bannedEdges.count(edgeKey(u, v))) continue;
            long long nd = d + e.w;
            if (nd < dist[v]) {
                dist[v] = nd;
                parent[v] = u;
                pq.push({nd, v});
            }
        }
    }

    if (dist[dst] >= INF / 2) return {};

    vector<int> path;
    for (int cur = dst; cur != -1; cur = parent[cur]) path.push_back(cur);
    reverse(path.begin(), path.end());

    if (path.empty() || path.front() != src) return {};

    DijkstraResult res;
    res.ok = true;
    res.dist = dist[dst];
    res.path = std::move(path);
    return res;
}

static string encodePath(const vector<int> &p) {
    // Simple encoding for de-duplication.
    string s;
    s.reserve(p.size() * 3);
    for (int x : p) {
        s.append(to_string(x));
        s.push_back(',');
    }
    return s;
}

static long long pathCost(const vector<int> &p, const unordered_map<long long, long long> &minW) {
    long long total = 0;
    for (size_t i = 0; i + 1 < p.size(); i++) {
        auto it = minW.find(edgeKey(p[i], p[i + 1]));
        if (it == minW.end()) return (long long)4e18;
        total += it->second;
    }
    return total;
}

struct Candidate {
    long long cost;
    vector<int> path;
};

struct CandidateCmp {
    bool operator()(const Candidate &a, const Candidate &b) const {
        if (a.cost != b.cost) return a.cost > b.cost; // min-heap behavior via priority_queue
        return a.path > b.path; // deterministic tie-break
    }
};

struct WalkState {
    long long dist;
    int v;
    int parentIdx;
};

static vector<int> buildPathFromStates(const vector<WalkState> &states, int idx) {
    vector<int> p;
    while (idx != -1) {
        p.push_back(states[idx].v);
        idx = states[idx].parentIdx;
    }
    reverse(p.begin(), p.end());
    return p;
}

static unordered_map<long long, long long> buildMinEdgeMap(
    int n,
    const vector<vector<Edge>> &adj
) {
    (void)n;
    unordered_map<long long, long long> minW;
    size_t approx = 0;
    for (int u = 1; u < (int)adj.size(); u++) approx += adj[u].size();
    minW.reserve(approx * 2 + 1);
    for (int u = 1; u < (int)adj.size(); u++) {
        for (const auto &e : adj[u]) {
            long long key = edgeKey(u, e.to);
            auto it = minW.find(key);
            if (it == minW.end() || e.w < it->second) minW[key] = e.w;
        }
    }
    return minW;
}

// 1) Yen's Algorithm (loopless/simple paths), NON-NEGATIVE edges.
// Complexity: ~ O(k * (E log V)) (k times Dijkstra), plus candidate bookkeeping.
static vector<Candidate> yenKShortestLooplessNonNegative(
    int n,
    const vector<vector<Edge>> &adj,
    const unordered_map<long long, long long> &minW,
    int src,
    int dst,
    int k
) {
    vector<Candidate> result;
    if (k <= 0) return result;

    unordered_set<int> emptyNodes;
    unordered_set<long long> emptyEdges;
    auto first = dijkstraNonNegative(n, adj, src, dst, emptyNodes, emptyEdges);
    if (!first.ok) return result;

    vector<vector<int>> A;
    vector<long long> Acost;
    unordered_set<string> seenPaths;
    seenPaths.reserve((size_t)k * 10);

    A.push_back(first.path);
    Acost.push_back(first.dist);
    seenPaths.insert(encodePath(first.path));

    priority_queue<Candidate, vector<Candidate>, CandidateCmp> B;
    unordered_set<string> seenCandidates;
    seenCandidates.reserve((size_t)k * 50);

    for (int kth = 1; kth < k; kth++) {
        const vector<int> &prevPath = A.back();
        int L = (int)prevPath.size();

        for (int i = 0; i < L - 1; i++) {
            int spurNode = prevPath[i];

            vector<int> rootPath(prevPath.begin(), prevPath.begin() + i + 1);
            long long rootCost = pathCost(rootPath, minW);
            if (rootCost >= (long long)4e18 / 2) continue;

            unordered_set<int> bannedNodes;
            bannedNodes.reserve(rootPath.size() * 2);
            for (int r = 0; r < i; r++) bannedNodes.insert(rootPath[r]);

            unordered_set<long long> bannedEdges;
            // Remove edges that would recreate previously found paths with same root.
            for (size_t pidx = 0; pidx < A.size(); pidx++) {
                const auto &p = A[pidx];
                if ((int)p.size() <= i + 1) continue;

                bool samePrefix = true;
                for (int t = 0; t <= i; t++) {
                    if (p[t] != rootPath[t]) {
                        samePrefix = false;
                        break;
                    }
                }
                if (samePrefix) {
                    bannedEdges.insert(edgeKey(p[i], p[i + 1]));
                }
            }

            auto spur = dijkstraNonNegative(n, adj, spurNode, dst, bannedNodes, bannedEdges);
            if (!spur.ok) continue;

            vector<int> totalPath = rootPath;
            for (size_t t = 1; t < spur.path.size(); t++) totalPath.push_back(spur.path[t]);

            string code = encodePath(totalPath);
            if (seenPaths.count(code)) continue;
            if (seenCandidates.count(code)) continue;

            long long totalCost = rootCost + spur.dist;
            B.push({totalCost, std::move(totalPath)});
            seenCandidates.insert(code);
        }

        if (B.empty()) break;

        Candidate best = B.top();
        B.pop();

        string bestCode = encodePath(best.path);
        if (seenPaths.count(bestCode)) {
            kth--; // pull next
            continue;
        }

        A.push_back(best.path);
        Acost.push_back(best.cost);
        seenPaths.insert(bestCode);
    }

    result.reserve(A.size());
    for (size_t i = 0; i < A.size(); i++) result.push_back({Acost[i], A[i]});
    return result;
}

// 2) k-Dijkstra for k shortest WALKS (paths may contain repeated vertices), NON-NEGATIVE edges.
// This is often used when "k shortest paths" doesn't forbid cycles.
// Complexity: roughly O(k * E log (kV)) in practice.
static vector<Candidate> kDijkstraKShortestWalksNonNegative(
    int n,
    const vector<vector<Edge>> &adj,
    int src,
    int dst,
    int k
) {
    vector<Candidate> result;
    if (k <= 0) return result;
    struct HeapItem {
        long long dist;
        int idx;
        bool operator>(const HeapItem &other) const {
            if (dist != other.dist) return dist > other.dist;
            return idx > other.idx;
        }
    };

    vector<WalkState> states;
    states.reserve((size_t)k * 50);

    priority_queue<HeapItem, vector<HeapItem>, greater<HeapItem>> pq;
    vector<int> popped(n + 1, 0);

    states.push_back({0, src, -1});
    pq.push({0, 0});

    while (!pq.empty() && (int)result.size() < k) {
        auto cur = pq.top();
        pq.pop();

        const auto &st = states[cur.idx];
        int u = st.v;

        if (popped[u] >= k) continue;
        popped[u]++;

        if (u == dst) {
            result.push_back({st.dist, buildPathFromStates(states, cur.idx)});
            continue;
        }

        // Expand outgoing edges
        for (const auto &e : adj[u]) {
            int v = e.to;
            long long nd = st.dist + e.w;
            states.push_back({nd, v, cur.idx});
            pq.push({nd, (int)states.size() - 1});
        }
    }

    return result;
}

// ------------------------------
// 4) Eppstein's Algorithm (NON-NEGATIVE edges)
// ------------------------------
// Finds k shortest paths from src to dst in a directed graph with NON-NEGATIVE weights.
// Note: "paths" here are the k shortest routes by total weight; cycles may appear.
// Complexity: O(E + V log V + k log k) (typical/expected), very fast when k is large.

struct SidetrackEdge {
    int from;
    int to;
    long long delta; // reduced cost: w + dist[to] - dist[from] (>= 0)
};

struct LeftistHeapNode {
    long long key; // delta
    int edgeIdx;   // index into sidetrack array
    const LeftistHeapNode *left;
    const LeftistHeapNode *right;
    int rank;
};

static int heapRank(const LeftistHeapNode *h) {
    return h ? h->rank : 0;
}

static const LeftistHeapNode *newHeapNode(
    long long key,
    int edgeIdx,
    const LeftistHeapNode *left,
    const LeftistHeapNode *right
) {
    LeftistHeapNode *n = new LeftistHeapNode{key, edgeIdx, left, right, 1};
    n->rank = heapRank(n->right) + 1;
    return n;
}

// Persistent leftist-heap merge: returns a new heap root, does not mutate inputs.
static const LeftistHeapNode *heapMerge(const LeftistHeapNode *a, const LeftistHeapNode *b) {
    if (!a) return b;
    if (!b) return a;
    if (a->key > b->key) std::swap(a, b);

    const LeftistHeapNode *mergedRight = heapMerge(a->right, b);
    const LeftistHeapNode *resLeft = a->left;
    const LeftistHeapNode *resRight = mergedRight;

    if (heapRank(resLeft) < heapRank(resRight)) std::swap(resLeft, resRight);

    return newHeapNode(a->key, a->edgeIdx, resLeft, resRight);
}

static const LeftistHeapNode *heapInsert(const LeftistHeapNode *h, long long key, int edgeIdx) {
    const LeftistHeapNode *single = newHeapNode(key, edgeIdx, nullptr, nullptr);
    return heapMerge(h, single);
}

static void dijkstraToTargetNonNegative(
    int n,
    const vector<vector<Edge>> &adj,
    int dst,
    vector<long long> &dist,
    vector<int> &nextHop
) {
    const long long INF = (long long)4e18;
    dist.assign(n + 1, INF);
    nextHop.assign(n + 1, -1);

    vector<vector<Edge>> rev(n + 1);
    for (int u = 1; u <= n; u++) {
        for (const auto &e : adj[u]) {
            rev[e.to].push_back({u, e.w});
        }
    }

    using State = pair<long long, int>;
    priority_queue<State, vector<State>, greater<State>> pq;
    dist[dst] = 0;
    pq.push({0, dst});

    while (!pq.empty()) {
        auto cur = pq.top();
        pq.pop();
        long long d = cur.first;
        int x = cur.second;
        if (d != dist[x]) continue;

        for (const auto &re : rev[x]) {
            int p = re.to;       // original edge p -> x
            long long w = re.w;
            long long nd = d + w;
            if (nd < dist[p]) {
                dist[p] = nd;
                nextHop[p] = x;
                pq.push({nd, p});
            }
        }
    }
}

static vector<int> buildShortestTreePath(int src, int dst, const vector<int> &nextHop) {
    vector<int> p;
    int cur = src;
    p.push_back(cur);
    while (cur != dst && cur != -1) {
        cur = nextHop[cur];
        if (cur == -1) break;
        p.push_back(cur);
    }
    if (!p.empty() && p.back() != dst) return {};
    return p;
}

static vector<int> buildEppsteinVertexPath(
    int src,
    int dst,
    const vector<int> &nextHop,
    const vector<SidetrackEdge> &sidetracks,
    const vector<int> &sidetrackEdgeIndices
) {
    vector<int> path;
    path.push_back(src);
    int cur = src;

    for (size_t i = 0; i < sidetrackEdgeIndices.size(); i++) {
        int eidx = sidetrackEdgeIndices[i];
        const SidetrackEdge &se = sidetracks[eidx];

        // Follow shortest-path tree from cur to se.from
        while (cur != se.from && cur != -1) {
            cur = nextHop[cur];
            if (cur == -1) break;
            path.push_back(cur);
        }
        if (cur != se.from) return {};

        // Take sidetrack edge
        cur = se.to;
        path.push_back(cur);
    }

    // Finish by following shortest-path tree to dst
    while (cur != dst && cur != -1) {
        cur = nextHop[cur];
        if (cur == -1) break;
        path.push_back(cur);
    }
    if (!path.empty() && path.back() != dst) return {};
    return path;
}

static vector<Candidate> eppsteinKShortestPathsNonNegative(
    int n,
    const vector<vector<Edge>> &adj,
    int src,
    int dst,
    int k
) {
    vector<Candidate> result;
    if (k <= 0) return result;

    vector<long long> dist;
    vector<int> nextHop;
    dijkstraToTargetNonNegative(n, adj, dst, dist, nextHop);
    if (dist[src] >= (long long)4e18 / 2) return result;

    // First path: the shortest-path-tree route.
    vector<int> basePath = buildShortestTreePath(src, dst, nextHop);
    if (basePath.empty()) return result;
    result.push_back({dist[src], basePath});
    if (k == 1) return result;

    // Collect sidetracks and build heaps.
    vector<SidetrackEdge> sid;
    sid.reserve(1024);

    vector<const LeftistHeapNode *> heapAt(n + 1, nullptr);

    for (int u = 1; u <= n; u++) {
        if (dist[u] >= (long long)4e18 / 2) continue;
        for (const auto &e : adj[u]) {
            if (dist[e.to] >= (long long)4e18 / 2) continue;

            // Tree edge is the dijkstra-chosen nextHop[u]. Everything else is a sidetrack.
            bool isTreeEdge = (nextHop[u] == e.to) && (dist[u] == e.w + dist[e.to]);
            if (isTreeEdge) continue;

            long long delta = e.w + dist[e.to] - dist[u];
            if (delta < 0) continue; // should not happen for non-negative weights with correct dist

            int idx = (int)sid.size();
            sid.push_back({u, e.to, delta});
            heapAt[u] = heapInsert(heapAt[u], delta, idx);
        }
    }

    // Build H(u): merge of sidetracks along the shortest-path tree from u to dst.
    vector<int> order;
    order.reserve(n);
    for (int u = 1; u <= n; u++) {
        if (dist[u] < (long long)4e18 / 2) order.push_back(u);
    }
    struct DistCmp {
        const vector<long long> *d;
        bool operator()(int a, int b) const {
            return (*d)[a] < (*d)[b];
        }
    };
    sort(order.begin(), order.end(), DistCmp{&dist});

    vector<const LeftistHeapNode *> H(n + 1, nullptr);
    // Build in increasing dist so parent (closer to dst) comes first.
    for (size_t i = 0; i < order.size(); i++) {
        int u = order[i];
        if (u == dst || nextHop[u] == -1) {
            H[u] = heapAt[u];
        } else {
            H[u] = heapMerge(heapAt[u], H[nextHop[u]]);
        }
    }

    struct PQItem {
        long long extra;
        const LeftistHeapNode *node;
        int prev;
        int stateIdx;
        bool operator>(const PQItem &o) const {
            if (extra != o.extra) return extra > o.extra;
            return node > o.node;
        }
    };

    struct StateRec {
        long long extra;
        const LeftistHeapNode *node;
        int prev;
    };
    vector<StateRec> states;
    states.reserve((size_t)k * 10);

    priority_queue<PQItem, vector<PQItem>, greater<PQItem>> pq;
    if (H[src]) {
        states.push_back({H[src]->key, H[src], -1});
        pq.push({H[src]->key, H[src], -1, 0});
    }

    unordered_set<string> seen;
    seen.reserve((size_t)k * 10);
    seen.insert(encodePath(basePath));

    while (!pq.empty() && (int)result.size() < k) {
        PQItem it = pq.top();
        pq.pop();

        int idx = it.stateIdx;
        const LeftistHeapNode *x = it.node;
        if (!x) continue;

        // Reconstruct sidetrack sequence
        vector<int> seq;
        int cur = idx;
        while (cur != -1) {
            seq.push_back(states[cur].node->edgeIdx);
            cur = states[cur].prev;
        }
        reverse(seq.begin(), seq.end());

        vector<int> path = buildEppsteinVertexPath(src, dst, nextHop, sid, seq);
        if (path.empty()) continue;
        string code = encodePath(path);
        if (seen.insert(code).second) {
            result.push_back({dist[src] + it.extra, path});
        }

        // 1) Replace the last chosen sidetrack by an alternative from the same heap (children).
        if (x->left) {
            long long extra2 = it.extra - x->key + x->left->key;
            states.push_back({extra2, x->left, it.prev});
            pq.push({extra2, x->left, it.prev, (int)states.size() - 1});
        }
        if (x->right) {
            long long extra2 = it.extra - x->key + x->right->key;
            states.push_back({extra2, x->right, it.prev});
            pq.push({extra2, x->right, it.prev, (int)states.size() - 1});
        }

        // 2) Append a new sidetrack after taking this sidetrack edge.
        int to = sid[x->edgeIdx].to;
        if (to >= 1 && to <= n && H[to]) {
            long long extra2 = it.extra + H[to]->key;
            states.push_back({extra2, H[to], idx});
            pq.push({extra2, H[to], idx, (int)states.size() - 1});
        }
    }

    return result;
}

// Bellman-Ford potentials for Johnson's algorithm.
// Returns false if a negative cycle exists.
static bool bellmanFordPotentials(
    int n,
    const vector<tuple<int, int, long long>> &edges,
    vector<long long> &h
) {
    // Super-source with 0 edges to all nodes => initialize h = 0 and relax.
    const long long INF = (long long)4e18;
    h.assign(n + 1, 0);

    for (int iter = 1; iter <= n; iter++) {
        bool changed = false;
        for (const auto &[u, v, w] : edges) {
            if (h[u] + w < h[v]) {
                h[v] = h[u] + w;
                changed = true;
            }
        }
        if (!changed) return true;
        if (iter == n && changed) return false; // negative cycle
    }
    return true;
}

// 3) Johnson Reweighting + Yen (loopless), supports NEGATIVE edges too.
// Optimal practical approach: O(VE) for Bellman-Ford + Yen on non-negative reweighted graph.
static vector<Candidate> johnsonYenKShortestLooplessAllowNegative(
    int n,
    const vector<vector<Edge>> &adjOriginal,
    const vector<tuple<int, int, long long>> &edgesOriginal,
    int src,
    int dst,
    int k
) {
    vector<long long> h;
    if (!bellmanFordPotentials(n, edgesOriginal, h)) {
        // Negative cycle exists: "shortest" paths are not well-defined.
        return {};
    }

    // Reweight edges to make them non-negative.
    vector<vector<Edge>> adj(n + 1);
    adj.reserve(adjOriginal.size());
    for (int u = 1; u <= n; u++) {
        for (const auto &e : adjOriginal[u]) {
            long long w2 = e.w + h[u] - h[e.to];
            if (w2 < 0) {
                // Should not happen if no negative cycle and BF potentials are correct.
                return {};
            }
            adj[u].push_back({e.to, w2});
        }
    }

    auto minW2 = buildMinEdgeMap(n, adj);
    auto pathsReweighted = yenKShortestLooplessNonNegative(n, adj, minW2, src, dst, k);

    // Convert distances back to original weights:
    // sum(w') = sum(w) + h[src] - h[dst]  =>  sum(w) = sum(w') - h[src] + h[dst]
    for (auto &c : pathsReweighted) {
        c.cost = c.cost - h[src] + h[dst];
    }
    return pathsReweighted;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    int k;
    if (!(cin >> n)) return 0;
    cin >> m;
    cin >> k;

    vector<vector<Edge>> adj(n + 1);
    vector<tuple<int, int, long long>> edges;
    edges.reserve((size_t)m);
    bool hasNegativeEdge = false;

    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        edges.push_back({u, v, w});
        if (w < 0) hasNegativeEdge = true;
    }

    int src, dst;
    cin >> src >> dst;

    vector<Candidate> ans;
    if (hasNegativeEdge) {
        ans = johnsonYenKShortestLooplessAllowNegative(n, adj, edges, src, dst, k);
    } else {
        auto minW = buildMinEdgeMap(n, adj);
        ans = yenKShortestLooplessNonNegative(n, adj, minW, src, dst, k);
        // If you want the faster "walks" variant instead, use:
        // ans = kDijkstraKShortestWalksNonNegative(n, adj, src, dst, k);
        // If you want Eppstein (very fast for large k, non-negative edges), use:
        // ans = eppsteinKShortestPathsNonNegative(n, adj, src, dst, k);
    }

    for (const auto &p : ans) {
        cout << p.cost << "\n";
        for (size_t i = 0; i < p.path.size(); i++) {
            if (i) cout << ' ';
            cout << p.path[i];
        }
        cout << "\n";
    }

    return 0;
}
