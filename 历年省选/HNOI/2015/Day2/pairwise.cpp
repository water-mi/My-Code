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

const int N = 1e2 + 10, P = 1e9 + 7;
int n, m, C[N][N], fa[N], bel[N], ind[N], f[N][N], siz[N], g[N];
bool isroot[N];
int cnt, from[N], to[N << 1], nxt[N << 1];
inline void addEdge(int u, int v) {
	to[++cnt] = v, nxt[cnt] = from[u], from[u] = cnt;
}
struct Node { int x, y; char r; } p[N];
int find(int x) { return fa[x] == x ? x : (fa[x] = find(fa[x])); }
bool unionn(int x, int y) {
	int fx = find(x), fy = find(y);
	if(fx == fy) return 1;
	fa[fx] = fy; return 0;
}

void dfs(int u, int fa) {
	siz[u] = f[u][1] = 1;
	for(int e = from[u]; e; e = nxt[e]) {
		int v = to[e]; if(v == fa) continue;
		dfs(v, u);
		for(int i = 1; i <= n; ++i) g[i] = 0;
		for(int i = 1; i <= siz[u] + siz[v]; ++i)
			for(int j = 1; j <= siz[u]; ++j)
				for(int k = 1; k <= siz[v]; ++k) {
					int x = k - i + j; if(x < 0) continue;
					(g[i] += 1ll * f[u][j] * f[v][k] % P *
					 C[i - 1][j - 1] % P * C[j - 1][x] % P) %= P;
				}
		siz[u] += siz[v];
		for(int i = 1; i <= siz[u]; ++i) f[u][i] = g[i];
	}
}

int main () {
    freopen("pairwise.in", "r", stdin);
    freopen("pairwise.out", "w", stdout);
	read(n), read(m), C[0][0] = 1;
	for(int i = 1; i <= 100; ++i) {
		C[i][0] = C[i][i] = 1;
		for(int j = 1; j < i; ++j)
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P; 
	}
	for(int i = 1; i <= n; ++i) fa[i] = i;
	for(int i = 1; i <= m; ++i) {
		scanf("%d %c%d", &p[i].x, &p[i].r, &p[i].y);
		if(p[i].r == '=') unionn(p[i].x, p[i].y);
	}
	for(int i = 1; i <= n; ++i)
		bel[i] = find(i), isroot[bel[i]] = 1, fa[i] = i;
	for(int i = 1; i <= m; ++i)
		if(p[i].r == '<') {
			addEdge(bel[p[i].x], bel[p[i].y]), addEdge(bel[p[i].y], bel[p[i].x]);
			++ind[bel[p[i].y]];
			if(unionn(bel[p[i].x], bel[p[i].y])) { puts("0"); return 0; }
		}
	for(int i = 1; i <= n; ++i)
		if(!ind[i] && isroot[i])
			addEdge(n + 1, i), addEdge(i, n + 1);
	int ret = 0; dfs(n + 1, 0);
	for(int i = 1; i <= siz[n + 1]; ++i)
		(ret += f[n + 1][i]) %= P;
	printf("%d\n", ret);
	return 0;
} 
