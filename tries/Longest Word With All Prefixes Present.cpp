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

string longest = "";

void dfs(trnode* T, string cur) {
    if (!T) return;
    if (T->eow == 0 && cur != "") return;

    if (cur.size() > longest.size()) longest = cur;

    for (int i = 0; i < 26; i++) {
        if (T->ptr[i]) {
            dfs(T->ptr[i], cur + char(i + 'a'));
        }
    }
}

int main() {
    trnode* T = NULL;
    string s;

    while (cin >> s && s != "#") create(T, s);

    dfs(T, "");
    if (longest != "")
        cout << "Longest word with all prefixes present: " << longest << "\n";
    else
        cout << "No such word found.\n";

    return 0;
}
