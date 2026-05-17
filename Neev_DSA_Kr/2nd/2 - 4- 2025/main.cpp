#include<iostream>
#include<cmath>
#include<vector>
#include<queue>
using namespace std;

struct lnode{
  int data;
  lnode* next = NULL;
};

struct TreeNode{
    int data;
    TreeNode* left,*right;
};

struct Stack{
    lnode* L = NULL;
    int size=0;
};

void pushSt(Stack &s, int k){
    s.size++;
    lnode* L1 = new lnode{k,s.L};
    s.L = L1;
}

int popSt(Stack &s){
    if(s.size==0) return -1;
    s.size--;
    lnode* L1 = s.L;
    int x = s.L->data;
    s.L=s.L->next;   
    delete L1;
    
    return x;    
}

int peekSt(Stack &s){
    if(s.size==0) return -1;
    return s.L->data;     
}
bool isEmpty(Stack &s){
    return s.size==0;
}
void insertRevSt(Stack &s, int t){
    if(isEmpty(s)){
        pushSt(s, t);
        return;
    }
    int x = popSt(s);
    insertRevSt(s, t);
    pushSt(s, x);
}

void reverseSt(Stack &s){
    if(s.size==0) return;
    int t = popSt(s);
    reverseSt(s);
    insertRevSt(s,t);
}

TreeNode* createT(Stack &s){
   int k = popSt(s);
   if(k==0) return NULL;
   return new TreeNode{k,createT(s),createT(s)};
}

void inorderTree(TreeNode* T){
    if(!T) return;
    inorderTree(T->left);
        cout<<T->data<<" ";
    inorderTree(T->right);
}

void heapify(int c, vector<int> &H) {
	if(c==0) return;
	if(H[(c-1)/2]<H[c]) return;
	swap(H[c],H[(c-1)/2]);
	heapify((c-1)/2,H);
}

void heapify_Helper(int c, vector<int> &H) {
	if(c>=H.size()) return;
	if(2*c+1>=H.size() && 2*c+2>=H.size()) return;
	int i;
    if(2*c+2>=H.size()) i = 2*c+1;
    else if(H[2*c+1]<H[2*c+2]) i=2*c+1;
    else i = 2*c+2;
	if(H[i]>H[c]) return;       // c is parent
	swap(H[i],H[c]);
	heapify_Helper(i,H);
}

vector<int> heapSort(vector<int> &H) {     // making empty or not depends on &
vector<int>arr;
	while(true) {
	    int x = H.back();
        H.pop_back();
		arr.push_back(H[0]);
		if(H.empty()) return arr;
		H[0] = x;
		heapify_Helper(0,H);
	}
	return arr;
}


void insertHeap(vector<int> &H, TreeNode* T){
        if(!T) return;
    insertHeap(H, T->left);
        H.push_back(T->data);
		heapify(H.size()-1,H);
    insertHeap(H, T->right);
}

vector<int> makeHeap(TreeNode* T){
    vector<int>H;
    insertHeap(H,T);
    return H;
}

void insertBST(TreeNode* & T, int &k){
    if(T==NULL) T = new TreeNode{k,NULL, NULL};
    else (k>T->data) ? insertBST(T->right,k) : insertBST(T->left,k); 
}

void divideAlgo(TreeNode* &T, vector<int> &arr, int l, int h){
    if(l>h) return;
    int mid = l + (h-l)/2;
    insertBST(T,arr[mid]);
    divideAlgo(T,arr,l,mid-1);
    divideAlgo(T,arr,mid+1,h);
}

TreeNode* createBST(vector<int> &arr){
    int x = 0;
    TreeNode* T = NULL;
    divideAlgo(T, arr, 0, arr.size()-1);
    return T;
}

void levelBylevel(queue<TreeNode*> &Q, int cnt){
    if(Q.empty()) return;
    if(cnt==0) cnt = Q.size();
    TreeNode* T = Q.front();
    Q.pop();
    cout << T->data << " ";
    if(cnt==1) cout << "999 ";
    if(T->left) Q.push(T->left);
    if(T->right) Q.push(T->right);
    levelBylevel(Q,cnt-1);
}

void levelOrder(TreeNode* T){
    queue<TreeNode*> Q;
    Q.push(T);
    levelBylevel(Q,0);  
}

int main(){
    
    Stack s;
    int k;
    while(cin>>k && k!=-1) pushSt(s,k);
    reverseSt(s);
    TreeNode* T = createT(s);
    inorderTree(T);                      cout<<endl;
    vector<int> H = makeHeap(T);
    for(int i : H) cout<<i<<" ";         cout<<endl;
    vector<int> arr = heapSort(H);
    for(int i : arr) cout<<i<<" ";       cout<<endl;
    TreeNode* BST = createBST(arr);
    levelOrder(BST); 
    
    return 0;
}