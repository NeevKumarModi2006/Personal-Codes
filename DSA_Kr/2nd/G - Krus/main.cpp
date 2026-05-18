#include <bits/stdc++.h>
using namespace std;

const int N = 7;
vector<vector<int>> G(N, vector<int>(N, INT_MAX));

inline void makeEdge(int i, int j, int w) {
    G[i-1][j-1] = w;
    G[j-1][i-1] = w;
}

vector<vector<int>> getEdges() {
    vector<vector<int>> arr;
    for(int i = 0; i < N; i++) 
        for(int j = i; j < N; j++) 
            if(G[i][j] != INT_MAX)
                arr.push_back({G[i][j], i, j});
    return arr;
}


int find(vector<int> &S,int x) {
    if (S[x] == x) return x;
    return find(S,S[x]);
}



void unionSet(vector<int> &S,int i, int j) {
    S[find(S,i)] = find(S,j);
}

void kruskal1() {
    vector<int> S(N);
    vector<vector<int>> edges = getEdges();
    sort(edges.begin(), edges.end());
    vector<vector<int>> A;
    for(int i = 0; i < N; i++) S[i] = i;
    int cnt = 0;
    for(auto &edge : edges) {
        int w = edge[0], u = edge[1], v = edge[2];
        if (find(S,u) != find(S,v)) {
            A.push_back({u, v, w});
            unionSet(S,u,v);
            cnt++;
        }
        else A.push_back({u,v,0});
        if (cnt == N - 1) break;
    }
    int sum = 0;
    for (auto &i : A) {
        if(i[2]) sum+=i[2] ;
        cout << i[0] + 1 << " " << i[1] + 1 << " " << (i[2]?1:0) << endl;
    }
    
    cout<<sum;
}

int main() {
    makeEdge(1,2,2);
    makeEdge(1,4,1);
    makeEdge(1,3,4);
    makeEdge(2,5,10);
    makeEdge(2,4,3);
    makeEdge(5,7,6);
    makeEdge(5,4,7);
    makeEdge(7,4,4);
    makeEdge(7,6,1);
    makeEdge(4,6,8);
    makeEdge(3,4,2);
    makeEdge(3,6,5);

    kruskal1();

    return 0;
}
