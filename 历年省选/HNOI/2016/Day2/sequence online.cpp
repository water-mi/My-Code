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
ll fr[_], fl[_], gr[_], gl[_];
inline int _min(int x, int y) { return a[x] < a[y] ? x : y; }
inline int query(int l, int r) {
	int k = Log[r - l + 1];
	return _min(f[k][l], f[k][r - (1 << k) + 1]);
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
		fr[i] = (ll)a[i] * (i - pre[i]) + fr[pre[i]], gr[i] = gr[i - 1] + fr[i];
	for(int i = n; i >= 1; --i)
		fl[i] = (ll)a[i] * (suf[i] - i) + fl[suf[i]], gl[i] = gl[i + 1] + fl[i];
	int L, R;
	while(q--) {
		read(L), read(R);
		int x = query(L, R);
		ll ret = ((ll)(x - L + 1) * (R - x + 1) * a[x] +
				  gr[R] - gr[x] - fr[x] * (R - x) + 
				  gl[L] - gl[x] - fl[x] * (x - L));
		printf("%lld\n", ret);
	}
	return 0;
} 
