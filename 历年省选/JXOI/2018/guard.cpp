#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using std::vector;
using std::min; using std::max;
using std::swap; using std::sort;
typedef long long ll;

template<typename T>
void read(T &x) {
    int flag = 1; x = 0; char ch = getchar();
    while(ch < '0' || ch > '9') { if(ch == '-') flag = -flag; ch = getchar(); }
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int N = 5e3 + 10;
int n, h[N], f[N][N];

double getk(int a, int b) {
	if(a == b) return 1e9;
	return 1. * (h[a] - h[b]) / (a - b);
}

int main () {
    freopen("guard.in", "r", stdin);
    freopen("guard.out", "w", stdout);
	read(n); int ans = 0;
	for(int i = 1; i <= n; ++i) read(h[i]);
	for(int r = 1, sum, now; r <= n; ++r) {
		sum = f[r][r] = 1; ans ^= f[r][r];
		now = r;
		for(int l = r - 1; l >= 1; --l) {
			if(getk(l, r) < getk(now, r)) {
				sum += min(f[l + 1][now - 1], f[l + 1][now]);
				now = l;
			}
			f[l][r] = sum + min(f[l][now - 1], f[l][now]);
			ans ^= f[l][r];
		}
	}
	printf("%d\n", ans);
	return 0;
} 
