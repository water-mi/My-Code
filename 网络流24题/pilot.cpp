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

const int _ = 1e4 + 10, Inf = 1e9 + 7;
int n, m, S, T;
int cnt = 1, from[_], to[_ << 1], nxt[_ << 1], flow[_ << 1];
inline void addEdge(int u, int v, int f) {
	to[++cnt] = v, nxt[cnt] = from[u], from[u] = cnt, flow[cnt] = f;
	to[++cnt] = u, nxt[cnt] = from[v], from[v] = cnt, flow[cnt] = 0;
}

int maxflow, dep[_]; queue<int> q;
bool bfs() {
	memset(dep, 0, sizeof dep), dep[S] = 1;
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
		k = dinic(v, min(flow[i], rest)); if(!k) dep[v] = 0;
		flow[i] -= k, flow[i ^ 1] += k, rest -= k;
	}
	return __ - rest;
}

int main () {
	freopen("pilot.in", "r", stdin);
	freopen("pilot.out", "w", stdout);
	read(m), read(n), S = n + 1, T = S + 1;
	for(int i = 1; i <= m; ++i) addEdge(S, i, 1);
	for(int i = m + 1; i <= n; ++i) addEdge(i, T, 1);
	int u, v, st = cnt + 1;
	while(scanf("%d%d", &u, &v) != EOF) {
		if(u == -1 && v == -1) break;
		addEdge(u, v, 1);
	}
	int __;
	while(bfs())
		while(__ = dinic(S, Inf))
			maxflow += __;
	printf("%d\n", maxflow);
	for(int i = st; i <= cnt; i += 2)
		if(!flow[i]) printf("%d %d\n", to[i ^ 1], to[i]);
	return 0;
} 
