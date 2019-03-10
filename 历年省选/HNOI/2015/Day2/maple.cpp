#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using std::min; using std::max;
using std::swap; using std::sort;
using std::queue;
typedef long long ll;

template<typename T>
void read(T &x) {
    int flag = 1; x = 0; char ch = getchar();
    while(ch < '0' || ch > '9') { if(ch == '-') flag = -flag; ch = getchar(); }
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int N = 1e5 + 10, M = 2e5 + 10, P = 1e9 + 7;
int n, m, a, b, ind[N], deg, f[N], u[M], v[M], tmp[N];
int cnt, from[N], to[M], nxt[M], vis[N];
inline void addEdge(int u, int v) {
	to[++cnt] = v, nxt[cnt] = from[u], from[u] = cnt;
}
int qpow(int a, int b) {
	int ret = 1;
	for(; b; a = 1ll * a * a % P, b >>= 1) if(b & 1) ret = 1ll * ret * a % P;
	return ret;
}
inline int inv(int x) { return qpow(x, P - 2); }

void dfs(int u) {
	vis[u] = 1;
	for(int i = from[u]; i; i = nxt[i])
		if(!vis[to[i]]) dfs(to[i]);
}

queue<int> q;
void dp(int s) {
	q.push(s), f[s] = inv(ind[s]);
	while(!q.empty()) {
		int u = q.front(); q.pop(); vis[u] = 1;
		for(int i = from[u]; i; i = nxt[i]) {
			int v = to[i]; if(vis[v]) continue;
			(f[v] += f[u]) %= P;
			if(!(--tmp[v])) f[v] = 1ll * f[v] * inv(ind[v]) % P, q.push(v);
		}
	}
}

int main () {
    freopen("maple.in", "r", stdin);
    freopen("maple.out", "w", stdout);
	read(n), read(m), read(a), read(b);
	deg = 1;
	for(int i = 1; i <= m; ++i) {
		read(u[i]), read(v[i]);
		addEdge(u[i], v[i]), ++ind[v[i]];
	}
	addEdge(a, b), ++ind[b], dfs(b);
	//预处理出b可以走到哪些点，方便拓扑序dp
	for(int i = 2; i <= n; ++i)
		deg = 1ll * deg * ind[i] % P;
	if(b == 1) { printf("%d\n", deg); return 0; }//记得特判!
	for(int i = 1; i <= m; ++i)
		if(vis[u[i]] && vis[v[i]])
			++tmp[v[i]];
	memset(vis, 0, sizeof vis), dp(b);
	printf("%lld\n", (1ll * deg + P - 1ll * deg * f[a] % P) % P);
	return 0;
} 
