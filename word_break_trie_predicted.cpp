#include <bits/stdc++.h>
using namespace std;

struct trnode {
    int eow = 0;
    trnode* ptr[26] = {NULL};
};

void create(trnode* &T, string &s, int i=0) {
    if (T == NULL) T = new trnode;
    if (i == s.size()) {
        T->eow = 1;
        return;
    }
    create(T->ptr[s[i] - 'a'], s, i + 1);
}

bool find(trnode* T, string &s, int i = 0) {
    if (!T) return false;
    if (i == s.size()) return T->eow;
    return find(T->ptr[s[i] - 'a'], s, i + 1);
}

// Memoization cache
unordered_map<string, vector<string>> mp;

vector<string> wordBreak2(trnode* T, string s) {
    if (mp.find(s) != mp.end()) return mp[s];
    vector<string> res;

    for (int i = 1; i <= s.size(); i++) {
        string before = s.substr(0, i);       // Prefix
        string after = s.substr(i);           // Remaining

        if (find(T, before)) {
            if (after.empty()) res.push_back(before);
            else {
                vector<string> suffixes = wordBreak2(T, after);
                for (string &w : suffixes)
                    res.push_back(before + " " + w);
            }
        }
    }
    return mp[s] = res;
}

int main() {
    trnode* T = NULL;
    string s;

    while (cin >> s && s != "#") create(T, s);
    cin >> s;

    vector<string> ans = wordBreak2(T, s);
    for (string &x : ans) cout << x << endl;

    return 0;
}
