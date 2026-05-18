#include <bits/stdc++.h>
using namespace std;

void heapify(int c, vector<int> &H) {
	if(c==0) return;
	if(H[(c-1)/2]>H[c]) return;
	swap(H[c],H[(c-1)/2]);
	heapify((c-1)/2,H);
}

void heapify_Helper(int c, vector<int> &H,int size) {
	if(c>=size) return;
	if(2*c+1>=size) return;
	int i;
    if(2*c+2>=size) i = 2*c+1;
    else if(H[2*c+1]>H[2*c+2]) i=2*c+1;
    else i = 2*c+2;
	if(H[i]<H[c]) return;       // c is parent
	swap(H[i],H[c]);
	heapify_Helper(i,H,size);
}

void heapSort_Modified(vector<int> H,int i) {     // making empty or not depends on &
int j=4;
	while(true) {
		    int x = H[i-1];
		    	        H[j++]=H[0];
		    i--;
            if(i==0) break;
		    H[0]=x;
		    heapify_Helper(0,H,i);
		    		    
	}
for(int j=8;j>=4;j--) cout<<H[j]<<" ";
}

int main() {
	vector<int>H(9);
	int i = 0;
	int k;
	while(cin>>k && k!=-1) {
		H[i++] = k;
		heapify(i-1,H);
		if(i>5){
		    int x = H[i-1];
		    i--;
		    H[0]=x;
		    heapify_Helper(0,H,i);
		}
	}

    heapSort_Modified(H,i);

	return 0;
}