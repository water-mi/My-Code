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

const int N = 2e4 + 10;
const ll Inf = (1ll << 60);
int n, L[N], R[N];
int a[N], b[N], c[N];
ll f[N][50][50];
template<typename T> inline void ChkMin(T &x, T y) { if(x > y) x = y; }

ll dp(int u, int x, int y) {
	if(u < 0) {//u是乡村则计算一下贡献
		int v = -u;
		return 1ll * c[v] * (a[v] + x) * (b[v] + y);
	} else {
		if(f[u][x][y] != -1) return f[u][x][y];
		f[u][x][y] = Inf;
		ChkMin(f[u][x][y], dp(L[u], x + 1, y) + dp(R[u], x, y));
		ChkMin(f[u][x][y], dp(L[u], x, y) + dp(R[u], x, y + 1));
		return f[u][x][y];
	}
}

int main () {
	freopen("road.in", "r", stdin);
	freopen("road.out", "w", stdout);
	read(n);
	for(int i = 1; i < n; ++i)
		read(L[i]), read(R[i]);
	for(int i = 1; i <= n; ++i)
		read(a[i]), read(b[i]), read(c[i]);
	memset(f, -1, sizeof f);
	printf("%lld\n", dp(1, 0, 0));
	return 0;
} 
