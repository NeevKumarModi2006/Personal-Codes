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

void deleteT2(vector<int>&arr,TreeNode* &P, TreeNode* T) {
	if(!T)  return;
	if(!T->left && !T->right) {
		arr.push_back(T->data);
		(P->left==T) ? P->left=NULL : P->right=NULL; 
		delete T;
		return;
	}
	deleteT2(arr,T,T->left);
	deleteT2(arr,T,T->right);
}

void add(vector<int>&arr,TreeNode* &T, int &i){
    if(!T) return;
    if(i>=arr.size()) return;
    add(arr,T->left,i);
    add(arr,T->right,i);

    if(T->right==NULL && T->left!=NULL) T->right = new TreeNode{arr[i++],NULL,NULL};
    else if(T->left==NULL && T->right!=NULL) T->left = new TreeNode{arr[i++],NULL,NULL};
    
}

void pre(TreeNode* T) {
	if(T) {
		cout<<T->data<<" ";
		pre(T->left);
		pre(T->right);
	}
}


int main() {

	TreeNode* T1 = create();
	TreeNode* T2 = create();
	vector<int>arr;
	deleteT2(arr, T2, T2);
	int i=0;
	add(arr,T1,i);
    pre(T1); cout<<endl;
    pre(T2);

	return 0;
}
