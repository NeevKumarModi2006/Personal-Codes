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

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void dfs(vector<vector<char>> &board, int i, int j, trnode* T, string path, set<string> &found) {
    char ch = board[i][j];
    if (ch == '#' || T->ptr[ch - 'a'] == NULL) return;

    T = T->ptr[ch - 'a'];
    path += ch;

    if (T->eow) {
        found.insert(path);
        T->eow = 0; // avoid duplicate insertions
    }

    board[i][j] = '#'; // mark visited

    for (int k = 0; k < 4; k++) {
        int ni = i + dx[k], nj = j + dy[k];
        if (ni >= 0 && nj >= 0 && ni < board.size() && nj < board[0].size())
            dfs(board, ni, nj, T, path, found);
    }

    board[i][j] = ch; // restore
}

int main() {
    vector<vector<char>> board = {
        {'o','a','a','n'},
        {'e','t','a','e'},
        {'i','h','k','r'},
        {'i','f','l','v'}
    };

    vector<string> words = {"oath","pea","eat","rain"};

    trnode* T = NULL;
    for (string &w : words) create(T, w);

    set<string> found;

    for (int i = 0; i < board.size(); i++)
        for (int j = 0; j < board[0].size(); j++)
            dfs(board, i, j, T, "", found);

    cout << "Words Found:\n";
    for (string w : found) cout << w << "\n";

    return 0;
}
