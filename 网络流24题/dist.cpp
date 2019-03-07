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

const int N = 2e2 + 10, M = 6e3 + 10, _ = 2e5 + 10, Inf = 1e9 + 7;
int n, m, S, T, x[N], y[N], poi;
int cnt = 1, from[_], to[_], nxt[_], flow[_];
inline void addEdge(int u, int v, int f) {
	to[++cnt] = v, nxt[cnt] = from[u], from[u] = cnt, flow[cnt] = f;
	to[++cnt] = u, nxt[cnt] = from[v], from[v] = cnt, flow[cnt] = 0;
}

int dep[_], maxflow; queue<int> q;
bool BFS() {
	memset(dep, 0, sizeof(int) * poi), dep[S] = 1;
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

int go[N], ind[N];
int main () {
	freopen("dist.in", "r", stdin);
	freopen("dist.out", "w", stdout);
	read(n), read(m), T = 2 * n + 1, poi = T + 10;
	for(int i = 1; i <= n; ++i) addEdge(S, i, 1);
	for(int i = 1; i <= n; ++i) addEdge(i + n, T, 1);
	for(int i = 1, u, v; i <= m; ++i)
		read(u), read(v), addEdge(u, v + n, 1);
	int __;
	while(BFS()) while(__ = dinic(S, Inf)) maxflow += __;
	for(int i = 1; i <= n; ++i)
	for(int u = 1; u <= n; ++u)
		for(int i = from[u]; i; i = nxt[i])
			if(!flow[i] && to[i] > n && to[i] < T)
				go[u] = to[i] - n, ++ind[to[i] - n];
	for(int i = 1, u; i <= n; ++i) {
		if(ind[i]) continue;
		printf("%d", u = i);
		while(go[u]) printf(" %d", u = go[u]);
		puts("");
	}
	printf("%d\n", n - maxflow);
	return 0;
} 
