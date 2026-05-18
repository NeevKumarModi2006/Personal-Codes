#include<bits/stdc++.h>
using namespace std;

int rfn(vector<int> &s,vector<int> &arr,int l, int h,int i) {
	if(l==h) return s[i] = arr[l];
	else return s[i] = rfn(s,arr,l,(l+h)/2,2*i+1) + rfn(s,arr,(l+h)/2+1,h,2*i+2);
}

int rangeSum(vector<int> &s, int l, int h, int ll, int hh, int i) {
	if (ll <= l && hh >= h) return s[i];        // total overlap
	if (h < ll || l > hh) return 0;                 // No Overlap
	return rangeSum(s, l, (l+h)/2, ll, hh, 2*i+1) + rangeSum(s, (l+h)/2+1, h, ll, hh, 2*i+2);      // partial overlapd
}   

void updateInSegTree(vector<int> &s, int l,int r, int pos, int diff, int si){
    if(l>pos || r<pos) return;  // no overlap
    s[si] += diff;
    if(l!=r){
        int mid = (l+r)/2;
        updateInSegTree(s,l,mid,pos,diff,2*si+1);
        updateInSegTree(s,mid+1,r,pos,diff,2*si+2);
    }
}

int main() {
	int k;
	vector<int>arr;
	while(cin>>k && k!=-1) arr.push_back(k);
	
	int siz = 1;
	int a = 1;
	while(a<arr.size()) {
		a*=2;
		siz += a;
	}
	vector<int> s(siz+1,0);
	rfn(s,arr,0,arr.size()-1,0);

	for(int i=0; i<s.size(); i++) cout<<s[i]<<" ";
	cout<<endl;
// 	int ll,rr;
	
// 	while(cin>>ll>>rr && ll!=-1) cout<<rangeSum(s,0,arr.size()-1,ll,rr,0)<<endl;
	
	
	// update main array, from there you can find difference = new - old; 
// 	// Or directly use range sum for given index to given index 
// 	// we want to update index i=3 from 2 to x=8 
	int i = 3, x = 8;
	int R = rangeSum(s,0,arr.size()-1,i,i,0);
	cout<<R<<endl;
	updateInSegTree(s,0,arr.size()-1, i, x-R, 0);
		for(int i=0; i<s.size(); i++) cout<<s[i]<<" ";
		
		

	return 0;
}
