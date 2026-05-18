#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
	int data;
	TreeNode* left,*right;
};

void insert(TreeNode* &T, int k) {
	if (!T) {
		T = new TreeNode{k,NULL,NULL};;
		return;
	}
	(k < T->data) ? insert(T->left, k) : insert(T->right, k);
}

TreeNode* create() {
	TreeNode* T = NULL;
	int k;
	while (cin >> k && k != -1) insert(T, k);
	return T;
}

void saturate(TreeNode* &T, int mini,int maxi) {
if(maxi-mini<2) return;
if(T==NULL) T = new TreeNode{(mini+maxi)/2,NULL,NULL};
saturate(T->left,mini,T->data-1);
saturate(T->right,T->data+1,maxi);
}

int depth(TreeNode* T) {
	if(T==NULL) return -1;
	return max(depth(T->left), depth(T->right)) + 1;
}

void pre(TreeNode * T) {
	if(T) {
		cout<<T->data<<" ";
		pre(T->left);
		pre(T->right);
	}
}

int main() {
	TreeNode* T = create();
	saturate(T,0,90);
	pre(T);
	return 0;
}