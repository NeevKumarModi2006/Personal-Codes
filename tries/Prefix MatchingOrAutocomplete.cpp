#include <bits/stdc++.h>
using namespace std;

struct trnode {
    int eow = 0;
    trnode* ptr[26];

    trnode() {
        for (int i = 0; i < 26; i++) ptr[i] = NULL;
    }
};

void create(trnode* &T, string &s, int i = 0) {
    if (T == NULL) T = new trnode;
    if (i == s.size()) {
        T->eow = 1;
        return;
    }
    create(T->ptr[s[i] - 'a'], s, i + 1);
}

void print(trnode* T, string s = "") {
    if (!T) return;
    if (T->eow == 1) cout << s << "\n";
    for (int i = 0; i < 26; i++)
        if (T->ptr[i])
            print(T->ptr[i], s + char(i + 'a'));
}

bool search(trnode* T, string &s, int i = 0) {
    if (!T) return false;
    if (i == s.size()) return T->eow == 1;
    return search(T->ptr[s[i] - 'a'], s, i + 1);
}

// Go to the node of the last letter of prefix
trnode* find(trnode* T, string &s, int i = 0) {
    if (!T) return NULL;
    if (i == s.size()) return T;
    return find(T->ptr[s[i] - 'a'], s, i + 1);
}

void autocomplete(trnode* T, string prefix) {
    trnode* node = find(T, prefix);
    if (!node) {
        cout << "No suggestions\n";
        return;
    }
    print(node, prefix);
}

int main() {
    trnode* T = NULL;
    string s;

    // Insert words
    while (cin >> s && s != "#") create(T, s);

    cout << "\nWords in Trie:\n";
    print(T);

    cout << "\nSearch suggestions:\n";
    vector<string> queries = {"a", "ap", "b", "bat", "c"};

    for (string q : queries) {
        cout << "Suggestions for \"" << q << "\":\n";
        autocomplete(T, q);
        cout << "---\n";
    }

    return 0;
}
