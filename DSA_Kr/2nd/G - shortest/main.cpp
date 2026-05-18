#include <bits/stdc++.h>
using namespace std;

struct node{
    int data;
    int r;  
    int b;
};

bool find(vector<node> &vec,node &temp){
    for(node t:vec){
        if(t.data==temp.data && t.r==temp.r && t.b==temp.b) return true;
    }
    return false;
}

void shortest_legal_path(int G[6][6],vector<node> &vec,vector<int> &ans,int start,int end,int r,int b){  
    if(start==end){
        if(ans.empty() || vec.size()<ans.size()){
            ans.clear();
            for(int i=0;i<vec.size();i++) ans.push_back(vec[i].data);
            ans.push_back(end);
        }
        return;
    }
    node temp;
    temp.data=start;temp.r=r;temp.b=b;
    if(find(vec,temp)) return;
    vec.push_back(temp);
    for(int j=0;j<6;j++){
        if(G[start][j]==1 && r!=2){
            shortest_legal_path(G,vec,ans,j,end,r+1,0);
        }
        else if(G[start][j]==2 && b!=2){
            shortest_legal_path(G,vec,ans,j,end,0,b+1);
        }
    }
    vec.pop_back();
}

int main(){
    //1 for red and 2 for blue
    int G[6][6]={
        {0,1,0,0,0,0},{0,0,1,0,0,0},{0,0,0,1,2,0},{0,2,0,0,1,0},{2,0,0,0,0,1},{1,2,0,0,0,0}
    };
    char v[6]={'s','a','b','t','d','c'};
    int start=0,end=3; //s to t
    vector<node> vec;
    vector<int> ans;
    shortest_legal_path(G,vec,ans,start,end,0,0);
    cout<<ans.size()-1<<endl;
    for(int val:ans) cout<<v[val]<<" ";
    return 0;
}