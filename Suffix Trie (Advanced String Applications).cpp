#include <bits/stdc++.h>
using namespace std;

struct trnode {
    trnode* ptr[26];
    bool end = false;

    trnode() {
        for (int i = 0; i < 26; i++) ptr[i] = NULL;
    }
};

// Insert a full word
void insert(trnode* &T, string &s, int i = 0) {
    if (T == NULL) T = new trnode;
    if (i == s.size()) {
        T->end = true;
        return;
    }
    insert(T->ptr[s[i] - 'a'], s, i + 1);
}

// Insert all suffixes
void insertSuffixes(trnode* &T, string &s) {
    for (int i = 0; i < s.size(); i++) {
        string suffix = s.substr(i);
        insert(T, suffix);
    }
}

// Search any substring in O(L)
bool search(trnode* T, string &s, int i = 0) {
    if (!T) return false;
    if (i == s.size()) return true;
    return search(T->ptr[s[i] - 'a'], s, i + 1);
}

int main() {
    string text = "banana";
    trnode* T = NULL;

    insertSuffixes(T, text);

    vector<string> queries = {"ana", "ban", "nana", "nab", "na"};
    for (string q : queries) {
        cout << q << ": " << (search(T, q) ? "YES" : "NO") << "\n";
    }

    return 0;
}
