// Winners never quit, and quitters never win."

// "An investment in knowledge pays the best interest."
// b An interest in coding gets the best intern b
//                                                  ~ KR
#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
	int data;
	TreeNode* left,*right;
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

TreeNode* create() {
	TreeNode* T = NULL;
	int k;
	while (cin >> k && k != -1) insert(T, k);
	return T;
}

void ino(TreeNode* T) {
	if(T) {
		ino(T->left);
		cout<<T->data<<" ";
		ino(T->right);
	}
}

void pre(TreeNode* T) {
	if(T) {
		cout<<T->data<<" ";
		pre(T->left);
		pre(T->right);
	}
}

void traverse(TreeNode* T1, TreeNode* T2) {
    if(T1==NULL || T2==NULL) return;
	if(T1->data>T2->data) {
		if(T1->left && T1->left->data > T2->data) traverse(T1->left,T2);
		else {
			if(T2->right && T2->right->data < T1->data)  traverse(T1,T2->right);
			else swap(T1->data,T2->data);
		}
	}
	else traverse(T1->right,T2);
}

void travel(TreeNode* T1, TreeNode* T2,TreeNode* prev=NULL) {
	if(T1 && T2) {
	    traverse(T1,T2);
		travel(T1,T2->left,prev);
		if(prev && prev->data>T2->data) swap(T2->data,prev->data);
		prev = T2;
		travel(T1,T2->right,prev);   
	}
}


bool check(TreeNode* T1, TreeNode* T2){
    if(T1==NULL || T2==NULL) return true;
    if(T1->data > T2->data) return false;
    return check(T1->right,T2) && check(T1,T2->left) ; 
}

void traveller(TreeNode* T1, TreeNode* T2){
    while(!check(T1,T2)) travel(T1,T2);
}

int main() {

	TreeNode* T1 = create();
	TreeNode* T2 = create();
	TreeNode* T3 = create();
    
    // int prev = 0;
    traveller(T2, T3);
    traveller(T1, T2);
    traveller(T2, T3);

    pre(T1);  pre(T2); pre(T3); 
   cout<<endl;
	ino(T1); ino(T2); ino(T3);

	return 0;
}