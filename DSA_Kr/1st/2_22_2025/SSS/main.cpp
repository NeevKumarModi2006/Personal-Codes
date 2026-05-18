#include<bits/stdc++.h>
using namespace std;

struct mnode {
	char data;
	vector<mnode*> mptr;
};

void create(queue<mnode**> &Q) {
	if (Q.empty()) return;
	mnode* &T = *Q.front();
	Q.pop();
	char k;
	int p;
	cin>>k>>p;
	T= new mnode{k};
	
	if(p>0) T->mptr.resize(p,NULL);
	for (int i = 0; i < p; i++) 
		Q.push(&T->mptr[i]);

	create(Q);
}

void level(queue<mnode *> &Q, int cnt=0) {
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

	mnode* M = NULL;
	queue<mnode**>Q;
	Q.push(&M);
	create(Q);

	DFT(M);
	cout<<".";

	return 0;
}