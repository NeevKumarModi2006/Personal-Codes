#include <bits/stdc++.h>
using namespace std;

struct trnode {
    trnode* ptr[26];

    trnode() {
        for (int i = 0; i < 26; i++) ptr[i] = NULL;
    }
};

int insert(trnode* &T, string &s, int i = 0) {
    if (T == NULL) {
        T = new trnode;
        return 1;
    }
    if (i == s.size()) return 0;
    return insert(T->ptr[s[i] - 'a'], s, i + 1);
}

int countDistinctSubstrings(string s) {
    trnode* T = NULL;
    int total = 0;

    for (int i = 0; i < s.size(); i++) {
        string suffix = s.substr(i);
        total += insert(T, suffix); // insert suffix and count new nodes
    }

    return total;
}

int main() {
    string s;
    cin >> s;

    int result = countDistinctSubstrings(s);
    cout << "Total distinct substrings: " << result << "\n";

    return 0;
}
