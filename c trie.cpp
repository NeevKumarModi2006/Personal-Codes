#include<bits/stdc++.h>
using namespace std;

struct trnode {
	int eow = 0;
	string s = "";
	trnode* ptr[26] = {NULL};
};

void create(trnode* &T, string &s, int i=0) {
	if(!T) {
		T = new trnode;
		T->eow = 1;
		T->s = s.substr(i);
		return;
	}
	if(T->s == s.substr(i, T->s.size())) {
		i += T->s.size();
		if(i < s.size())  create(T->ptr[s[i]-'a'], s, i);
		else T->eow = 1;
		return;
	}
	int x = 0;
	while(x < T->s.size() && (i+x) < s.size() && T->s[x] == s[i+x]) x++;
	if(x==0) return;
	trnode* X = new trnode;
	X->s = T->s.substr(x);
	X->eow = T->eow;        // 1 OR 0
	memcpy(X->ptr, T->ptr, sizeof(T->ptr));     // memcpy(dest, src, strlen(src) + 1);
	memset(T->ptr, 0, sizeof(T->ptr));
	T->s = T->s.substr(0, x);
	T->eow = 0;
	if(X->s.size()) T->ptr[X->s[0]-'a'] = X;
	else T->eow = X->eow;
	if(i+x < s.size()) create(T->ptr[s[i+x]-'a'], s, i+x);
	else T->eow = 1;

}

vector<string>longest;

void print(trnode* T, string s = "") {
	if(!T) return;
	s += T->s;
	if(T->eow > 0) {
	    if(longest.empty() || s.size()==longest[0].size()) longest.push_back(s);
	    else if(s.size()>longest[0].size()){
	        longest.clear();
	        longest.push_back(s);
	    }
		cout << s << " ";
	}
	for(int i = 0; i < 26; i++) print(T->ptr[i], s);
}

void countIt(trnode* T,int &cnt) {
	if(!T) return;
	if(T->eow > 0) cnt++;
	for(int i = 0; i < 26; i++) countIt(T->ptr[i], cnt);
}

int main() {

	trnode* T = new trnode;
	string s;

	while(cin >> s && s != "#") create(T->ptr[s[0]-'a'], s);

	int cnt = 0;
	countIt(T,cnt);
	cout << cnt << endl;
	print(T);
    for(auto &i : longest) cout << endl << i;

	return 0;

}