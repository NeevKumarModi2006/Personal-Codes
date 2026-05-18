#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int data;
    TreeNode *left, *right;
};

void insert(TreeNode* &T, int k) {
    if (!T) {
    T = new TreeNode{k,NULL,NULL};
    }
    else (k < T->data) ? insert(T->left, k) : insert(T->right, k);
}

TreeNode* create(){
        TreeNode* T = NULL;
    int k;
    while (cin >> k && k != -1) insert(T, k);
    return T;
}

void pre(TreeNode* T) {
	if(T) {
		cout<<T->data<<" ";
		pre(T->left);
		pre(T->right);
	}
}   

TreeNode *rotateR(TreeNode *T)
{
    if (!T || !T->left) return T;
    TreeNode *x = T->left;
    T->left = x->right;
    x->right = T;
    return x;
}

TreeNode *rotateL(TreeNode *&T)
{
    if (!T || !T->right) return T;
    TreeNode *x = T->right;
    T->right = x->left;
    x->left = T;
    return x;
}

TreeNode* splay(TreeNode* T, int k) {
    if (T==NULL || T->data == k) return T;
    if (k < T->data) {
        if (!T->left) return T;
        if (k < T->left->data) {
            T->left->left = splay(T->left->left, k);
            T = rotateR(T);
        } else if (k > T->left->data) {
            T->left->right = splay(T->left->right, k);
            if (T->left->right) T->left = rotateL(T->left);
        }
        return T->left ? rotateR(T) : T;
    } else {
        if (!T->right) return T;
        if (k < T->right->data) {
            T->right->left = splay(T->right->left, k);
            if (T->right->left) T->right = rotateR(T->right);
        } else if (k > T->right->data) {
            T->right->right = splay(T->right->right, k);
            T = rotateL(T);
        }
        return T->right ? rotateL(T) : T;
    }
}

TreeNode* convert(TreeNode* T1, TreeNode* T2) {
    if (!T1 || !T2) return NULL;
    T1 = splay(T1,T2->data);
    T1->left = convert(T1->left, T2->left);
    T1->right = convert(T1->right, T2->right);
    return T1;
}

int main() {
    TreeNode* T1 = create();
    TreeNode* T2 = create();
        
        T1 = convert(T1,T2);
        pre(T1);

	return 0;
}

