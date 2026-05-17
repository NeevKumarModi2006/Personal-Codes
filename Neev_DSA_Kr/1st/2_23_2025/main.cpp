#include<bits/stdc++.h>
using namespace std;

struct mnode {
	char data;
	vector<mnode*> mptr;
};
struct TreeNode {
	char data;
	TreeNode* left,*right;
};
mnode* create(char k) {
	mnode* M = new mnode{k};
	while(cin>>k && k!='.') M->mptr.push_back(create(k));
	return M;
}

void insertToMap(mnode* M, unordered_map<mnode*, deque<mnode*>> &D)
{
	if (M==NULL) return;
	deque<mnode*> Q;
	for(auto i : M->mptr) Q.push_back(i);
	D[M] = Q;
	for(auto i : M->mptr) insertToMap(i,D);
}
void pre(TreeNode* T)
{
	if (T) {
		cout << T->data;
		pre(T->left);
		pre(T->right);
	}
	else cout<<".";
}
TreeNode* convert(mnode* M, unordered_map<mnode*, deque<mnode*>> &D) {
	if (!M)  return NULL;

	TreeNode* T = new TreeNode{M->data,NULL, NULL};

	if (!D[M].empty())
	{
		mnode* P = D[M].front();
		D[M].pop_front();
		T->left = convert(P, D);

		if (!D[M].empty())
		{
			mnode* X = D[M].front();
			D[M].pop_front();
			T->right = convert(X, D);

			if (!D[X].empty())  D[M].push_front(X);
		}
		if (!D[P].empty())  D[M].push_front(P);
	}
	return T;
}

int main() {
	char k;
	cin>>k;
	mnode* M = create(k);
	unordered_map<mnode*, deque<mnode*>> D;        // list is also okay
	insertToMap(M,D);

	while(!D[M].empty()) {
		TreeNode* T = convert(M,D);
		pre(T);
		cout<<endl;
	}

	return 0;
}
