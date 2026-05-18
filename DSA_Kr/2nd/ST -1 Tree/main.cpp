#include<bits/stdc++.h>
using namespace std;

struct str {
	int data = 0;
	int l=-1,h=-1;
};


str rfn(vector<str> &s,vector<int> &arr,int l, int h,int i) {
	if(l==h) {
		s[i].data = arr[l];
		s[i].l = s[i].h = l;
		return s[i];
	}
	else {
		str L = rfn(s,arr,l,(l+h)/2,2*i+1);
		str R = rfn(s,arr,(l+h)/2+1,h,2*i+2);
		s[i].data = L.data + R.data;
		s[i].l = (L.l!=-1) ? L.l : R.l;
		s[i].h = (R.h!=-1) ? R.h : L.h;
		return s[i];
	}
}

void update(vector<str> &s,int j,int x) {
	int f = 0;
	for(int i=0; i<s.size(); i++) {
		if(s[i].data!=0 && (s[i].l==s[i].h) && s[i].l==j) {
			f = s[i].data;
			break;
		}
	}
	for(int i=0; i<s.size(); i++) {
		if(s[i].data!=0) 
			if(j>=s[i].l && j<=s[i].h ) s[i].data = s[i].data + (x-f);
	}
}

int rangeSum(vector<str> &s, int l, int h) {
	int sum = 0;

	for(int i=0; i<s.size(); i++) {
		if(s[i].data!=0 && (s[i].l==s[i].h)) 
			if(s[i].h>=l && s[i].h<=h) sum+=s[i].data;
	}

	return sum;
}

int mini(vector<str> &s,int l, int h) {
	int ans = INT_MAX;
	for(int i=0; i<s.size(); i++) {
		if(s[i].data!=0 && (s[i].l==s[i].h)) 
			if(s[i].h>=l && s[i].h<=h) ans = min(ans,s[i].data);
	}
	return ans;
}

int average(vector<str> &s,int l, int h) {
	int ans = 0;
	for(int i=0; i<s.size(); i++) {
		if(s[i].data!=0 && (s[i].l==s[i].h)) 
			if(s[i].h>=l && s[i].h<=h) ans += s[i].data;
	}
	return ans/(h-l+1);
}

int main() {
	int k;
	cin>>k;
	vector<int> arr(k);
	for(int i=0; i<k; i++) {
		int p;
		cin>>p;
		arr[i] = p;
	}

	int siz = 1;
	int a = 1;
	while(a<k) {
		a*=2;
		siz += a;
	}
	vector<str> s(siz);
	rfn(s,arr,0,k-1,0);
	
	cin>>k;
	while(k--) {
		int p,i,x;
		cin>>p>>i>>x;
		if(p==0) update(s,i-1,x);
		else if(p==1) cout<< rangeSum(s,i-1,x-1) << endl;
		else if(p==2) cout << mini(s,i-1,x-1) << endl;
		else cout<<average(s,i-1,x-1)<<endl;
	}
	
	return 0;
}