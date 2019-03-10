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

const int _ = 1e5 + 10, Inf = 1e9 + 7;
int n, m, S, T, poi, r[_], c[_], tot, __;
int cnt = 1, from[_], to[_], nxt[_], flow[_];
inline void addEdge(int u, int v, int f) {
	to[++cnt] = v, nxt[cnt] = from[u], from[u] = cnt, flow[cnt] = f;
	to[++cnt] = u, nxt[cnt] = from[v], from[v] = cnt, flow[cnt] = 0;
}

int dep[_], maxflow; queue<int> q;
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
		k = dinic(v, min(rest, flow[i])); if(!k) dep[v] = 0;
		flow[i] -= k, flow[i ^ 1] += k, rest -= k;
	}
	return __ - rest;
}

int main () {
	freopen("table.in", "r", stdin);
	freopen("table.out", "w", stdout);
	read(m), read(n), T = n * m + 1;
	for(int i = 1; i <= m; ++i) {
		read(r[i]), addEdge(S, i, r[i]), tot += r[i];
		for(int j = 1; j <= n; ++j) addEdge(i, j + m, 1);
	}
	for(int i = 1; i <= n; ++i) read(c[i]), addEdge(i + m, T, c[i]);
	while(BFS()) while(__ = dinic(S, Inf)) maxflow += __;
	if(maxflow == tot) {
		puts("1");
		for(int u = 1; u <= m; ++u) {
			for(int i = from[u]; i; i = nxt[i]) {
				int v = to[i] - m; if(flow[i]) continue;
				if(v >= 1 && v <= n) printf("%d ", v);
			}
			puts("");
		}
	} else puts("0");
	return 0;
} 
