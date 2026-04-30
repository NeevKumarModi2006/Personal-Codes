/**
 * B-Tree Implementation
 *
 * Supports insertion, deletion, and traversal.
 * Order is supplied at runtime as the first input (internally halved to get d).
 *
 * Input format:
 *   <order>
 *   <key1> <key2> ... -1      (insert keys; -1 terminates)
 *
 * Example:
 *   3  4 8 45 10 6 5 18 7 9 36 1 3 -1
 * 
 * This work was done in May-June 2025
 */

#include <bits/stdc++.h>
using namespace std;

// ---------------------------------------------------------------------------
// Data structure
// ---------------------------------------------------------------------------

struct BNode {
    int            count = 0;
    vector<int>    keys;
    vector<BNode*> ptr;
    BNode*         parent = nullptr;
};

// ---------------------------------------------------------------------------
// Forward declarations
// ---------------------------------------------------------------------------

BNode* findLeaf(BNode* node, int key);
BNode* overflow(BNode* node, BNode* newChild, int key, int d);
BNode* add(BNode*& root, int key, int d);
void   inorder(BNode* node);
void   levelOrder(queue<BNode*>& q, int cnt);

BNode* del(BNode*& root, int key, int d);
pair<BNode*, int> findKey(BNode* node, int key);
pair<BNode*, int> checkRight(BNode* node, int d);
pair<BNode*, int> checkLeft(BNode* node, int d);
BNode* underFlow(BNode*& node, int d);
int    getInorderPredecessor(BNode* node, int d);
int    getInorderSuccessor(BNode* node, int d);
BNode* getInorderPredecessorNode(BNode* node, int d);
BNode* getInorderSuccessorNode(BNode* node, int d);

// ---------------------------------------------------------------------------
// Search helpers
// ---------------------------------------------------------------------------

BNode* findLeaf(BNode* node, int key) {
    if (node == nullptr)
        return node;

    for (int i = 0; i < node->count; i++)
        if (key < node->keys[i])
            return node->ptr[i] != nullptr ? findLeaf(node->ptr[i], key) : node;

    return node->ptr[node->count] != nullptr
               ? findLeaf(node->ptr[node->count], key)
               : node;
}

static bool comp(BNode* a, BNode* b) {
    if (b == nullptr) return true;
    if (a == nullptr) return false;
    return a->keys[0] < b->keys[0];
}

// ---------------------------------------------------------------------------
// Insertion
// ---------------------------------------------------------------------------

BNode* overflow(BNode* node, BNode* newChild, int key, int d) {
    // Collect all keys, add the new one, and sort
    vector<int> allKeys(node->keys.begin(), node->keys.begin() + 2 * d);
    allKeys.push_back(key);
    sort(allKeys.begin(), allKeys.end());

    // Left half stays in node
    node->keys.clear();
    node->keys.insert(node->keys.begin(), allKeys.begin(), allKeys.begin() + d);

    // Right half goes into a new sibling
    BNode* sibling = new BNode;
    sibling->keys.insert(sibling->keys.begin(), allKeys.begin() + d + 1, allKeys.end());
    node->count = sibling->count = d;

    if (newChild != nullptr) {
        // Redistribute child pointers
        vector<BNode*> allPtrs(node->ptr.begin(), node->ptr.begin() + 2 * d + 1);
        allPtrs.push_back(newChild);
        sort(allPtrs.begin(), allPtrs.end(), comp);

        node->ptr.clear();
        node->ptr.insert(node->ptr.begin(), allPtrs.begin(), allPtrs.begin() + d + 1);
        sibling->ptr.insert(sibling->ptr.begin(), allPtrs.begin() + d + 1, allPtrs.end());

        for (int i = 0; i < (int)node->ptr.size(); i++) {
            node->ptr[i]->parent    = node;
            sibling->ptr[i]->parent = sibling;
        }
    } else {
        node->ptr.resize(d + 1, nullptr);
        sibling->ptr.resize(d + 1, nullptr);
    }

    // The median key bubbles up
    int medianKey = allKeys[d];
    BNode* parent = node->parent;

    if (parent == nullptr) {
        // Create a new root
        parent = new BNode;
        parent->keys.push_back(medianKey);
        parent->ptr.push_back(node);
        parent->ptr.push_back(sibling);
        parent->count++;
        node->parent    = parent;
        sibling->parent = parent;
        return parent;
    }

    if (parent->count >= 2 * d) {
        // Parent also overflows
        return overflow(parent, sibling, medianKey, d);
    }

    // Parent has room
    parent->count++;
    parent->keys.push_back(medianKey);
    parent->ptr.push_back(sibling);
    sort(parent->keys.begin(), parent->keys.begin() + parent->count);
    sort(parent->ptr.begin(),  parent->ptr.begin()  + parent->count + 1, comp);

    BNode* root = parent;
    while (root->parent) root = root->parent;
    return root;
}

BNode* add(BNode*& root, int key, int d) {
    if (root == nullptr) {
        root = new BNode;
        root->keys.push_back(key);
        root->count++;
        root->ptr.resize(2, nullptr);
        return root;
    }

    BNode* leaf = findLeaf(root, key);

    if (leaf->count == 2 * d) {
        return overflow(leaf, nullptr, key, d);
    }

    leaf->keys.push_back(key);
    sort(leaf->keys.begin(), leaf->keys.end());
    leaf->count++;
    leaf->ptr.push_back(nullptr);
    return root;
}

// ---------------------------------------------------------------------------
// Traversal
// ---------------------------------------------------------------------------

void inorder(BNode* node) {
    if (node == nullptr) return;
    for (int i = 0; i < (int)node->keys.size(); i++) {
        if ((int)node->ptr.size() > i) inorder(node->ptr[i]);
        cout << node->keys[i] << " ";
    }
    if ((int)node->ptr.size() > (int)node->keys.size())
        inorder(node->ptr[node->keys.size()]);
}

void levelOrder(queue<BNode*>& q, int cnt) {
    if (q.empty()) return;
    if (cnt == 0) cnt = (int)q.size();

    BNode* node = q.front();
    q.pop();

    for (int i = 0; i < node->count; i++) cout << node->keys[i] << " ";
    cout << "  ";
    if (cnt == 1) cout << "-1\n";

    for (int i = 0; i <= node->count; i++)
        if (node->ptr[i] != nullptr) q.push(node->ptr[i]);

    levelOrder(q, cnt - 1);
}

// ---------------------------------------------------------------------------
// Deletion helpers
// ---------------------------------------------------------------------------

pair<BNode*, int> findKey(BNode* node, int key) {
    if (node == nullptr) return {node, -1};

    for (int i = 0; i < node->count; i++) {
        if (key == node->keys[i]) return {node, i};
        if (key < node->keys[i])  return findKey(node->ptr[i], key);
    }
    return findKey(node->ptr[node->count], key);
}

pair<BNode*, int> checkLeft(BNode* node, int d) {
    BNode* parent = node->parent;
    if (parent == nullptr) return {nullptr, -1};

    int i = 0;
    for (; i <= parent->count; i++)
        if (parent->ptr[i] == node) break;

    if (i == 0) return {nullptr, -1};

    BNode* leftSibling = parent->ptr[i - 1];
    return leftSibling->count > d ? make_pair(leftSibling, i - 1)
                                  : make_pair(leftSibling, -1);
}

pair<BNode*, int> checkRight(BNode* node, int d) {
    BNode* parent = node->parent;
    if (parent == nullptr) return {nullptr, -1};

    int i = 0;
    for (; i <= parent->count; i++)
        if (parent->ptr[i] == node) break;

    if (i == parent->count) return {nullptr, -1};

    BNode* rightSibling = parent->ptr[i + 1];
    return rightSibling->count > d ? make_pair(rightSibling, i)
                                   : make_pair(rightSibling, -1);
}

int getInorderPredecessor(BNode* node, int d) {
    if (node->ptr[node->count] == nullptr) {
        if (node->count <= d) return -1;
        int val = node->keys.back();
        node->keys.pop_back();
        node->ptr.pop_back();
        node->count--;
        return val;
    }
    return getInorderPredecessor(node->ptr[node->count], d);
}

int getInorderSuccessor(BNode* node, int d) {
    if (node->ptr[0] == nullptr) {
        if (node->count <= d) return -1;
        int val = node->keys[0];
        node->keys.erase(node->keys.begin());
        node->ptr.erase(node->ptr.begin());
        node->count--;
        return val;
    }
    // Note: intentionally calls getInorderPredecessor (original logic preserved)
    return getInorderPredecessor(node->ptr[0], d);
}

BNode* getInorderPredecessorNode(BNode* node, int d) {
    if (node->ptr[node->count] == nullptr) return node;
    return getInorderPredecessorNode(node->ptr[node->count], d);
}

BNode* getInorderSuccessorNode(BNode* node, int d) {
    if (node->ptr[0] == nullptr) return node;
    // Note: intentionally calls getInorderPredecessorNode (original logic preserved)
    return getInorderPredecessorNode(node->ptr[0], d);
}

// ---------------------------------------------------------------------------
// Underflow fix
// ---------------------------------------------------------------------------

BNode* underFlow(BNode*& node, int d) {
    BNode* parent = node->parent;

    if (parent == nullptr) {
        if (node->count > 0) return node;
        BNode* child = node->ptr[0];
        child->parent = nullptr;
        delete node;
        return child;
    }

    if (node->count >= d) {
        BNode* root = parent;
        while (root->parent) root = root->parent;
        return root;
    }

    // Try borrowing from left sibling
    auto [leftSibling, il] = checkLeft(node, d);
    if (il != -1) {
        BNode* leftLast = leftSibling->ptr.back();
        int    val      = leftSibling->keys.back();
        leftSibling->keys.pop_back();
        leftSibling->ptr.pop_back();
        leftSibling->count--;

        int parentVal    = parent->keys[il];
        parent->keys[il] = val;

        node->keys.insert(node->keys.begin(), parentVal);
        node->ptr.insert(node->ptr.begin(), leftLast);
        if (leftLast) leftLast->parent = node;
        node->count++;

        BNode* root = parent;
        while (root->parent) root = root->parent;
        return root;
    }

    // Try borrowing from right sibling
    auto [rightSibling, ir] = checkRight(node, d);
    if (ir != -1) {
        BNode* rightFirst = rightSibling->ptr[0];
        int    val        = rightSibling->keys[0];
        rightSibling->keys.erase(rightSibling->keys.begin());
        rightSibling->ptr.erase(rightSibling->ptr.begin());
        rightSibling->count--;

        int parentVal    = parent->keys[ir];
        parent->keys[ir] = val;

        node->keys.insert(node->keys.end(), parentVal);
        node->ptr.insert(node->ptr.end(), rightFirst);
        if (rightFirst) rightFirst->parent = node;
        node->count++;

        BNode* root = parent;
        while (root->parent) root = root->parent;
        return root;
    }

    // Must merge
    if (leftSibling != nullptr) {
        int i = 0;
        for (; i <= parent->count; i++)
            if (parent->ptr[i] == node) break;

        int              separatorKey = parent->keys[i - 1];
        vector<int>      nodeKeys(node->keys);
        vector<BNode*>   nodePtrs(node->ptr);

        parent->ptr.erase(parent->ptr.begin() + i);
        parent->keys.erase(parent->keys.begin() + i - 1);
        parent->count--;

        leftSibling->keys.push_back(separatorKey);
        leftSibling->keys.insert(leftSibling->keys.end(), nodeKeys.begin(), nodeKeys.end());
        leftSibling->ptr.insert(leftSibling->ptr.end(), nodePtrs.begin(), nodePtrs.end());
        if (leftSibling->ptr[0])
            for (auto& child : nodePtrs) child->parent = leftSibling;
        leftSibling->count = (int)leftSibling->keys.size();

        delete node;

        if (parent->count < d) return underFlow(parent, d);

        BNode* root = parent;
        while (root->parent) root = root->parent;
        return root;
    }

    if (rightSibling != nullptr) {
        int i = 0;
        for (; i <= parent->count; i++)
            if (parent->ptr[i] == node) break;

        int              separatorKey  = parent->keys[i];
        vector<int>      rightKeys(rightSibling->keys);
        vector<BNode*>   rightPtrs(rightSibling->ptr);

        parent->ptr.erase(parent->ptr.begin() + i + 1);
        parent->keys.erase(parent->keys.begin() + i);
        parent->count--;

        node->keys.push_back(separatorKey);
        node->keys.insert(node->keys.end(), rightKeys.begin(), rightKeys.end());
        node->ptr.insert(node->ptr.end(), rightPtrs.begin(), rightPtrs.end());
        if (node->ptr[0])
            for (auto& child : rightPtrs) child->parent = node;
        node->count = (int)node->keys.size();

        delete rightSibling;

        if (parent->count < d) return underFlow(parent, d);

        BNode* root = parent;
        while (root->parent) root = root->parent;
        return root;
    }

    cout << "impossible case: node has neither left nor right sibling\n";
    BNode* root = parent;
    while (root->parent && root->parent->count > 0) root = root->parent;
    return root;
}

// ---------------------------------------------------------------------------
// Deletion
// ---------------------------------------------------------------------------

BNode* del(BNode*& root, int key, int d) {
    if (root == nullptr || root->count == 0) return root;

    auto [node, index] = findKey(root, key);

    if (index == -1) {
        cout << "key not found\n";
        return root;
    }

    // Leaf node: directly remove
    if (node->ptr[0] == nullptr) {
        node->keys.erase(node->keys.begin() + index);
        node->count--;
        node->ptr.resize(node->count + 1, nullptr);

        if (node->count < d) return underFlow(node, d);
        return root;
    }

    // Internal node: replace with inorder predecessor if possible
    int predecessor = getInorderPredecessor(node->ptr[index], d);
    if (predecessor != -1) {
        node->keys[index] = predecessor;
        return root;
    }

    // Try inorder successor
    int successor = getInorderSuccessor(node->ptr[index + 1], d);
    if (successor != -1) {
        node->keys[index] = successor;
        return root;
    }

    // Last resort: pull successor node's first key and handle underflow
    BNode* successorNode = getInorderSuccessorNode(node->ptr[index + 1], d);
    node->keys[index] = successorNode->keys[0];

    successorNode->keys.erase(successorNode->keys.begin());
    successorNode->ptr.erase(successorNode->ptr.begin());
    successorNode->count--;

    return underFlow(successorNode, d);
}

// ---------------------------------------------------------------------------
// Main
// ---------------------------------------------------------------------------

int main() {
    int order;
    cin >> order;
    int d = order / 2;

    int    key;
    BNode* root = nullptr;

    while (cin >> key && key != -1)
        root = add(root, key, d);

    // Print tree before deletion
    inorder(root);
    cout << "\n";
    {
        queue<BNode*> q;
        q.push(root);
        levelOrder(q, 0);
    }

    cout << "\n--------------------\n";

    root = del(root, 6, d);

    // Print tree after deletion
    inorder(root);
    cout << "\n";
    {
        queue<BNode*> q;
        q.push(root);
        levelOrder(q, 0);
    }

    return 0;
}