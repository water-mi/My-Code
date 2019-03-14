#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using std::queue; using std::fill;
using std::unique; using std::lower_bound;
using std::min; using std::max;
using std::swap; using std::sort;
typedef long long ll;

template<typename T>
void read(T &x) {
	int flag = 1; x = 0; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') flag = -flag; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int N = 1e4 + 10, _ = 4e6 + 10, Inf = 1e9 + 7;
int n, m, k, S, T, l[N], r[N], c[N], lsh[N];
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

inline ll sqr(int x) { return 1ll * x * x; }
int main () {
	freopen("segment.in", "r", stdin);
	freopen("segment.out", "w", stdout);
	read(n), read(k); int Y1, Y2;
	for(int i = 1; i <= n; ++i) {
		read(l[i]), read(Y1), read(r[i]), read(Y2);
		if(l[i] > r[i]) swap(l[i], r[i]);
		c[i] = floor(sqrt(sqr(r[i] - l[i]) + sqr(Y2 - Y1)));
		l[i] <<= 1, r[i] <<= 1;
		if(l[i] == r[i]) r[i] |= 1; else l[i] |= 1;
		lsh[++m] = l[i], lsh[++m] = r[i];
	}
	sort(lsh + 1, lsh + m + 1);
	m = unique(lsh + 1, lsh + m + 1) - lsh - 1;
	for(int i = 1; i <= n; ++i) {
		l[i] = lower_bound(lsh + 1, lsh + m + 1, l[i]) - lsh;
		r[i] = lower_bound(lsh + 1, lsh + m + 1, r[i]) - lsh;
		addEdge(l[i], r[i], 1, c[i]);
	}
	T = m + 1, addEdge(S, 1, k, 0), addEdge(m, T, k, 0);
	for(int i = 1; i < m; ++i) addEdge(i, i + 1, k, 0);
	while(spfa()) update(); printf("%d\n", maxcost);
	return 0;
} 
