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

const int N = 1e3 + 10, _ = 4e6 + 10, Inf = 1e9 + 7;
int k, n, S, T, t[N], p[N];
int cnt = 1, from[_], to[_], nxt[_], flow[_];
inline void addEdge(int u, int v, int f) {
	to[++cnt] = v, nxt[cnt] = from[u], from[u] = cnt, flow[cnt] = f;
	to[++cnt] = u, nxt[cnt] = from[v], from[v] = cnt, flow[cnt] = 0;
}

int dep[_]; queue<int> q;
bool BFS() {
	memset(dep, 0, sizeof(int) * (T + 5)), dep[S] = 1;
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

int maxflow, tot, __;
int main () {
	freopen("test.in", "r", stdin);
	freopen("test.out", "w", stdout);
	read(k), read(n), T = k + n + 1;
	for(int i = 1; i <= k; ++i)
		read(t[i]), addEdge(i + n, T, t[i]), tot += t[i];
	for(int i = 1; i <= n; ++i) {
		addEdge(S, i, 1), read(p[i]);
		for(int j = 1, x; j <= p[i]; ++j)
			read(x), addEdge(i, x + n, 1);
	}
	while(BFS()) while(__ = dinic(S, Inf)) maxflow += __;
	if(maxflow != tot) puts("No Solution!");
	else
		for(int i = 1; i <= k; ++i) {
			printf("%d:", i);
			int u = i + n;
			for(int e = from[u]; e; e = nxt[e]) {
				int v = to[e];
				if(v >= 1 && v <= n && !flow[e ^ 1])
					printf(" %d", v);
			}
			puts("");
		}
	return 0;
} 
