#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using std::queue; using std::vector;
using std::min; using std::max;
using std::swap; using std::sort;
typedef long long ll;

template<typename T>
void read(T &x) {
	int flag = 1; x = 0; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') flag = -flag; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int _ = 4e6 + 10, Inf = 1e9 + 7;
int n, poi, S, T = _ - 10, id[2][_], go[_], ind[_];
int cnt = 1, from[_], to[_], nxt[_], flow[_], tag[_], ban[_];
inline void addEdge(int u, int v, int f) {
	to[++cnt] = v, nxt[cnt] = from[u], from[u] = cnt, flow[cnt] = f, tag[cnt] = 1;
	to[++cnt] = u, nxt[cnt] = from[v], from[v] = cnt, flow[cnt] = 0, tag[cnt] = 0;
}

int dep[_], maxflow; queue<int> q;
bool bfs() {
	memset(dep, 0, sizeof (int) * (poi + 5)), dep[T] = 0, dep[S] = 1;
	while(q.size()) q.pop(); q.push(S);
	while(q.size()) {
		int u = q.front(); q.pop();
		for(int i = from[u]; i; i = nxt[i]) {
			int v = to[i]; if(!flow[i] || dep[v] || ban[i]) continue;
			dep[v] = dep[u] + 1, q.push(v);
			if(v == T) return 1;
		}
	}
	return 0;
}

int dinic(int u, int __) {
	if(u == T) return __;
	int rest = __, k;
	for(int i = from[u]; i; i = nxt[i] ) {
		int v = to[i]; if(!flow[i] || dep[v] != dep[u] + 1 || ban[i]) continue;
		k = dinic(v, min(flow[i], rest)); if(!k) dep[v] = 0;
		flow[i] -= k, flow[i ^ 1] += k, rest -= k;
	}
	return __ - rest;
}

int main () {
	freopen("ball.in", "r", stdin);
	freopen("ball.out", "w", stdout);
	read(n); int now = 0, __;
	while(++now) {
		id[0][now] = ++poi, id[1][now] = ++poi;
		addEdge(S, id[0][now], 1), addEdge(id[1][now], T, 1);
		for(int i = 1; i < now; ++i) {
			int sqr = floor(sqrt(i + now));
			if(sqr * sqr != i + now) continue;
			addEdge(id[0][i], id[1][now], 1);
		}
		while(bfs()) while(__ = dinic(S, Inf)) maxflow += __;
		if(now - maxflow > n) break;
	}
	for(int i = from[id[1][now]]; i; i = nxt[i]) ban[i] = ban[i ^ 1] = 1;
	for(int i = from[id[0][now]]; i; i = nxt[i]) ban[i] = ban[i ^ 1] = 1;
	for(int i = 2; i <= cnt; i += 2) flow[i] = 1, flow[i ^ 1] = 0;
	printf("%d\n", --now), maxflow = 0;
	while(bfs()) while(__ = dinic(S, Inf)) maxflow += __;
	for(int u = 1; u <= now; ++u)
		for(int i = from[id[0][u]]; i; i = nxt[i]) {
			int v = to[i] / 2;
			if(!flow[i] && (v * 2 == to[i]) && v > 0 && v <= now)
				go[u] = v, ++ind[v];
		}
	for(int i = 1, u; i <= now; ++i) {
		if(ind[i]) continue;
		printf("%d", u = i);
		while(go[u]) printf(" %d", u = go[u]);
		puts("");
	}
	return 0;
} 
