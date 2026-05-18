#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
	int data;
	TreeNode *left;
	TreeNode *right;
};

int height(TreeNode* T) {
	if(T==NULL) return -1;
	return max(height(T->left), height(T->right)) + 1 ;
}

int balance(TreeNode* T) {
	return height(T->left) - height(T->right);
}

TreeNode* rotateR(TreeNode* T) {
	TreeNode* x = T->left;
	T->left = x->right;
	x->right = T;
    return x;
}

TreeNode* rotateL(TreeNode* &T) {
	TreeNode* x = T->right;
	T->right = x->left;
	x->left = T;
	return x;
}
TreeNode* insert(TreeNode* T, int k) {
	if (T==NULL) return	new TreeNode{k,NULL,NULL};
	
	if (k < T->data) T->left = insert(T->left, k);
	else  T->right = insert(T->right, k);

	int b = balance(T);
	if (b > 1 && k < T->left->data) return rotateR(T);  // Rr
	if (b < -1 && k > T->right->data) return rotateL(T);    // Rl
	if (b > 1 && k > T->left->data) {       // Rl Rr
		T->left=rotateL(T->left);
	    return rotateR(T);
	}
	if (b < -1 && k < T->right->data) {     // Rr Lr
		T->right=rotateR(T->right);
		return rotateL(T);
	}
	return T;
}

void print_pre(TreeNode* T) {
	if (T) {
		cout << T->data << " ";
		print_pre(T->left);
		print_pre(T->right);
	}
}

int main() {
	TreeNode* T = NULL;
	int k;
	while (cin >> k && k != -1) {
		T = insert(T, k);       // possiblity of changing root every time
		print_pre(T);
		cout << endl;
	}
	return 0;
}
