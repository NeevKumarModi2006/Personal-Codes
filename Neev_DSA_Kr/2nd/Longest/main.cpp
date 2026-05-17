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

int height(TreeNode* T) {
	if(!T) return 0;
	return max(height(T->left),height(T->right)) + 1;
}

void trav(TreeNode* T, TreeNode* &A, int &i) {
	if(T) {
		int h = height(T->left)+height(T->right);
		if(i<h) {
			i=h;
			A=T;
		}
		trav(T->left,A,i);
		trav(T->right,A,i);
	}
}

void travel(TreeNode* T, vector<int> &a, vector<int> b) {
	if(!T) return;
	b.push_back(T->data);
	if(!T->left && !T->right && a.size()<b.size()) {
		a = b;
		return;
	}
	travel(T->left,a,b);
	travel(T->right,a,b);
}

int main() {

	TreeNode* T1 = create();
	TreeNode* T=NULL;
	int i = 0;
	trav(T1,T,i);

	vector<int>arr;
	vector<int>a;
	
	travel(T->left,a,vector<int>());
	reverse(a.begin(),a.end());
	arr.insert(arr.end(),a.begin(),a.end());
	
	a.clear();
	arr.push_back(T->data);
	
	travel(T->right,a,vector<int>());
	arr.insert(arr.end(),a.begin(),a.end());
	a.clear();

	cout<<arr.size()<<endl;     // i+1 
	for(int i : arr) cout<<i<<" ";

	return 0;
}

