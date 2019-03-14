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

const int N = 20, _ = 4e6 + 10, Inf = 1e9 + 7;
int a, b, P, Q, S, T;
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

inline int getid(int x, int y) { return (x - 1) * Q + y; }
int main () {
	freopen("robot.in", "r", stdin);
	freopen("robot.out", "w", stdout);
	read(a), read(b), read(P), read(Q), ++P, ++Q;
	T = P * Q + 1; int k, x, y;
	for(int i = 1; i <= P; ++i)
		for(int j = 1; j < Q; ++j) {
			read(x); int u = getid(i, j), v = getid(i, j + 1);
			addEdge(u, v, 1, x), addEdge(u, v, Inf, 0);
		}
	for(int j = 1; j <= Q; ++j)
		for(int i = 1; i < P; ++i) {
			read(x); int u = getid(i, j), v = getid(i + 1, j);
			addEdge(u, v, 1, x), addEdge(u, v, Inf, 0);
		}
	for(int i = 1; i <= a; ++i) {
		read(k), read(x), read(y);
		addEdge(S, getid(x + 1, y + 1), k, 0);
	}
	for(int i = 1; i <= b; ++i) {
		read(k), read(x), read(y);
		addEdge(getid(x + 1, y + 1), T, k, 0);
	}
	while(spfa()) update(); printf("%d\n", maxcost);
	return 0;
} 
