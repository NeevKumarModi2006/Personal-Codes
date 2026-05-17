#include<bits/stdc++.h>
using namespace std;

struct mnode {
	char data;
	vector<mnode*> mptr;
};

mnode* create(char k) {
	mnode* M = new mnode;
	M->data = k;
	int p;
	cin>>p;
	if(p>0) {
		M->mptr.resize(p,NULL);
		for(int i=0; i<p; i++) {
			cin>>k;
			mnode* T = create(k);
			M->mptr[i] = T;
		}
	}
	return M;
}

void level(queue<mnode *> &Q, int cnt) {
	if (Q.empty()) return;
	if (cnt == 0) cnt = Q.size();

	mnode *T = Q.front();
	Q.pop();

	cout<<T->data<<" ";
	if (cnt==1) cout << "/\n";

	for (int i = 0; i < T->mptr.size(); i++) {
		if (T->mptr[i] != NULL)
			Q.push(T->mptr[i]);
	}
	level(Q, cnt-1);
}

void DFT(mnode* M) {
	if(M) {
		cout<<M->data;
		for(int i=0; i<M->mptr.size(); i++) {
			DFT(M->mptr[i]);
		}
		cout<<".";
	}
}


int main() {
	char k;
	cin>>k;
	mnode* M = create(k);
	DFT(M);
    cout<<".";
	return 0;
}