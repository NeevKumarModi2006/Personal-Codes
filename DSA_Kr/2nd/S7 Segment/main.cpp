#include <bits/stdc++.h>
using namespace std;

struct str {
	int maxx, minn, what;  // what: 1 = inc, 2 = dec, 0 = random, 3 = leaf
	bool valid = true;
		str(int a = 0, int b = 0, int c = 3, bool v = true) {
		maxx = a;
		minn = b;
		what = c;
		valid = v;
	}
};

// Build Segment Tree
str rfn(vector<str> &s, vector<int> &arr, int l, int h, int i) {
	if (l == h) {
		s[i].maxx = s[i].minn = arr[l];
		s[i].what = 3;  // leaf
		s[i].valid = true;
		return s[i];
	}
	str L = rfn(s, arr, l, (l + h) / 2, 2 * i + 1);
	str R = rfn(s, arr, (l + h) / 2 + 1, h, 2 * i + 2);
	s[i].maxx = max(L.maxx, R.maxx);
	s[i].minn = min(L.minn, R.minn);

	int wl = (L.what == 3) ? -1 : L.what;
	int wr = (R.what == 3) ? -1 : R.what;
	if ((wl == 1 || wl == -1) && (wr == 1 || wr == -1) && L.maxx < R.minn) s[i].what = 1;
	else if ((wl == 2 || wl == -1) && (wr == 2 || wr == -1) && L.minn > R.maxx) s[i].what = 2;
	else s[i].what = 0;

	s[i].valid = true;
	return s[i];
}

// Query Function
str qfn(vector<str> &s, vector<int> &arr, int l, int h, int i, int ql, int qh) {
	if (qh < l || ql > h) return {INT_MIN, INT_MAX, 3, false};
	if (ql <= l && qh >= h) return s[i];

	int mid = (l + h) / 2;
	str L = qfn(s, arr, l, mid, 2 * i + 1, ql, qh);
	str R = qfn(s, arr, mid + 1, h, 2 * i + 2, ql, qh);

	if (!L.valid) return R;
	if (!R.valid) return L;

	str res;
	res.valid = true;
	res.maxx = max(L.maxx, R.maxx);
	res.minn = min(L.minn, R.minn);

	int wl = (L.what == 3) ? -1 : L.what;
	int wr = (R.what == 3) ? -1 : R.what;
	if ((wl == 1 || wl == -1) && (wr == 1 || wr == -1) && L.maxx < R.minn) res.what = 1;
	else if ((wl == 2 || wl == -1) && (wr == 2 || wr == -1) && L.minn > R.maxx) res.what = 2;
	else res.what = 0;

	return res;
}

int main() {
	vector<int> arr;
	int k;
	while (cin >> k && k != -1) arr.push_back(k);
	int n = arr.size();

	int size = 1;
	while (size < n) size *= 2;
	size = 2 * size - 1;
	vector<str> s(size + 1);

	rfn(s, arr, 0, n - 1, 0);

	while (cin >> k && k != -1) {
		int r;
		cin >> r;
		str res = qfn(s, arr, 0, n - 1, 0, k, r);
		if (res.what == 1) cout << "increasing\n";
		else if (res.what == 2) cout << "decreasing\n";
		else cout << "random\n";
	}

	return 0;
}
