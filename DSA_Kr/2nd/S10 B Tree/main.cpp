#include <bits/stdc++.h>
using namespace std;

struct bnode {
	int count = 0;
	vector<int> keys;
	vector<bnode*> ptr;
	bnode* p = NULL;
    bnode* ll = NULL;
    bnode* rr = NULL;
};

bnode* find(bnode* B, int k) {
	if (B == NULL) {
		cout<<"no\n";
		return B;
	}
	
	for (int i = 0; i < B->count; i++) 
		if (k < B->keys[i]) 
			return B->ptr[i] != NULL ? find(B->ptr[i], k) : B;
		
	return B->ptr[B->count]!=NULL ? find(B->ptr[B->count],k) : B;
}

static bool comp(bnode* A, bnode* B) {
	if(B==NULL) return true;
	if(A==NULL) return false;
	return A->keys[0]<B->keys[0];
}

bnode* overflow(bnode* B,bnode* N, int k, int d) {

	vector<int> Q(B->keys.begin(),B->keys.begin()+2*d); // B->count+1 = 2*d+1
	Q.push_back(k);
	sort(Q.begin(), Q.end());
	B->keys.clear();
	B->keys.insert(B->keys.begin(), Q.begin(), Q.begin()+d); // 0 to d

	bnode* B2 = new bnode;
	B2->keys.insert(B2->keys.begin(), Q.begin()+d+1, Q.end());
	B->count=B2->count=d;

	if(N!=NULL) {
	    vector<bnode*> X (B->ptr.begin(),B->ptr.begin()+2*d+1);     // 2d+1
		X.push_back(N);
		sort(X.begin(),X.end(),comp);   
		B->ptr.clear();
		B->ptr.insert(B->ptr.begin(),X.begin(), X.begin()+d+1);
		B2->ptr.insert(B2->ptr.begin(),X.begin()+d+1, X.end());
		for(int i=0;i<B->ptr.size();i++){       
		    B->ptr[i]->p = B;
		    B2->ptr[i]->p = B2;
		}
	}
	else {
		B->ptr.resize(d+1,NULL);
		B2->ptr.resize(d+1,NULL);
	}

	k = Q[d];
	bnode* P = B->p;
	if (P==NULL) {
		P = new bnode;
		P->keys.push_back(k);
		P->ptr.push_back(B);
		P->ptr.push_back(B2);
		P->count++;
		B->p = P;
		B2->p = P;
		return P;
	}
	else {
		if (P->count >= 2*d) return overflow(P,B2,k,d);
		else {
		    P->count++;
         P->keys.push_back(k);
         P->ptr.push_back(B2);
         sort(P->keys.begin(),P->keys.begin()+P->count);
         sort(P->ptr.begin(),P->ptr.begin()+P->count+1,comp);
        B2->p = P;
         while(P->p) P = P->p;
		 return P;
		}
	}
}


bnode* add(bnode* &B, int k, int d) {
	if (B == NULL) {
		B = new bnode;
		B->keys.push_back(k);
		B->count++;
		B->ptr.resize(2,NULL);
		return B;
	}
	bnode* B1 = find(B, k);
	if (B1->count == 2*d) {
		return overflow(B1,NULL, k, d);  // leaf
	} else {
		B1->keys.push_back(k);      // B1 is leaf
		sort(B1->keys.begin(), B1->keys.end());
		B1->count++;
		B1->ptr.push_back(NULL);
	}
	return B;
}

void ino(bnode* B) {
	if (B == NULL) return;
	for (int i = 0; i < B->keys.size(); i++) {
		if (B->ptr.size() > i) ino(B->ptr[i]);
		cout << B->keys[i] << " ";
	}
	if (B->ptr.size() > B->keys.size()) ino(B->ptr[B->keys.size()]);
}

void level(queue<bnode*> &Q, int cnt,bnode* prev) {
	if (Q.empty()) return;
	if (cnt == 0) cnt = Q.size();

	bnode *T = Q.front();
	Q.pop();
	
	for (int i = 0; i < T->count; i++) cout << T->keys[i] << " ";
	cout<<"  ";
	if (cnt==1) cout << "\n";
    bool k = true;
	for (int i = 0; i <= T->count; i++)
		if (T->ptr[i] != NULL){
		    k = false;
		    Q.push(T->ptr[i]);
		}
    if(prev!=NULL){
        T->ll = prev;
        prev->rr = T;
    }
	level(Q, cnt-1,k?T:NULL);

}

void print(bnode* B){
    bnode* B1 = B, *B2 = B;
    while(B1->ptr[0]) B1 = B1->ptr[0];
    while(B2->ptr[B2->ptr.size()-1]) B2 = B2->ptr[B2->ptr.size()-1];
    
    while(B1){
        for(int i : B1->keys) cout<<i<<" ";
        B1 = B1->rr;
    }
    cout<<endl;
    while(B2){
        for(int i = B2->keys.size()-1; i>=0 ;i--) cout<<B2->keys[i]<<" ";
        B2 = B2->ll;
    }
    
}

int main() {
	int d = 3;
	d = (d-1)/2;
	int k;
	bnode* B = NULL;

	while (cin >> k && k != 0) {
		B = add(B, k, d);
	}


	queue<bnode*> Q;
	Q.push(B);
	level(Q,0,NULL);
    
    print(B);
    
    
	return 0;
}
// 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 16 17 18 0