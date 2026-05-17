#include <bits/stdc++.h>
using namespace std;

const int N = 7;
vector<vector<int>> G =
    {
        {0, 5, 0, 10, 8, 0, 0}, // s
        {5, 0, 1, 4, 0, 6, 0},
        {0, 1, 0, 0, 0, 11, 0},
        {10, 4, 0, 0, 9, 3, 0},
        {8, 0, 0, 9, 0, 0, 12},
        {0, 0, 11, 3, 0, 7, 0}, // t
        {0, 0, 0, 0, 2, 12, 7}};

        int ans = INT_MAX;
void getAns(vector<pair<int,int>> &arr){
    int ansdummy = 0;
for(auto i : arr) ansdummy = max(ansdummy,arr[i.first][i.second]);
ans = min(ans, ansdummy);
}

void path(int s, int t, visited<bool> &vis,vector<pair<int,int>> &arr)
{
    vis[s] = true;
    if (s == t)
    {
        getAns(arr);
        vis[s] = false;
        return;
    }

    for (int i = 0; i < N; i++)
    {
        if (!vis[i] && G[s][i] != 0)
            path(i, t, vis);
    }
    vis[s] = false;
}

int main()
{
    vector<pair<int,int>> arr;
    vector<bool> vis(N, false);
    path(0, 5);

    return 0;
}