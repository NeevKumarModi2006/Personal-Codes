#include <bits/stdc++.h>
using namespace std;

struct trnode {
    trnode* ptr[2]; // Only 0 and 1 needed for binary

    trnode() {
        ptr[0] = ptr[1] = NULL;
    }
};

void insert(trnode* &T, int num) {
    if (T == NULL) T = new trnode;
    trnode* temp = T;
    for (int i = 30; i >= 0; i--) {
        int bit = (num >> i) & 1;
        if (temp->ptr[bit] == NULL)
            temp->ptr[bit] = new trnode;
        temp = temp->ptr[bit];
    }
}

int findMaxXOR(trnode* T, int num) {
    trnode* temp = T;
    int ans = 0;
    for (int i = 30; i >= 0; i--) {
        int bit = (num >> i) & 1;
        int opp = 1 - bit;
        if (temp->ptr[opp]) {
            ans |= (1 << i);
            temp = temp->ptr[opp];
        } else {
            temp = temp->ptr[bit];
        }
    }
    return ans;
}

int main() {
    trnode* T = NULL;
    vector<int> a = {3, 10, 5, 25, 2, 8};

    for (int x : a)
        insert(T, x);

    int maxXOR = 0;
    for (int x : a)
        maxXOR = max(maxXOR, findMaxXOR(T, x));

    cout << "Maximum XOR of two numbers: " << maxXOR << "\n";
    return 0;
}
