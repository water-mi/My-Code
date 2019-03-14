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

const int N = 50, _ = 4e6 + 10, Inf = 1e9 + 7;
int car, P, Q, S, T, a[N][N];
int cnt = 1, from[_], to[_], nxt[_], flow[_], cost[_];
inline void addEdge(int u, int v, int f, int c) {
	to[++cnt] = v, nxt[cnt] = from[u], from[u] = cnt, flow[cnt] = f, cost[cnt] = c;
	to[++cnt] = u, nxt[cnt] = from[v], from[v] = cnt, flow[cnt] = 0, cost[cnt] = -c;
}

int maxflow, maxcost; queue<int> q;
int dis[_], inc[_], inq[_], pre[_];
bool spfa() {
	fill(dis + 1, dis + T + 6, -Inf), dis[S] = 0;
	while(q.size()) q.pop(); q.push(S), inq[S] = 1, inc[S] = Inf;
	while(q.size()) {
		int u = q.front(); q.pop(), inq[u] = 0;
		for(int i = from[u]; i; i = nxt[i]) {
			if(!flow[i]) continue;
			int v = to[i], w = dis[u] + cost[i];
			if(w > dis[v]) {
				dis[v] = w, pre[v] = i;
				inc[v] = min(inc[u], flow[i]);
				if(!inq[v]) q.push(v), inq[v] = 1;
			}
		}
	}
	return dis[T] > -Inf;
}
void update() {
	int x = T; maxflow += inc[T], maxcost += inc[T] * dis[T];
	while(x != S) {
		int i = pre[x]; x = to[i ^ 1];
		flow[i] -= inc[T], flow[i ^ 1] += inc[T];
	}
}

inline int getid(int x, int y) { return (x - 1) * P + y; }
int k, poi; bool flag;
void findPath(int x, int y) {
	int u = getid(x, y);
	if(flag || u == getid(Q, P)) { flag = 1; return ; }
	for(int i = from[u + poi]; i; i = nxt[i]) {
		int v = to[i]; if(v == u) continue;
		if(flag) return ;
		if(v >= 1 && v <= poi && flow[i ^ 1]) {
			--flow[i ^ 1];
			int ny = v % P, nx = (v - ny) / P + 1;
			if(v == u + 1) printf("%d 1\n", k);
			else printf("%d 0\n", k);
			findPath(nx, ny);
		}
	}
}

int main () {
	freopen("mars.in", "r", stdin);
	freopen("mars.out", "w", stdout);
	read(car), read(P), read(Q);
	poi = Q * P, T = 2 * poi + 1;
	for(int i = 1; i <= Q; ++i)
		for(int j = 1; j <= P; ++j) {
			read(a[i][j]); int x = getid(i, j);
			if(a[i][j] == 1) continue;
			addEdge(x, x + poi, Inf, 0);
			if(a[i][j] == 2) addEdge(x, x + poi, 1, 1);
		}
	addEdge(S, getid(1, 1), car, 0), addEdge(getid(Q, P) + poi, T, car, 0);
	for(int i = 1; i <= Q; ++i)
		for(int j = 1; j <= P; ++j) {
			if(i < Q) addEdge(getid(i, j) + poi, getid(i + 1, j), Inf, 0);
			if(j < P) addEdge(getid(i, j) + poi, getid(i, j + 1), Inf, 0);
		}
	while(spfa()) update();
	for(k = 1; k <= maxflow; ++k) flag = 0, findPath(1, 1);
	return 0;
} 
