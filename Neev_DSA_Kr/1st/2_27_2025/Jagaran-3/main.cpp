#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
	int data;
	TreeNode* left,*right;
};

TreeNode* create(void) {
	int k;
	cin>>k;
	if(k==0) return NULL;
	TreeNode* T = new TreeNode{k};

	T->left = create();
	T->right = create();
	return T;
}

void pre(TreeNode* T) {
	if(T) {
		cout<<T->data<<" ";
		pre(T->left);
		pre(T->right);
	}
}

void heapify_BT(TreeNode* T) {
	if(T==NULL) return;
	heapify_BT(T->left);
	if(T->right == NULL || (T->left && T->left->data<T->right->data)){
    	if(T->left && T->data>T->left->data) {
    		swap(T->data,T->left->data);
    		heapify_BT(T->left);
    	}
	}
	else if(T->right && T->data>T->right->data) {
		swap(T->data,T->right->data);
	}
	heapify_BT(T->right);
}

int main() {

	TreeNode* T = create();
	heapify_BT(T);
	pre(T);

	return 0;
}

