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
#if __cplusplus >= 201103l
template<typename T, typename... V>
void read(T &x, V&... v) { read(x), read(v...); }
#endif

const int P = 998244353, R = 160, N = 60;
int n, r[N], f[N][R][R], mx;
int dp(int x, int L, int R) {
	if(x > n) return 1;
	int &ans = f[x][L][R];
	if(ans != -1) return ans; ans = 0;
	for(int i = max(1, L); i <= min(r[x], R); ++i) {
		if(i == L || i == R) (ans += dp(x + 1, i, i)) %= P;
		else (ans += ((dp(x + 1, L, i) + dp(x + 1, i, R)) % P + P - dp(x + 1, i, i)) % P) %= P;
	}
	return ans;
}
int main () {
	freopen("sequence.in", "r", stdin);
	freopen("sequence.out", "w", stdout);
	read(n), memset(f, -1, sizeof f);
	for(int i = 1; i <= n; ++i) read(r[i]), mx = max(mx, r[i]);
	return printf("%d\n", dp(1, 0, mx + 1)), 0;
} 
