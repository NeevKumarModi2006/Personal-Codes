#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
	int data;
	TreeNode *left, *right;
};

TreeNode* create(void) {
	int k;
	cin>>k;
	if(k==0) return NULL;
	TreeNode* T = new TreeNode{k,create(),create()};
	return T;
}

void pre(TreeNode* T) {
	if(T) {
		cout<<T->data<<" ";
		pre(T->left);
		pre(T->right);
	}
}

void LORE(TreeNode* T, stack<TreeNode*> &A, stack<TreeNode*> &B,int k) {
	if(!T) return;
	if(k==3) {
		LORE(T->left,A,B,1);
			    LORE(T->right,A,B,0);
	}
	else {
		if(k==1 && k!=T->data%2) A.push(T);     // 1 != 0       // left side's even
		else if(k==0 && k!=T->data%2) B.push(T);     // 0 != 1       // right side's odd
		LORE(T->left,A,B,k);
		LORE(T->right,A,B,k);
	}
}

int main() {
	TreeNode* T = create();
	stack<TreeNode*> A,B;
	LORE(T,A,B,3);
    while(!A.empty() || !B.empty()){        // A.size()==B.size() 
        swap(A.top()->data,B.top()->data);
        A.pop();
        B.pop();
    }
	
	pre(T);

	return 0;
}