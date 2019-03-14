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

const int N = 1e2 + 10, _ = 4e6 + 10, Inf = 1e9 + 7;
int n, a[N], ave, S, T;
int cnt = 1, from[_], to[_], nxt[_], flow[_], cost[_];
inline void addEdge(int u, int v, int f, int c) {
	to[++cnt] = v, nxt[cnt] = from[u], from[u] = cnt, flow[cnt] = f, cost[cnt] = c;
	to[++cnt] = u, nxt[cnt] = from[v], from[v] = cnt, flow[cnt] = 0, cost[cnt] = -c;
}

int maxflow, mincost; queue<int> q;
int dis[_], inc[_], inq[_], pre[_];
bool spfa() {
	fill(dis + 1, dis + T + 6, Inf), dis[S] = 0;
	while(q.size()) q.pop(); q.push(S), inq[S] = 1, inc[S] = Inf;
	while(q.size()) {
		int u = q.front(); q.pop(), inq[u] = 0;
		for(int i = from[u]; i; i = nxt[i]) {
			if(!flow[i]) continue;
			int v = to[i], w = dis[u] + cost[i];
			if(w < dis[v]) {
				dis[v] = w, pre[v] = i;
				inc[v] = min(inc[u], flow[i]);
				if(!inq[v]) q.push(v), inq[v] = 1;
			}
		}
	}
	return dis[T] < Inf;
}
void update() {
	int x = T; maxflow += inc[T], mincost += inc[T] * dis[T];
	while(x != S) {
		int i = pre[x]; x = to[i ^ 1];
		flow[i] -= inc[T], flow[i ^ 1] += inc[T];
	}
}

int main () {
	freopen("balance.in", "r", stdin);
	freopen("balance.out", "w", stdout);
	read(n), T = n + 1;
	for(int i = 1; i <= n; ++i) read(a[i]), ave += a[i];
	if(n == 1) return puts("0"), 0;
	if(n == 2) return printf("%d\n", abs(a[1] - a[2]) / 2), 0;
	ave /= n;
	for(int i = 1; i <= n; ++i)
		addEdge(S, i, a[i], 0), addEdge(i, T, ave, 0);
	for(int i = 1; i <= n; ++i)
		addEdge(i, i == n ? 1 : i + 1, Inf, 1),
		addEdge(i, i == 1 ? n : i - 1, Inf, 1);
	while(spfa()) update(); printf("%d\n", mincost);
	return 0;
} 
