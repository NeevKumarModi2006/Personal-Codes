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
	return new TreeNode{k,create(),create()};
}

vector<int> getIt(TreeNode* T1) {
	queue<TreeNode*>Q ;
	Q.push(T1);
	vector<int>arr;

	while(!Q.empty()) {
    TreeNode* T = Q.front(); Q.pop();
	if(!T->left && !T->right)	arr.push_back(T->data);
		if(T->left) Q.push(T->left);
		if(T->right) Q.push(T->right);
	}
	return arr;
}

int main() {
	TreeNode* T1 = create();
	TreeNode* T2 = create();

    vector<int>  A = getIt(T1), B = getIt(T2);
    sort(A.begin(),A.end());
    sort(B.begin(),B.end());
    cout << ((A==B) ? "YES" : "NO" );
    
	return 0;
}