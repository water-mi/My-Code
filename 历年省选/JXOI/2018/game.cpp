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

const int _ = 1e7 + 10, P = 1e9 + 7;
int l, r, n, fac[_], ifac[_];
bool notprime[_];

int qpow(int a, int b) {
	int ret = 1;
	for(; b; b >>= 1, a = 1ll * a * a % P)
		if(b & 1) ret = 1ll * ret * a % P;
	return ret;
}
int inv(int x) { return qpow(x, P - 2); }
int C(int n, int m) { return 1ll * fac[n] * ifac[m] % P * ifac[n - m] % P; }

int main () {
    freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	read(l), read(r), n = r - l + 1, fac[0] = 1;
	for(int i = 1; i <= _ - 10; ++i)
		fac[i] = 1ll * fac[i - 1] * i % P;
	ifac[_ - 10] = inv(fac[_ - 10]);
	for(int i = _ - 10; i >= 1; --i)
		ifac[i - 1] = 1ll * ifac[i] * i % P;
	if(l == 1) printf("%d\n", (int)(1ll * fac[n + 1] * inv(2) % P));
	else {
		int tot = 0, ret = 0;
		for(int i = l; i <= r; ++i)
			if(!notprime[i]) {
				++tot;
				for(int j = 2; 1ll * j * i <= r; ++j)
					notprime[j * i] = 1;
			}
		for(int i = tot; i <= n; ++i) {
			int now = 1ll * i * tot % P * C(n - tot, n - i) % P
				* fac[i - 1] % P * fac[n - i] % P;
			(ret += now) %= P;
		}
		printf("%d\n", ret);
	}
	return 0;
} 
