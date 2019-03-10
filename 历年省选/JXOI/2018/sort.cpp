#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using std::min; using std::max;
using std::swap; using std::sort;
using std::unique; using std::lower_bound;
typedef long long ll;

template<typename T>
void read(T &x) {
    int flag = 1; x = 0; char ch = getchar();
    while(ch < '0' || ch > '9') { if(ch == '-') flag = -flag; ch = getchar(); }
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int N = 2e5 + 10, M = 1.02e7 + 10, P = 998244353;
int n, m, l, r, x[N], lsh[N], tot[N], sum[N];
int fac[M], ifac[M];

int qpow(int a, int b) {
	int ret = 1;
	for(; b; a = 1ll * a * a % P, b >>= 1)
		if(b & 1) ret = 1ll * ret * a % P;
	return ret;
}

int T;
signed main () {
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
	read(T), fac[0] = 1;
	for(register int i = 1; i <= M - 10; ++i)
		fac[i] = 1ll * fac[i - 1] * i % P;
	ifac[M - 10] = qpow(fac[M - 10], P - 2);
	for(register int i = M - 10; i >= 1; --i)
		ifac[i - 1] = 1ll * ifac[i] * i % P;
	while(T--) {
		read(n), read(m), read(l), read(r);
		memset(tot, 0, sizeof(int) * (n + 5));
		memset(sum, 0, sizeof(int) * (n + 5));
		int ret = fac[n + m], rest = r - l + 1, tmp = n;
		for(int i = 1; i <= n; ++i)
			read(x[i]), lsh[i] = x[i];
		sort(lsh + 1, lsh + tmp + 1);
		tmp = unique(lsh + 1, lsh + tmp + 1) - lsh - 1;
		for(int i = 1; i <= tmp; ++i)
			if(l <= lsh[i] && lsh[i] <= r)
				--rest;
		for(int i = 1; i <= n; ++i) {
			x[i] = lower_bound(lsh + 1, lsh + tmp + 1, x[i]) - lsh;
			if(lsh[x[i]] >= l && lsh[x[i]] <= r) ++tot[x[i]];
			++sum[x[i]];
		}
		int ans = 1, st = tmp;
		for(int i = 1; i <= tmp; ++i)
			ans = 1ll * ans * fac[sum[i]] % P;
		sort(tot + 1, tot + tmp + 1);
		for(int i = 1; i <= tmp; ++i)
			if(tot[i]) { st = i - 1; break; }
		int ed = tmp - st;
		for(int i = 1; i <= ed; ++i)
			tot[i] = tot[i + st];
		for(int i = 1; i <= ed && m; ++i) {
			if(tot[i] == tot[i - 1]) continue;
			if(1ll * (tot[i] - tot[i - 1]) * (i - 1 + rest) <= m) {
				m -= (tot[i] - tot[i - 1]) * (i - 1 + rest);
				int x = 1ll * fac[tot[i]] * ifac[tot[i - 1]] % P;
				ans = 1ll * ans * qpow(x, i - 1 + rest) % P;
			} else {
				int _ = m / (i - 1 + rest);
				int x = 1ll * fac[tot[i - 1] + _] * ifac[tot[i - 1]] % P;
				ans = 1ll * ans * qpow(x, i - 1 + rest);
				ans = 1ll * ans * qpow(tot[i - 1] + _ + 1, m % (i - 1 + rest)) % P;
				m = 0; break;
			}
		}
		if(m) {
			int _ = m / (r - l + 1);
			int x = 1ll * fac[tot[ed] + _] * ifac[tot[ed]] % P;
			ans = 1ll * ans * qpow(x, r - l + 1) % P;
			ans = 1ll * ans * qpow(tot[ed] + _ + 1, m % (r - l + 1)) % P;
		}
		printf("%d\n", (int)(1ll * ret * qpow(ans, P - 2) % P));
	}
	return 0;
} 
