#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using std::queue;
using std::min; using std::max;
using std::swap; using std::sort;
typedef long long ll;

template<typename T>
void read(T &x) {
	int flag = 1; x = 0; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') flag = -flag; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int N = 1e2 + 10, _ = 4e6 + 10, Inf = 1e9 + 7;
int n, m, k, S, T = _ - 10, poi;
int cnt = 1, from[_], to[_], nxt[_], flow[_];
inline void addEdge(int u, int v, int f) {
	to[++cnt] = v, nxt[cnt] = from[u], from[u] = cnt, flow[cnt] = f;
	to[++cnt] = u, nxt[cnt] = from[v], from[v] = cnt, flow[cnt] = 0;
}

int dep[_], tim; queue<int> q;
bool bfs() {
	memset(dep, 0, sizeof(dep[0]) * ((tim + 1) * n + 5)), dep[T] = 0, dep[S] = 1;
	while(q.size()) q.pop(); q.push(S);
	while(q.size()) {
		int u = q.front(); q.pop();
		for(int i = from[u]; i; i = nxt[i]) {
			int v = to[i]; if(!flow[i] || dep[v]) continue;
			dep[v] = dep[u] + 1, q.push(v);
			if(v == T) return 1;
		}
	}
	return 0;
}
int dinic(int u, int __) {
	if(u == T) return __;
	int rest = __, k;
	for(int i = from[u]; i; i = nxt[i]) {
		int v = to[i]; if(!flow[i] || dep[v] != dep[u] + 1) continue;
		k = dinic(v, min(rest, flow[i])); if(!k) dep[v] = 0;
		flow[i] -= k, flow[i ^ 1] += k, rest -= k;
	}
	return __ - rest;
}

int ret, maxflow, __;
int h[N], siz[N], go[N][N];
int main () {
	freopen("galaxy.in", "r", stdin);
	freopen("galaxy.out", "w", stdout);
	read(n), read(m), read(k), n += 2;
	for(int i = 1; i <= m; ++i) {
		read(h[i]), read(siz[i]);
		for(int j = 0; j < siz[i]; ++j)
			read(go[i][j]), go[i][j] += 2;
	}
	addEdge(S, 2, Inf), addEdge(1, T, Inf);
	while(++tim <= 2000) {
		addEdge(S, tim * n + 2, Inf);
		addEdge(tim * n + 1, T, Inf);
		for(int i = 1; i <= n; ++i)
			addEdge((tim - 1) * n + i, tim * n + i, Inf);
		for(int i = 1; i <= m; ++i) {
			int x = go[i][(tim - 1) % siz[i]];
			int y = go[i][tim % siz[i]];
			addEdge((tim - 1) * n + x, tim * n + y, h[i]);
		}
		while(bfs()) while(__ = dinic(S, Inf)) maxflow += __;
		if(maxflow >= k) { ret = tim; break; }
	}
	printf("%d\n", ret);
	return 0;
} 
