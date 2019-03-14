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

const int N = 1e2 + 10, _ = 4e6 + 10, Inf = 1e9 + 7;
int m, n, S, T, x[N][N], y[N][N], p[N][N], poi;
int cnt = 1, from[_], to[_], nxt[_], flow[_], cost[_];
inline void addEdge(int u, int v, int f, int c) {
	to[++cnt] = v, nxt[cnt] = from[u], from[u] = cnt, flow[cnt] = f, cost[cnt] = c;
	to[++cnt] = u, nxt[cnt] = from[v], from[v] = cnt, flow[cnt] = 0, cost[cnt] = -c;
}
inline void Init(int n) {
	T = n + 1, cnt = 1, memset(from, 0, sizeof(from[0]) * (T + 5));
}

int inc[_], dis[_], pre[_], inq[_]; queue<int> q;
bool spfa() {
	memset(inq, 0, sizeof (inq[0]) * (T + 5));
	std::fill(dis + 1, dis + T + 6, -Inf), dis[S] = 0, inc[S] = Inf;
	while(q.size()) q.pop(); q.push(S), inq[S] = 1;
	while(q.size()) {
		int u = q.front(); q.pop(); inq[u] = 0;
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
int maxflow, maxcost;
void update() {
	int x = T; maxflow += inc[T], maxcost += inc[T] * dis[T];
	while(x != S) {
		int i = pre[x]; x = to[i ^ 1];
		flow[i] -= inc[T], flow[i ^ 1] += inc[T];
	}
}

namespace Cpp1 {
	void Main() {
		int poi = ::poi; maxflow = 0, maxcost = 0;
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j < m + i; ++j)
				y[i][j] = ++poi;
		Init(poi);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j < m + i; ++j) {
				addEdge(x[i][j], y[i][j], 1, 0);
				if(i == 1) addEdge(S, x[i][j], 1, p[i][j]);
				if(i == n) addEdge(y[i][j], T, 1, 0);
				else {
					addEdge(y[i][j], x[i + 1][j], 1, p[i + 1][j]);
					addEdge(y[i][j], x[i + 1][j + 1], 1, p[i + 1][j + 1]);
				}
			}
		while(spfa()) update();
		printf("%d\n", maxcost);
	}
}
namespace Cpp2 {
	void Main() {
		maxflow = 0, maxcost = 0, Init(poi);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j < m + i; ++j) {
				if(i == 1) addEdge(S, x[i][j], 1, p[i][j]);
				if(i == n) addEdge(x[i][j], T, Inf, 0);
				else {
					addEdge(x[i][j], x[i + 1][j], 1, p[i + 1][j]);
					addEdge(x[i][j], x[i + 1][j + 1], 1, p[i + 1][j + 1]);
				}
			}
		while(spfa()) update();
		printf("%d\n", maxcost);
	}
}
namespace Cpp3 {
	void Main() {
		maxflow = 0, maxcost = 0, Init(poi);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j < m + i; ++j) {
				if(i == 1) addEdge(S, x[i][j], 1, p[i][j]);
				if(i == n) addEdge(x[i][j], T, Inf, 0);
				else {
					addEdge(x[i][j], x[i + 1][j], Inf, p[i + 1][j]);
					addEdge(x[i][j], x[i + 1][j + 1], Inf, p[i + 1][j + 1]);
				}
			}
		while(spfa()) update();
		printf("%d\n", maxcost);
	}
}

int main () {
	freopen("trape.in", "r", stdin);
	freopen("trape.out", "w", stdout);
	read(m), read(n);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j < m + i; ++j)
			x[i][j] = ++poi, read(p[i][j]);
	Cpp1::Main(), Cpp2::Main(), Cpp3::Main();
	return 0;
} 
