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

void traverse(TreeNode* T, TreeNode* T1, string s) {
	if (T == NULL) return;
	s += to_string(T->data) + " ";

	if (T1 == NULL && T->left == NULL && T->right == NULL) 	cout << s << endl;         // child print
	
	TreeNode* Q=NULL,*P=NULL;
	if(T1) {
		P=T1;
		Q=T1;
	}
	else {
		P=T->right;
		Q=T->left;
	}
	traverse(T->left, P, s);
	traverse(T->right, Q, s);
	if(T->right)  traverse(T1, T->right, s);
	else traverse(T1,T->left,s);
}


int main() {
	TreeNode* T = NULL;
	int k;
	while (cin >> k && k != -1) insert(T, k);

	traverse(T,NULL,"");

	return 0;
}

// 9 5 15 7 12 -1