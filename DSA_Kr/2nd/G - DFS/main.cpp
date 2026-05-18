#include <bits/stdc++.h>
using namespace std;

void postGraph(int G[10][10],bool visited[10],vector<int>& nums,int st,int &x){
    visited[st] = true;
    for(int j=0;j<10;j++){
        if(G[st][j] && !visited[j]){
            postGraph(G,visited,nums,j,x);
        }
    }
    nums[st]=x;
    x++;
}

int main(){
    int G[10][10]={
        {0,1,0,1,0,0,0,0,0,0},
        {0,0,1,0,0,1,0,0,0,0},
        {1,0,0,1,1,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0},
        {0,0,0,0,0,1,0,1,0,0},
        {0,0,0,0,0,1,0,0,0,1},
        {0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,0,0,0,1,0}
    };
    
    bool visited[10]={false};
    std::vector<int>  nums(10);
    int x=1;
    
    postGraph(G,visited,nums,1,x);
    postGraph(G,visited,nums,7,x);
    postGraph(G,visited,nums,6,x);
    
    for(int j=0;j<10;j++)  cout<<j+1<<" "<<nums[j]<<endl;

    return 0;
}
