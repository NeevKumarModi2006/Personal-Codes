#include <bits/stdc++.h>       
using namespace std;

void merge(vector<int>& arr, int l, int mid, int r) {
    vector<int> L(arr.begin() + l, arr.begin() + mid + 1);
    vector<int> R(arr.begin() + mid + 1, arr.begin() + r + 1);
    int i = 0, j = 0, k = l;
    while (i < L.size() && j < R.size()) 
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < L.size()) arr[k++] = L[i++];
    while (j < R.size()) arr[k++] = R[j++];
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int mid = l + (r - l) / 2;
        mergeSort(arr, l, mid);
        mergeSort(arr, mid + 1, r);
        merge(arr, l, mid, r);
    }
}
void bucketSort(vector<int>& arr) {
    
    int maxi = *max_element(arr.begin(), arr.end());
    int mini = *min_element(arr.begin(), arr.end());
    int cnt =   4;

    vector<vector<int>> buckets(cnt);

    for (int i = 0; i < arr.size(); ++i) {
        int ind = ((arr[i] - mini) / (maxi - mini) * (cnt - 1));
        buckets[ind].push_back(arr[i]);
    }
    
    arr.clear();
    for (int i = 0; i < cnt; ++i) {
        sort(buckets[i].begin(), buckets[i].end());
        arr.insert(arr.end(), buckets[i].begin(), buckets[i].end());
    }
}

void mway(vector<int> arr){
    mergeSort(arr,0,4);
    mergeSort(arr,5,8);
    mergeSort(arr,9,17);
    mergeSort(arr,18,22);
for(auto i : arr) cout<<i<<" ";     cout<<endl;
    bucketSort(arr);
for(auto i : arr) cout<<i<<" ";
}

int main() {

	vector<int>arr(23);
	for(int i=0; i<23; i++) {
		int p ;
		cin>>p;
		arr[i]=p;
	}
	swap(arr[17],arr[18]);
    mway(arr);

	return 0;
}