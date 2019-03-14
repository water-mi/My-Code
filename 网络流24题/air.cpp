#include <map>
#include <queue>
#include <cmath>
#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using std::string;
using std::cin; using std::cout;
using std::map; using std::queue;
using std::min; using std::max;
using std::swap; using std::sort;
typedef long long ll;

const int N = 1e2 + 10, _ = 4e6 + 10, Inf = 1e9 + 7;
int n, m, S, T; string city[N]; map<string, int> M;
int cnt = 1, from[_], to[_], nxt[_], flow[_], cost[_]; bool vis[N];
inline void addEdge(int u, int v, int f, int c) {
	to[++cnt] = v, nxt[cnt] = from[u], from[u] = cnt, flow[cnt] = f, cost[cnt] = c;
	to[++cnt] = u, nxt[cnt] = from[v], from[v] = cnt, flow[cnt] = 0, cost[cnt] = -c;
}

int inq[_], dis[_], inc[_], pre[_]; queue<int> q;
bool spfa() {
	memset(inq, 0, sizeof(inq[0]) * (T + 5));
	std::fill(dis + 1, dis + T + 6, -Inf), dis[S] = 0, inc[S] = Inf;
	while(q.size()) q.pop(); q.push(S), inq[S] = 1;
	while(q.size()) {
		int u = q.front(); q.pop(), inq[u] = 0;
		for(int i = from[u]; i; i = nxt[i]) {
			if(!flow[i]) continue;
			int v = to[i], w = dis[u] + cost[i];
			if(dis[v] < w) {
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

int main () {
	freopen("air.in", "r", stdin);
	freopen("air.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	cin >> n >> m, T = 2 * n + 1;
	for(int i = 1; i <= n; ++i) {
		cin >> city[i], M[city[i]] = i;
		int f = 1; if(i == 1 || i == n)  ++f;
		addEdge(i, i + n, f, 1);
	}
	string u, v;
	for(int i = 1; i <= m; ++i)
		cin >> u >> v, addEdge(M[u] + n, M[v], 1, 0);
	addEdge(S, 1, 2, 0), addEdge(n + n, T, 2, 0);
	while(spfa()) update();
	if(!maxcost) return puts("No Solution!"), 0;
	if(maxcost != 2) maxcost = maxcost - 1 - (n != 1);
	cout << maxcost << '\n';
	int x = 1;
	while(x != n && !vis[x]) {
		vis[x] = 1, cout << city[x] << '\n';
		for(int i = from[x + n]; i; i = nxt[i]) {
			if(!flow[i] && to[i] >= 1 && to[i] <= n && !vis[to[i]]) {
				x = to[i]; break; 
			}
		}
	}
	while(x != 1 && !vis[x]) {
		vis[x] = 1, cout << city[x] << '\n';
		for(int i = from[x]; i; i = nxt[i])
			if(!flow[i ^ 1] && to[i] - n >= 1 && to[i] - n <= n)
				if(!vis[to[i] - n]) { x = to[i] - n; break; }
	}
	cout << city[1] << '\n';
	return 0;
} 
