#include<bits/stdc++.h>
using namespace std;

struct mnode {
	char data;
	vector<mnode*> mptr;
};

mnode* create(char k) {
	mnode* M = new mnode;
	M->data = k;
	while(cin>>k && k!='.') {
		mnode* T = create(k);
		M->mptr.push_back(T);
	}
	return M;
}

void level(queue<mnode *> &Q, int cnt) {
	if (Q.empty()) return;
	if (cnt == 0) cnt = Q.size();

	mnode *T = Q.front();
	Q.pop();

	cout<<T->data<<" ";
	if (cnt==1) cout << "*\n";

	for (int i = 0; i < T->mptr.size(); i++) {
		if (T->mptr[i] != NULL)
			Q.push(T->mptr[i]);
	}
	level(Q, cnt-1);
}

int main() {
	char k;
	cin>>k;
	mnode* M = create(k);
	queue<mnode*> Q;
	Q.push(M);
	level(Q,0);


	return 0;
}