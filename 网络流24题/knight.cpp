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

const int N = 2e2 + 10, _ = 4e6 + 10, Inf = 1e9 + 7;
const int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
const int dy[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int n, m, S, T; bool stop[N][N];
int cnt = 1, from[_], to[_], nxt[_], flow[_], cur[_];
inline void addEdge(int u, int v, int f) {
	to[++cnt] = v, nxt[cnt] = from[u], from[u] = cnt, flow[cnt] = f;
	to[++cnt] = u, nxt[cnt] = from[v], from[v] = cnt, flow[cnt] = 0;
}

int dep[_], maxflow; queue<int> q;
bool bfs() {
	memset(dep, 0, sizeof(dep[0]) * (T + 5)), dep[S] = 1;
	memcpy(cur, from, sizeof(from[0]) * (T + 5));
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
	for(int &i = cur[u]; i; i = nxt[i]) {
		int v = to[i]; if(!flow[i] || dep[v] != dep[u] + 1) continue;
		k = dinic(v, min(flow[i], rest));
		flow[i] -= k, flow[i ^ 1] += k, rest -= k; 
	}
	return __ - rest;
}

inline int getid(int x, int y) { return (x - 1) * n + y; }
int main () {
	freopen("knight.in", "r", stdin);
	freopen("knight.out", "w", stdout);
	read(n), read(m); int __, col;
	T = n * n + 1;
	for(int i = 1, x, y; i <= m; ++i)
		read(x), read(y), stop[x][y] = 1;
	for(int i = 1; i <= n; ++i) {
		col = i % 2;
		for(int j = 1; j <= n; ++j) {
			col = !col;
			if(stop[i][j]) continue; ++maxflow;
			if(col) addEdge(S, getid(i, j), 1);
			else addEdge(getid(i, j), T, 1);
			for(int k = 0; k < 8; ++k) {
				int nx = i + dx[k], ny = j + dy[k];
				if(nx < 1 || nx > n || ny < 1 || ny > n || stop[nx][ny]) continue;
				if(col) addEdge(getid(i, j), getid(nx, ny), Inf);
			}
		}
	}
	while(bfs()) while(__ = dinic(S, Inf)) maxflow -= __;
	printf("%d\n", maxflow);
	return 0;
} 
