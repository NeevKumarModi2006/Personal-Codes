#include<bits/stdc++.h>
using namespace std;

inline int radixOf(int k) {
	return to_string(k).size();
}
void print(vector<int>&a){
    for(int i: a) cout<<i<<" ";
    cout<<endl;
}
void countSort(vector<int> &A,int r) {
	int q = pow(10,r);
	int m  = 10;
	vector<int> cnt (m);
	for(int i : A) {
		int k = (i/q) % 10;
		cnt[k]++;
	}
	for(int i = 1; i<m; i++)  cnt[i] += cnt[i-1];
	vector<int> O (A.size(),0);
	for(int i = A.size()-1; i >= 0; i--) {
		int k = (A[i] / q) % 10;
		O[--cnt[k]] = A[i];
	}
	A = O;
}

void radixSort(vector<int> &A,int r) {
	for(int i=0; i<r; i++) countSort(A,i);
}

int main() {

	int k;
	cin>>k;
	vector<int> A(k);
	int r=0,i=0;
	
	while(cin>>k && k!=-1) {
		A[i++] = k;
		r = max(r,radixOf(k));
	}
	radixSort(A,r);
	for(int i : A) cout<<i<<" ";

	return 0;
}