// Person value is know when you loose
// Time value is know wen you  passes it
// Life value is know when you experience it.
// Program value is know when you encounter during OT
#include <bits/stdc++.h>
using namespace std;

void heapify(int c, vector<int> &H) {
	if(c==0) return;
	if(H[(c-1)/2]<H[c]) return;
	swap(H[c],H[(c-1)/2]);
	heapify((c-1)/2,H);
}
void level(vector<int> &H, int i, int j) {
	if(i==H.size()) return;
	if(i==pow(2,j)-1) {
		cout<<endl;
		j++;
	}
	cout<<H[i]<<" ";
	level(H,i+1,j);
}

void heapify_Helper(int c, vector<int> &H) {
	if(c>=H.size()) return;
	if(2*c+1>=H.size() && 2*c+2>=H.size()) return;
	int i;
    if(2*c+2>=H.size()) i = 2*c+1;
    else if(H[2*c+1]<H[2*c+2]) i=2*c+1;
    else i = 2*c+2;
	if(H[i]>H[c]) return;       // c is parent
	swap(H[i],H[c]);
	heapify_Helper(i,H);
}

void heapSort(vector<int> &H) {     // making empty or not depends on &
	while(true) {
		int x = H.back();
		H.pop_back();
		if(!H.empty())  cout<<H[0]<<" ";
		else {
			cout<<x;
			break;
		}
		H[0]=x;
		heapify_Helper(0,H);
	}
	cout<<endl;
}
bool check(vector<int>& H, int c){
	if(c>=H.size()) return true;
	if(2*c+1>=H.size() && 2*c+2>=H.size()) return true;
    if(2*c+2>=H.size()) return H[c]<H[2*c+1];
    return (H[c]<H[2*c+1] && H[c]<H[2*c+2] && check(H, c+1));
}
int main() {
	vector<int>H;
	int k;
	while(cin>>k && k!=-1) {
		H.push_back(k);
		heapify(H.size()-1,H);
	}
	heapSort(H);
	while(cin>>k && k!=-1) {
		H.push_back(k);

	}
    cout<<check(H,0);

	return 0;
}