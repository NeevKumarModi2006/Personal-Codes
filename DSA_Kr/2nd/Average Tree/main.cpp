// Average Tree
// It is a complete binary tree , but stored in an Array, and is
// implemented using Array.  You should code an Array AT[ ] only as a Tree,  not with pointers
// Create an Average Tree (AT ) as shown below and print the contents of the tree
// created( i.e. that is in Array) in a level order way as shown below.
// Note :  Fully Code using Arrays only.   Must have to code a recursive function to create the Tree
// The input is given , read input into an Array A [] and from that array create AT [
    #include <bits/stdc++.h>
    using namespace std;
    
    struct TreeNode
    {
        int data;
        TreeNode *left;
        TreeNode *right;
    };
    void insert_T(TreeNode *&T, int k)
    {
        T = new TreeNode;
        T->data = k;
        T->left = NULL;
        T->right = NULL;
    }
    
    void level(TreeNode *T)
    {
        queue<TreeNode *> Q;
        Q.push(T);
        int cnt = 0;
        while (!Q.empty())
        {
            if (cnt == 0)
                cnt = Q.size();
            TreeNode *X = Q.front();
            Q.pop();
            cout << X->data << " ";
            if (cnt == 1)
                cout << "/\n";
            if (X->left)
                Q.push(X->left);
            if (X->right)
                Q.push(X->right);
            cnt--;
        }
    }
    
    void pre(TreeNode *T)
    {
        if (!T)
            return;
        cout << T->data << " ";
        pre(T->left);
        pre(T->right);
    }
    
    TreeNode *create_AT(vector<int> arr, int l, int h)
    {
        if (l > h)  return NULL;
        if (l == h) return new TreeNode{arr[l],NULL,NULL};
        else
        {
            int mid = l + (h-l)/2;
          TreeNode* T1 = create_AT(arr,l,mid);
          TreeNode* T2 = create_AT(arr,mid+1,h);
          return new TreeNode{((T1->data) + (T2->data)) / 2, T1, T2};
        }
    }
    void createAT(vector<int>& arr, int h) {
        if(h<1) return;
        vector<int> a;
            for (int i = 0; i <= h; i += 2) {
                if (i+1 <= h)
                    a.push_back((arr[i] + arr[i + 1]) / 2);
                else a.push_back(arr[i]);
            }
            arr.insert(arr.begin(),a.begin(),a.end());
            createAT(arr,a.size()-1);
    
    }
    void levelOrder(vector<int>& AT) {
        int a = 1;
        int c = 1;
        for (int i = 0; i < AT.size(); i++) {
            cout << AT[i] << " ";
            if ((i + 1) ==  c ) {
                cout << "/\n";
                a*=2;
                c += a;
            }
        }
    }
    
    int main()
    {
        vector<int> arr;
        int k;
        while (cin >> k && k != -1)     // 5 3 6 2 4 8 7 5 -1
            arr.push_back(k);
    
        // if (arr.size() % 2)
        //     arr.push_back(0);
        // TreeNode *T = create_AT(arr, 0, arr.size()-1);
        // level(T);
    
        createAT(arr, arr.size()-1);
        levelOrder(arr);
    
        return 0;
    }