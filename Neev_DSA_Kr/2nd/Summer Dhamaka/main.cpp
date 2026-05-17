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
		if(i < s.size())  create(T->ptr[s[i]-'A'], s, i);
		else T->eow = 1;
		return;
	}
	int x = 0;
	while(x < T->s.size() && (i+x) < s.size() && T->s[x] == s[i+x]) x++;
	if(x==0) return;
	trnode* X = new trnode;
	X->s = T->s.substr(x);
	X->eow = T->eow;        // 1 OR 0
	memcpy(X->ptr, T->ptr, sizeof(T->ptr));     //  memcpy(dest, src, strlen(src) + 1);
	memset(T->ptr, 0, sizeof(T->ptr));
	T->s = T->s.substr(0, x);
	T->eow = 0;
	if(X->s.size()) T->ptr[X->s[0]-'A'] = X;
	else T->eow = X->eow;
	if(i+x < s.size()) create(T->ptr[s[i+x]-'A'], s, i+x);
	else T->eow = 1;

}

int cnt = 0;

void print(trnode* T, string s = "") {
	if(!T) return;
	s += T->s;
	if(T->eow > 0) cout << s << "\n";
	cnt++;
	for(int i = 0; i < 26; i++) print(T->ptr[i], s);
}



int main() {

	trnode* T = new trnode;
	string s;

	while(cin >> s && s != "#")
		create(T->ptr[s[0]-'A'], s);


	print(T);
	cout << cnt;

	return 0;

}