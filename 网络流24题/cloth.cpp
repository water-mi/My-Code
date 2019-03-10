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

const int N = 2e3 + 10, _ = 4e6 + 10, Inf = 1e9 + 7;
int n, p, fd, fw, sd, sw, S, T, r[N];
int cnt = 1, from[_], to[_], nxt[_], flow[_], cost[_];
inline void addEdge(int u, int v, int f, int c) {
	to[++cnt] = v, nxt[cnt] = from[u], from[u] = cnt, flow[cnt] = f, cost[cnt] = c;
	to[++cnt] = u, nxt[cnt] = from[v], from[v] = cnt, flow[cnt] = 0, cost[cnt] = -c;
}

int inc[_], dis[_], inq[_], pre[_]; queue<int> q;
bool SPFA() {
	memset(inq, 0, sizeof(int) * (T + 5));
	std::fill(dis + 1, dis + T + 6, Inf);
	while(q.size()) q.pop();
	q.push(S), inc[S] = Inf, dis[S] = 0, inq[S] = 1;
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

int maxflow, mincost;
void update() {
	int x = T; maxflow += inc[T], mincost += inc[T] * dis[T];
	while(x != S) {
		int i = pre[x]; x = to[i ^ 1];
		flow[i] -= inc[T], flow[i ^ 1] += inc[T];
	}
}

int main () {
    freopen("cloth.in", "r", stdin);
    freopen("cloth.out", "w", stdout);
	read(n), read(p), read(fd), read(fw), read(sd), read(sw);
	T = 2 * n + 1;
	for(int i = 1; i <= n; ++i) {
		addEdge(S, i + n, Inf, p), read(r[i]);
		addEdge(S, i, r[i], 0), addEdge(i + n, T, r[i], 0);
		if(i < n) addEdge(i, i + 1, Inf, 0);
		if(i + fd <= n) addEdge(i, i + fd + n, Inf, fw);
		if(i + sd <= n) addEdge(i, i + sd + n, Inf, sw);
	}
	while(SPFA()) update();
	printf("%d\n", mincost);
    return 0; 
} 
