#include<bits/stdc++.h>
using namespace std;


struct TreeNode{
    int data;
 TreeNode* left,*right;   
};

TreeNode* create(vector<int> &v,int &i){
  if(v[i++]==-1) return NULL;
  i--;
  return new TreeNode{v[i++],create(v,i),create(v,i)};
}

int ans = 0;
void find_freq(TreeNode* T,int &k){
 if(!T) return;
 if(T->data == k) ans++;
 find_freq(T->left,k);
 find_freq(T->right,k);
}

void pre(TreeNode* T){
 if(!T) return;
 cout<<T->data<<" ";
 pre(T->left);
 pre(T->right);
}


int main(){
    vector<int>v = {0,7,22,5,-1,-1,45,-1,-1,10,-1,-1,0,42,-1,18,10,-1,-1,35,-1,-1,0,63,7,-1,-1,36,5,-1,-1,18,-1,-1,0,
        18,-1,27,22,-1,-1,-1,0,12,36,-1,-1,7,85,-1,-1,52,-1,-1,-1
    };
    int i=0;
  TreeNode* T = create(v,i);
  int k; cin>>k;
//   pre(T);
    find_freq(T,k);
    
    cout<<(ans?ans:-1);
    
    return 0;
}