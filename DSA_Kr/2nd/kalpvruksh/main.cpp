#include <bits/stdc++.h>
using namespace std;

struct bnode {
	int count = 0;
	vector<int> keys;
	vector<bnode*> ptr;
	bnode* p = NULL;
};

bnode* find(bnode* B, int k) {
	if (B == NULL) 		return B;
	
	for (int i = 0; i < B->count; i++) 
		if (k < B->keys[i]) 
			return B->ptr[i] != NULL ? find(B->ptr[i], k) : B;
		
	return B->ptr[B->count]!=NULL ? find(B->ptr[B->count],k) : B;
}

static bool comp(bnode* A, bnode* B) {
	if(B==NULL) return true;
	if(A==NULL) return false;
	return A->keys[0]<B->keys[0];
}

bnode* overflow(bnode* B,bnode* N, int k, int d) {

	vector<int> Q(B->keys.begin(),B->keys.begin()+2*d); // B->count+1 = 2*d+1
	Q.push_back(k);
	sort(Q.begin(), Q.end());
	B->keys.clear();
	B->keys.insert(B->keys.begin(), Q.begin(), Q.begin()+d); // 0 to d

	bnode* B2 = new bnode;
	B2->keys.insert(B2->keys.begin(), Q.begin()+d+1, Q.end());
	B->count=B2->count=d;
	
	if(N!=NULL) {
	    vector<bnode*> X (B->ptr.begin(),B->ptr.begin()+2*d+1);     // 2d+1
		X.push_back(N);
		sort(X.begin(),X.end(),comp);   
		B->ptr.clear();
		B->ptr.insert(B->ptr.begin(),X.begin(), X.begin()+d+1);
		B2->ptr.insert(B2->ptr.begin(),X.begin()+d+1, X.end());
		for(int i=0;i<B->ptr.size();i++){       
		    B->ptr[i]->p = B;
		    B2->ptr[i]->p = B2;
		}
	}
	else {
		B->ptr.resize(d+1,NULL);
		B2->ptr.resize(d+1,NULL);
	}

	k = Q[d];
	bnode* P = B->p;
	if (P==NULL) {
		P = new bnode;
		P->keys.push_back(k);
		P->ptr.push_back(B);
		P->ptr.push_back(B2);
		P->count++;
    	B->p = B2->p =  P;
		return P;
	}
	else {
		if (P->count >= 2*d) return overflow(P,B2,k,d);
		
		else {
		    P->count++;
         P->keys.push_back(k);
         P->ptr.push_back(B2);
         sort(P->keys.begin(),P->keys.end());
         sort(P->ptr.begin(),P->ptr.end(),comp);
        B2->p = P;
         while(P->p) P = P->p;
		 return P;
		}
	}
}


bnode* add(bnode* &B, int k, int d) {
	if (B == NULL) {
		B = new bnode;
		B->keys.push_back(k);
		B->count++;
		B->ptr.resize(2,NULL);
		return B;
	}
	bnode* B1 = find(B, k);
	if (B1->count == 2*d) {
		return overflow(B1,NULL, k, d);  // leaf
	} else {
		B1->keys.push_back(k);      // B1 is leaf
		sort(B1->keys.begin(), B1->keys.end());
		B1->count++;
		B1->ptr.push_back(NULL);
	}
	return B;
}

void ino(bnode* B) {
	if (B == NULL) return;
	for (int i = 0; i < B->keys.size(); i++) {
		if (B->ptr.size() > i) ino(B->ptr[i]);
		cout << B->keys[i] << " ";
	}
	if (B->ptr.size() > B->keys.size()) ino(B->ptr[B->keys.size()]);
}

void level(queue<bnode*> &Q, int cnt) {
	if (Q.empty()) return;
	if (cnt == 0) cnt = Q.size();

	bnode *T = Q.front();
	Q.pop();

	for (int i = 0; i < T->count; i++) cout << T->keys[i] << " ";
	cout<<"  ";
	if (cnt==1) cout << "-1\n";

	for (int i = 0; i <= T->count; i++)
		if (T->ptr[i] != NULL)Q.push(T->ptr[i]);

	level(Q, cnt-1);
}

bnode* fixUnderflow(bnode* parent, int idx, int d);

bnode* findPredecessor(bnode* B) {
    // Find the rightmost leaf node in the left subtree
    while (B->ptr.back() != NULL) {
        B = B->ptr.back();
    }
    return B;
}

bnode* findSuccessor(bnode* B) {
    // Find the leftmost leaf node in the right subtree
    while (B->ptr.front() != NULL) {
        B = B->ptr.front();
    }
    return B;
}

// Get previous sibling if exists, otherwise returns NULL
bnode* getPrevSibling(bnode* parent, int idx) {
    return idx > 0 ? parent->ptr[idx - 1] : NULL;
}

// Get next sibling if exists, otherwise returns NULL
bnode* getNextSibling(bnode* parent, int idx, int count) {
    return idx < count ? parent->ptr[idx + 1] : NULL;
}

// Borrow a key from the previous sibling
void borrowFromPrev(bnode* node, int idx, bnode* sibling, int d) {
    // Shift all keys and pointers in the current node one position right
    node->ptr.push_back(NULL);
    for (int i = node->count; i > 0; i--) {
        node->keys[i] = node->keys[i-1];
        node->ptr[i+1] = node->ptr[i];
    }
    node->ptr[1] = node->ptr[0];
    
    // Parent's key goes into the current node
    node->keys[0] = node->p->keys[idx-1];
    
    // Last key from sibling becomes parent's key
    node->p->keys[idx-1] = sibling->keys[sibling->count-1];
    
    // If not a leaf, move the last child from sibling
    if (!sibling->ptr.empty() && sibling->ptr[sibling->count] != NULL) {
        node->ptr[0] = sibling->ptr[sibling->count];
        sibling->ptr[sibling->count] = NULL;
        node->ptr[0]->p = node;
    }
    
    // Update counts
    node->count++;
    sibling->count--;
    
    // Resize sibling's containers
    sibling->keys.resize(sibling->count);
    sibling->ptr.resize(sibling->count + 1);
}

// Borrow a key from the next sibling
void borrowFromNext(bnode* node, int idx, bnode* sibling, int d) {
    // Parent's key goes into the current node
    node->keys.push_back(node->p->keys[idx]);
    
    // First key from sibling becomes parent's key
    node->p->keys[idx] = sibling->keys[0];
    
    // If not a leaf, move the first child from sibling
    if (!sibling->ptr.empty() && sibling->ptr[0] != NULL) {
        node->ptr.push_back(sibling->ptr[0]);
        node->ptr.back()->p = node;
        
        // Shift all of sibling's children left
        for (int i = 0; i < sibling->count; i++) {
            sibling->ptr[i] = sibling->ptr[i+1];
        }
    } else {
        node->ptr.push_back(NULL);
    }
    
    // Shift all of sibling's keys left
    for (int i = 0; i < sibling->count - 1; i++) {
        sibling->keys[i] = sibling->keys[i+1];
    }
    
    // Update counts
    node->count++;
    sibling->count--;
    
    // Resize sibling's containers
    sibling->keys.resize(sibling->count);
    sibling->ptr.resize(sibling->count + 1);
}

// Merge node with its next sibling
bnode* merge(bnode* parent, int idx, int d) {
    bnode* child = parent->ptr[idx];
    bnode* sibling = parent->ptr[idx + 1];
    
    // Add the separator key from parent to child
    child->keys.push_back(parent->keys[idx]);
    
    // Add all keys and pointers from sibling to child
    for (int i = 0; i < sibling->count; i++) {
        child->keys.push_back(sibling->keys[i]);
        if (sibling->ptr[i] != NULL) {
            child->ptr.push_back(sibling->ptr[i]);
            sibling->ptr[i]->p = child;
        }
    }
    
    // Add the last pointer from sibling if not null
    if (sibling->ptr[sibling->count] != NULL) {
        child->ptr.push_back(sibling->ptr[sibling->count]);
        sibling->ptr[sibling->count]->p = child;
    }
    
    // Update child's count
    child->count = child->keys.size();
    
    // Shift keys and pointers in parent to remove the separator
    for (int i = idx; i < parent->count - 1; i++) {
        parent->keys[i] = parent->keys[i + 1];
        parent->ptr[i + 1] = parent->ptr[i + 2];
    }
    
    // Update parent's count
    parent->count--;
    parent->keys.resize(parent->count);
    parent->ptr.resize(parent->count + 1);
    
    // Delete sibling
    delete sibling;
    
    // If parent is now empty (was the root), make child the new root
    if (parent->count == 0 && parent->p == NULL) {
        child->p = NULL;
        delete parent;
        return child;
    }
    
    // Handle parent underflow if needed
    if (parent->count < d && parent->p != NULL) {
        // Find parent's index in its parent
        bnode* grandparent = parent->p;
        int parent_idx = 0;
        while (parent_idx <= grandparent->count && grandparent->ptr[parent_idx] != parent) {
            parent_idx++;
        }
        
        // Handle parent's underflow
        return fixUnderflow(grandparent, parent_idx, d);
    }
    
    return parent->p ? parent->p : parent;
}

bnode* fixUnderflow(bnode* parent, int idx, int d) {
    bnode* child = parent->ptr[idx];
    
    // Try borrowing from left sibling
    if (idx > 0) {
        bnode* leftSibling = parent->ptr[idx - 1];
        if (leftSibling->count > d) {
            borrowFromPrev(child, idx, leftSibling, d);
            return parent->p ? parent->p : parent;
        }
    }
    
    // Try borrowing from right sibling
    if (idx < parent->count) {
        bnode* rightSibling = parent->ptr[idx + 1];
        if (rightSibling->count > d) {
            borrowFromNext(child, idx, rightSibling, d);
            return parent->p ? parent->p : parent;
        }
    }
    
    // Must merge nodes
    if (idx > 0) {
        // Merge with left sibling
        return merge(parent, idx - 1, d);
    } else {
        // Merge with right sibling
        return merge(parent, idx, d);
    }
}

void removeKey(bnode* &B, int k, int d) {
    if (!B) return;
    
    // Find the index of k in the current node
    int idx = 0;
    while (idx < B->count && B->keys[idx] < k) {
        idx++;
    }
    
    // Key is in this node
    if (idx < B->count && B->keys[idx] == k) {
        // Case 1: Node is a leaf
        if (B->ptr[0] == NULL) {
            // Remove the key
            for (int i = idx; i < B->count - 1; i++) {
                B->keys[i] = B->keys[i + 1];
            }
            B->count--;
            B->keys.resize(B->count);
            B->ptr.resize(B->count + 1);
            
            // Handle underflow if necessary
            if (B->count < d && B->p != NULL) {
                // Find B's index in its parent
                bnode* parent = B->p;
                int child_idx = 0;
                while (child_idx <= parent->count && parent->ptr[child_idx] != B) {
                    child_idx++;
                }
                
                bnode* newRoot = fixUnderflow(parent, child_idx, d);
                if (parent->p == NULL && parent->count == 0) {
                    B = newRoot; // Update the root if it changed
                }
            }
        }
        // Case 2: Node is an internal node
        else {
            // Find predecessor (rightmost key in left subtree)
            bnode* pred = findPredecessor(B->ptr[idx]);
            
            // Replace key with predecessor
            int predKey = pred->keys[pred->count - 1];
            B->keys[idx] = predKey;
            
            // Recursively delete predecessor
            removeKey(B->ptr[idx], predKey, d);
        }
    }
    // Key is not in this node, go to appropriate child
    else if (B->ptr[0] != NULL) {
        bnode* child = B->ptr[idx];
        removeKey(child, k, d);
        
        // Check for underflow in child after deletion
        if (child->count < d && child->p != NULL) {
            bnode* newRoot = fixUnderflow(B, idx, d);
            if (B->p == NULL && B->count == 0) {
                B = newRoot; // Update the root if it changed
            }
        }
    }
    // Key not found in tree
    else {
        cout << "Key " << k << " not found in the tree." << endl;
    }
}

int main() {
	int d;
	cin >> d;
	d = (d-1)/2;
	int k;
	bnode* B = NULL;

	while (cin >> k && k != -1) {
		B = add(B, k, d);
	}
			ino(B);
	cout << endl;

	queue<bnode*> Q;
	Q.push(B);
	level(Q,0);
	
    while(cin>>k && k!=-1){
	removeKey(B, k, d);
	cout<<" -----------------"<<k<<"------------------------\n";
    Q.push(B);
	level(Q,0);
    }
	return 0;
}
// 3  4 8 45 10 6 5 18 7 9 36 1 3 -1