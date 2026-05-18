#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
};

TreeNode* create(void) {
int k; cin>>k;
if(k==0) return NULL;
TreeNode* T = new TreeNode{k,NULL,NULL};
T->left = create();
T->right = create();
return T;
}

void pairFunc(TreeNode* T1, TreeNode* T2){
    if(!T1 || !T2) return;
    if(T1->left && T2->right) cout<<T1->left->data<<" "<<T2->right->data<<" ";
    if(T1->right && T2->left) cout<<T1->right->data<<" "<<T2->left->data<<" ";    
    pairFunc(T1->left,T2->left);
    pairFunc(T1->right,T2->right);
}

int main() {
    
    TreeNode* T1 =  create();
    TreeNode* T2 =  create();
   pairFunc(T1,T2);
   
    return 0;
}

