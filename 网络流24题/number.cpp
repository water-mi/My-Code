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
const int dx[5] = {0, 0, 0, 1, -1}, dy[5] = {0, 1, -1, 0, 0};
int n, m, S, T;
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
		k = dinic(v, min(rest, flow[i])); if(!k) dep[v] = 0;
		flow[i] -= k, flow[i ^ 1] += k, rest -= k;
	}
	return __ - rest;
}

int ret, __;
inline int getid(int i, int j) { return (i - 1) * m + j; }
int main () {
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);
	read(n), read(m), T = n * m + 1;
	for(int i = 1, col; i <= n; ++i) {
		col = i % 2;
		for(int j = 1, x; j <= m; ++j) {
			read(x), col = !col, ret += x;
			if(col) addEdge(S, getid(i, j), x);
			else addEdge(getid(i, j), T, x);
			for(int k = 1; k <= 4; ++k) {
				int nx = i + dx[k], ny = j + dy[k];
				if(nx < 1 || ny < 1 || nx > n || ny > m) continue;
				if(col) addEdge(getid(i, j), getid(nx, ny), Inf);
			}
		}
	}
	while(BFS()) while(__ = dinic(S, Inf)) ret -= __;
	printf("%d\n", ret);
	return 0;
} 
