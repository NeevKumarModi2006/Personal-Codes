#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
};

void insert(TreeNode* &T, int k) {
    if (!T) {
        T = new TreeNode;
        T->data = k;
        T->left = T->right = NULL;
        return;
    }
    (k < T->data) ? insert(T->left, k) : insert(T->right, k);
}

void pre(TreeNode* T){
if(T){
    cout<<T->data<<" ";
    pre(T->left);
    pre(T->right);
}
}
TreeNode* create(){
        TreeNode* T = NULL;
    int k;
    while (cin >> k && k != -1) insert(T, k);
    return T;
}

set<vector<int>>ans;

void trav(int a,int b,TreeNode* T){
    if(!T) return;
if(a+b==T->data) ans.insert({a,b,T->data});
else if(a+b<T->data) trav(a,b,T->left);
else trav(a,b,T->right);
}

void findPrint(TreeNode* T1, TreeNode* T2, TreeNode* alpha,TreeNode* beta){
if(!T1 || !T2) return;
trav(T1->data,T2->data,alpha);
trav(T1->data,T2->data,beta);
findPrint(T1->right,T2,alpha,beta);
findPrint(T1,T2->left,alpha,beta);
findPrint(T1->left,T2,alpha,beta);
findPrint(T1,T2->right,alpha,beta);
}

int main() {

    TreeNode* T1 = create();
    TreeNode* T2 = create();
    findPrint(T1,T2,T1,T2);
    
    for(auto i : ans) cout<<i[0]<<" "<<i[1]<<" "<<i[2]<<endl;
    
    return 0;
}
