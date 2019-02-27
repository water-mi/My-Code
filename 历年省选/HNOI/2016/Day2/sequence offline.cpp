#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using std::min; using std::max;
using std::swap; using std::sort;
typedef long long ll;

template<typename T>
void read(T &x) {
	int flag = 1; x = 0; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') flag = -flag; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int _ = 1e5 + 10, LogN = 17, Inf = 1e9 + 7;
int n, q, a[_], f[LogN][_], Log[_];
int st[_], top, suf[_], pre[_];
ll fr[_], fl[_], ans[_];
inline int _min(int x, int y) { return a[x] < a[y] ? x : y; }
inline int query(int l, int r) {
	int k = Log[r - l + 1];
	return _min(f[k][l], f[k][r - (1 << k) + 1]);
}

struct Ques { int l, r, k, id; } Qu[_];
inline bool operator < (const Ques &a, const Ques &b) {
	return a.k < b.k || (a.k == b.k && a.r < b.r);
}

inline ll moveback(int l, int r) {
	int p = query(l, r + 1);
	return (ll)a[p] * (p - l + 1) + fr[r + 1] - fr[p];
}
inline ll movefront(int l, int r) {
	int p = query(l - 1, r);
	return (ll)a[p] * (r - p + 1) + fl[l - 1] - fl[p]; 
}

int main () {
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	read(n), read(q), Log[0] = -1;
	for(int i = 1; i <= n; ++i)
		read(a[i]), Log[i] = Log[i >> 1] + 1, f[0][i] = i;
	a[0] = a[n + 1] = Inf;
	for(int j = 1; j <= Log[n]; ++j)
		for(int i = 1; (i + (1 << j) - 1) <= n; ++i)
			f[j][i] = _min(f[j - 1][i], f[j - 1][i + (1 << (j - 1))]);
	for(int i = 1; i <= n; ++i) {
		while(top && a[st[top]] > a[i]) suf[st[top--]] = i;
		pre[i] = st[top], st[++top] = i;
	} 
	while(top) pre[st[top]] = st[top - 1], suf[st[top--]] = n + 1;
	for(int i = 1; i <= n; ++i)
		fr[i] = (ll)a[i] * (i - pre[i]) + fr[pre[i]];
	for(int i = n; i >= 1; --i)
		fl[i] = (ll)a[i] * (suf[i] - i) + fl[suf[i]];
	int L, R, size = sqrt(n);
	for(int i = 1; i <= q; ++i) {
		read(L), read(R);
		Qu[i] = (Ques){L, R, L / size, i};
	}
	sort(Qu + 1, Qu + q + 1);
	int x = Qu[1].l, y = x - 1; ll now = 0;
	for(int i = 1; i <= q; ++i) {
		L = Qu[i].l, R = Qu[i].r;
		while(L < x) now += movefront(x, y), --x;
		while(y < R) now += moveback(x, y), ++y;
		while(L > x) now -= movefront(x + 1, y), ++x;
		while(y > R) now -= moveback(x, y - 1), --y;
		ans[Qu[i].id] = now;
	}
	for(int i = 1; i <= q; ++i)
		printf("%lld\n", ans[i]);
	return 0;
} 
