#include <queue>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using std::min; using std::max;
using std::swap; using std::greater;
using std::vector; using std::pair;
using std::priority_queue;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<pii, int> node;

template<typename T>
void read(T &x) {
    int flag = 1; x = 0; char ch = getchar();
    while(ch < '0' || ch > '9') { if(ch == '-') flag = -flag; ch = getchar(); }
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int N = 1e5 + 10, M = 2e5 + 10, Inf = 1 << 30;
int n, m, L, sp[M];
int u[M], v[M], w[M], stop[M];

int cnt, from[N], nxt[M];
inline void addEdge (int u) { nxt[++cnt] = from[u], from[u] = cnt; }

pii dis[2][N];
priority_queue< node, vector<node>, greater<node> > q;
void Dijkstra (int s, int t, int opt) {
	q.push((node){dis[opt][s], s});
	for(int i = 1, x = sp[i]; i <= L; x = sp[++i])
		q.push((node){dis[opt][v[x]], v[x]});
	while(q.size()) {
		node x = q.top(); q.pop();
		if(x.first != dis[opt][x.second] || x.second == t) continue;
		for(int i = from[x.second]; i; i = nxt[i]) {
			if(stop[i]) continue;
			int y = v[i]; pii z = x.first; z.first += w[i];
			if(z < dis[opt][y]) dis[opt][y] = z, q.push((node){z, y});
		}
	}
}
//建最短路图并找出最远的i和j

int t[N << 2];
void build(int o = 1, int l = 1, int r = L) {
	t[o] = Inf; if(l == r) return ;
	int mid = (l + r) >> 1, lc = o << 1, rc = lc | 1;
	build(lc, l, mid), build(rc, mid + 1, r);
}
void modify(int ml, int mr, int p, int o = 1, int l = 1, int r = L) {
	if(l >= ml && r <= mr) { t[o] = min(t[o], p); return ; }
	int mid = (l + r) >> 1, lc = o << 1, rc = lc | 1;
	if(ml <= mid) modify(ml, mr, p, lc, l, mid);
	if(mr > mid) modify(ml, mr, p, rc, mid + 1, r);
}
int query(int pos, int o = 1, int l = 1, int r = L) {
	if(l == r && l == pos) return t[o];
	int mid = (l + r) >> 1, lc = o << 1, rc = lc | 1;
	if(pos <= mid) return min(t[o], query(pos, lc, l, mid));
	else return min(t[o], query(pos, rc, mid + 1, r));
}
//线段树标记永久化维护区间最小值。

int main () {
    freopen("road.in", "r", stdin);
    freopen("road.out", "w", stdout);
	read(n), read(m), read(L);
	for(int i = 1; i <= m; ++i)
		read(u[i]), read(v[i]), read(w[i]), addEdge(u[i]);
	for(int i = 1; i <= n; ++i)
		dis[0][i] = dis[1][i] = (pii){Inf, 0};
	dis[0][1] = dis[1][n] = (pii){0, 0};
	for(int i = 1, x; i <= L; ++i) {
		read(x), stop[x] = 1, sp[i] = x;
		dis[0][v[x]].first = dis[0][u[x]].first + w[x];
		dis[0][v[x]].second = i, dis[1][v[x]].second = -i;
	}//取负数才能在反图上跑出最大的j
	for(int i = L, x = sp[i]; i >= 1; x = sp[--i])
		dis[1][u[x]].first = dis[1][v[x]].first + w[x];
	//预处理出最短路
	Dijkstra(1, n, 0), memset(from, 0, sizeof from), cnt = 0;
	for(int i = 1; i <= m; ++i) swap(u[i], v[i]), addEdge(u[i]);
	//建反图
	Dijkstra(n, 1, 1); for(int i = 1; i <= m; ++i) swap(u[i], v[i]);
	for(int i = 1; i <= n; ++i) dis[1][i].second *= -1;
	build();
	for(int i = 1; i <= m; ++i) {
		if(stop[i]) continue;
		pii x = dis[0][u[i]], y = dis[1][v[i]];
		if(x.second >= y.second) continue;
		modify(x.second + 1, y.second, x.first + y.first + w[i]);
	}//根据最远的i和j来更新
	for(int i = 1; i <= L; ++i) {
		int ret = query(i); 
		printf("%d\n", ret >= Inf ? -1 : ret);
	}
	return 0;
} 
