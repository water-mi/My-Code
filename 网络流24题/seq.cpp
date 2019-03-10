#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using std::upper_bound; using std::queue;
using std::min; using std::max;
using std::swap; using std::sort;
typedef long long ll;

template<typename T>
void read(T &x) {
	int flag = 1; x = 0; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') flag = -flag; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int N = 5e2 + 10, _ = 4e6 + 10, Inf = 1e9 + 7;
int n, m, x[N], f[N], S, T;
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

int ans1, ans2, __;
int main () {
	freopen("seq.in", "r", stdin);
	freopen("seq.out", "w", stdout);
	read(n), T = 2 * n + 1;
	if(n == 1) return puts("1\n1\n1"), 0;
	for(int i = 1; i <= n; ++i) read(x[i]);
	for(int i = n; i >= 1; --i) {
		f[i] = 1, addEdge(i, i + n, 1);
		for(int j = i + 1; j <= n; ++j)
			if(x[j] >= x[i]) f[i] = max(f[i], f[j] + 1);
		m = max(m, f[i]);
	}
	for(int i = 1; i <= n; ++i) {
		if(f[i] == m) addEdge(S, i, 1);
		if(f[i] == 1) addEdge(i + n, T, 1);
		for(int j = i + 1; j <= n; ++j)
			if(x[j] >= x[i] && f[i] == f[j] + 1)
				addEdge(i + n, j, 1);
	}
	while(BFS()) while(__ = dinic(S, Inf)) ans1 += __;
	for(int i = 2; i <= cnt; i += 2) {
		flow[i] = 1, flow[i ^ 1] = 0;
		if(to[i ^ 1] == 1 && to[i] == n + 1) flow[i] = Inf;
		if(to[i ^ 1] == n && to[i] == n + n) flow[i] = Inf;
		if(to[i ^ 1] == n + n && to[i] == T) flow[i] = Inf;
		if(to[i ^ 1] == S && to[i] == 1) flow[i] = Inf;
	}
	while(BFS()) while(__ = dinic(S, Inf)) ans2 += __;
	printf("%d\n%d\n%d\n", m, ans1, ans2);
	return 0;
} 
