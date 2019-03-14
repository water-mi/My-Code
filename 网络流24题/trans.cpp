#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using std::queue; using std::fill;
using std::min; using std::max;
using std::swap; using std::sort;
typedef long long ll;

template<typename T>
void read(T &x) {
	int flag = 1; x = 0; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') flag = -flag; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int _ = 4e6 + 10, N = 1e2 + 10, Inf = 1e9 + 7;
int n, m, S, T, a[N], b[N], c[N][N];
int cnt = 1, from[_], to[_], nxt[_], flow[_], cost[_];
inline void addEdge(int u, int v, int f, int c) {
	to[++cnt] = v, nxt[cnt] = from[u], from[u] = cnt, flow[cnt] = f, cost[cnt] = c;
	to[++cnt] = u, nxt[cnt] = from[v], from[v] = cnt, flow[cnt] = 0, cost[cnt] = -c;
}

int maxflow, totcost; queue<int> q;
int inc[_], dis[_], inq[_], pre[_], opt;
bool spfa() {
	fill(dis + 1, dis + T + 6, opt * Inf), dis[S] = 0;
	while(q.size()) q.pop(); q.push(S), inq[S] = 1, inc[S] = Inf;
	while(q.size()) {
		int u = q.front(); q.pop(), inq[u] = 0;
		for(int i = from[u]; i; i = nxt[i]) {
			if(!flow[i]) continue;
			int v = to[i], w = dis[u] + cost[i];
			if(w * opt < dis[v] * opt) {
				dis[v] = w, pre[v] = i;
				inc[v] = min(inc[u], flow[i]);
				if(!inq[v]) q.push(v), inq[v] = 1;
			}
		}
	}
	return opt * dis[T] < opt * (opt * Inf);
}
void update() {
	int x = T; maxflow += inc[T], totcost += inc[T] * dis[T];
	while(x != S) {
		int i = pre[x]; x = to[i ^ 1];
		flow[i] -= inc[T], flow[i ^ 1] += inc[T];
	}
}

void doit() {
	cnt = 1, memset(from, 0, sizeof(from[0]) * (T + 5));
	for(int i = 1; i <= m; ++i) addEdge(S, i, a[i], 0);
	for(int i = 1; i <= n; ++i) addEdge(i + m, T, b[i], 0);
	for(int i = 1; i <= m; ++i)
		for(int j = 1; j <= n; ++j)
			addEdge(i, j + m, Inf, c[i][j]);
	maxflow = 0, totcost = 0;
	while(spfa()) update();
	printf("%d\n", totcost);
}

int main () {
	freopen("trans.in", "r", stdin);
	freopen("trans.out", "w", stdout);
	read(m), read(n), T = m + n + 1;
	for(int i = 1; i <= m; ++i) read(a[i]);
	for(int i = 1; i <= n; ++i) read(b[i]);
	for(int i = 1; i <= m; ++i)
		for(int j = 1; j <= n; ++j)
			read(c[i][j]);
	opt = 1, doit(); opt = -1, doit();
	return 0;
} 
