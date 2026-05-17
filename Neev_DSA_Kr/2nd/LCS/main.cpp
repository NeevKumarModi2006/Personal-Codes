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

int ans = 0;

bool check(TreeNode* T1, TreeNode* T2,int &i) {
    if (!T1 && !T2) return true;
    if (!T1 || !T2) return false;
    i++;
    return (check(T1->left, T2->left,i) && check(T1->right, T2->right,i));
}
void LCS(TreeNode* T1,  TreeNode* T2){
    if(!T1 || !T2) return;
    
    int i = 0;
      if (check(T1, T2,i)) 
        ans = max(ans, i); 
    
    LCS(T1,T2->left);
    LCS(T1,T2->right);
    LCS(T1->left,T2);
    LCS(T1->right,T2);

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
    LCS(T1,T2);
	cout<<ans;


	return 0;
}