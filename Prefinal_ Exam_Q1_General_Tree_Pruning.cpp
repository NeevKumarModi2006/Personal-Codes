#include <bits/stdc++.h>
using namespace std;

struct mnode {
	int data;
	vector<mnode*> mptr;
};

// Create general tree from vector
mnode* create(int k, vector<int> &v, int &i) {
	mnode* M = new mnode{k};
	while (v[i++] != 0) 
		M->mptr.push_back(create(v[i-1], v, i));
	return M;
}

// Print remaining general tree in level-order
void level(queue<mnode *> &Q, int cnt) {
	if (Q.empty()) return;
	if (cnt == 0) cnt = Q.size();

	mnode *T = Q.front();
	Q.pop();

	cout << T->data << " ";
	if (cnt == 1) cout << "\n";

	for (int i = 0; i < T->mptr.size(); i++) {
		if (T->mptr[i] != NULL)
			Q.push(T->mptr[i]);
	}
	level(Q, cnt - 1);
}

// Height function (used in heap check)
int height(mnode* M) {
	if (M->mptr.empty()) return 0;
	int h = 0;
	for (auto c : M->mptr) {
		h = max(h, height(c));
	}
	return h + 1;
}

// Check if a subtree is a Binary Search Tree
bool checkbst(mnode* M) {
	if (M->mptr.size() > 2) return false;
	if (M->mptr.size() == 0) return true;
	if (M->mptr.size() == 1) 
		return (M->mptr[0]->data < M->data && checkbst(M->mptr[0]));
	else 
		return (M->mptr[0]->data < M->data && M->mptr[1]->data > M->data &&
		        checkbst(M->mptr[0]) && checkbst(M->mptr[1]));
}

// Check if a subtree is a Min-Heap
bool checkheap(mnode* M) {
	if (M->mptr.size() > 2) return false;
	if (M->mptr.size() == 0) return true;
	if (M->mptr.size() == 1)
		return (M->mptr[0]->data > M->data && checkheap(M->mptr[0]));
	else {
		if (!(M->mptr[0]->data > M->data && M->mptr[1]->data > M->data))
			return false;
		if (height(M->mptr[0]) != height(M->mptr[1])) return false;
		return checkheap(M->mptr[0]) && checkheap(M->mptr[1]);
	}
}

// Store result as: level ? list of (type, value)
vector<vector<pair<string, int>>> result(100);

// DFS traversal to find and remove BST/Heap subtrees
void DFT(mnode* M, int level) {
	if (!M) return;
	for (int i = 0; i < M->mptr.size(); i++) {
		if (M->mptr[i]) {
			if (!M->mptr[i]->mptr.empty() && checkbst(M->mptr[i])) {
				result[level].push_back({"BST", M->mptr[i]->data});
				M->mptr[i] = NULL;
			} else if (!M->mptr[i]->mptr.empty() && checkheap(M->mptr[i])) {
				result[level].push_back({"Heap", M->mptr[i]->data});
				M->mptr[i] = NULL;
			} else {
				DFT(M->mptr[i], level + 1);
			}
		}
	}
}

int main() {
	// Tree Input
	vector<int> v = {
		9, 7, 2, 3, 0, 0, 5, 0, 3, 5, 10, 0, 8, 0, 0, 7, 9, 0, 0, 0, 0,
		18, 45, 0, 10, 6, 4, 0, 8, 7, 0, 0, 0, 0, 63, 27, 0, 0, 0,
		5, 4, 2, 1, 0, 3, 0, 0, 0, 8, 6, 0, 0, 0,
		2, 7, 0, 4, 1, 36, 0, 15, 72, 0, 0, 0, 0, 8, 0, 0, 0
	};

	int i = 0;
	mnode* M = create(v[i++], v, i);

	// Process tree to remove BSTs and Heaps
	DFT(M, 1);

	// Print grouped BST/Heap roots by level
	for (int lvl = 1; lvl < result.size(); lvl++) {
		if (!result[lvl].empty()) {
			cout << lvl << " ";
			for (auto &p : result[lvl])
				cout << p.first << " " << p.second << " ";
			cout << endl;
		}
	}

	// Print remaining general tree
	queue<mnode*> Q;
	Q.push(M);
	level(Q, 0);

	return 0;
}

