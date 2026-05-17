#include <bits/stdc++.h>
using namespace std;
// normal for min heap , normal + x for max heap
void heapifyX(int c, vector<int> &H) {      
    if (c == 0) return;
    if (H[(c - 1) / 2] > H[c]) return;
    swap(H[c], H[(c - 1) / 2]);
    heapifyX((c - 1) / 2, H);
}

void heapify_HelperX(int c, vector<int> &H) {
    if (c >= H.size()) return;
    if (2 * c + 1 >= H.size()) return;
    int i;
    if (2 * c + 2 >= H.size()) i = 2 * c + 1;
    else if (H[2 * c + 1] > H[2 * c + 2]) i = 2 * c + 1;
    else i = 2 * c + 2;
    if (H[i] < H[c]) return;  // c is parent
    swap(H[i], H[c]);
    heapify_HelperX(i, H);
}

void heapify(int c, vector<int> &H) {
    if (c == 0) return;
    if (H[(c - 1) / 2] < H[c]) return;
    swap(H[c], H[(c - 1) / 2]);
    heapify((c - 1) / 2, H);
}

void heapify_Helper(int c, vector<int> &H) {
    if (c >= H.size()) return;
    if (2 * c + 1 >= H.size() && 2 * c + 2 >= H.size()) return;
    int i;
    if (2 * c + 2 >= H.size()) i = 2 * c + 1;
    else if (H[2 * c + 1] < H[2 * c + 2]) i = 2 * c + 1;
    else i = 2 * c + 2;
    if (H[i] > H[c]) return;  // c is parent
    swap(H[i], H[c]);
    heapify_Helper(i, H);
}

void printMedian(vector<int>&H, vector<int>&Hx) {
    if (H.size() > Hx.size() + 1) {
        int mini = H[0];
        H[0] = H.back();
        H.pop_back();
        heapify_Helper(0, H);   // heapify2 min heap after popping 
        Hx.push_back(mini);
        heapifyX(Hx.size() - 1, Hx);    // heapify1 max heap after pushing
    } 
    else if (Hx.size() > H.size() + 1) {
        int maxi = Hx[0];
        Hx[0] = Hx.back();
        Hx.pop_back();
        heapify_HelperX(0, Hx);  // heapify2 max heap after popping 
        H.push_back(maxi);
        heapify(H.size() - 1, H);       // heapify1 min heap after pushing
    }
    // median print
    if (H.size() == Hx.size()) 
        cout << (H[0] + Hx[0])/2 << " ";
    else if (H.size() > Hx.size()) 
        cout << H[0] << " ";
    else 
        cout << Hx[0] << " ";
}

int main() {
    vector<int> Hx, H;
    int k;
    
cin >> k;
    Hx.push_back(k);
    cout << k << " ";
    while (cin >> k && k != -1) {
        if (k > Hx.front()) {
            H.push_back(k);
            heapify(H.size() - 1, H);
            
        } else {
            Hx.push_back(k);
            heapifyX(Hx.size() - 1, Hx);
         
        }
        printMedian(H, Hx);
    }

    return 0;
}