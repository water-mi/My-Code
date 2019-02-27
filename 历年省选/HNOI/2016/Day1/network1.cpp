#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using std::priority_queue;
using std::min; using std::max;
using std::swap; using std::sort;
typedef long long ll;

template<typename T>
void read(T &x) {
	int flag = 1; x = 0; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') flag = -flag; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int N = 1e5 + 10, M = 2e5 + 10;
int n, m;
struct Heap {
	priority_queue<int> q1, q2;
	inline void insert(int x) { q1.push(x); }
	inline void erase(int x) { q2.push(x); }
	inline int top() {
		while(q2.size() && q1.top() == q2.top()) q1.pop(), q2.pop();
		return q1.size() ? q1.top() : -1;
	}
};//可删堆
struct Range { int l, r; } st[N]; int t;
inline bool operator < (const Range &a, const Range &b) {
	return a.l == b.l ? a.r < b.r : a.l < b.l;
}

int cnt, from[N], to[N << 1], nxt[N << 1];
inline void addEdge(int u, int v) {
	to[++cnt] = v, nxt[cnt] = from[u], from[u] = cnt;
}
struct Dist { int x, y, k; } d[M];

int fa[N], son[N], siz[N], top[N], dep[N], dfn[N], tim;
void dfs(int u) {
	siz[u] = 1, dep[u] = dep[fa[u]] + 1;
	for(int i = from[u]; i; i = nxt[i]) {
		int v = to[i]; if(v == fa[u]) continue;
		fa[v] = u, dfs(v), siz[u] += siz[v];
		if(siz[v] > siz[son[u]]) son[u] = v;
	}
}
void dfs(int u, int t) {
	dfn[u] = ++tim, top[u] = t;
	if(son[u]) dfs(son[u], t);
	for(int i = from[u]; i; i = nxt[i])
		if(to[i] != fa[u] && to[i] != son[u])
			dfs(to[i], to[i]);
}
//树链剖分

Heap rt[N << 2];
void update(int gx, int ul, int ur, int k, int o = 1, int l = 1, int r = tim) {
	if(ul == l && ur == r) {
		if(gx) rt[o].insert(k);
		else rt[o].erase(k);
		return ;
	}
	int mid = (l + r) >> 1, lc = o << 1, rc = lc | 1;
	if(ur <= mid) update(gx, ul, ur, k, lc, l, mid);
	else if(ul > mid) update(gx, ul, ur, k, rc, mid + 1, r);
	else {
		update(gx, ul, mid, k, lc, l, mid);
		update(gx, mid + 1, ur, k, rc, mid + 1, r);
	}
}
int query(int pos, int o = 1, int l = 1, int r = tim) {
	if(l == r) return rt[o].top();
	int mid = (l + r) >> 1, lc = o << 1, rc = lc | 1, ans = rt[o].top();
	if(pos <= mid) return max(ans, query(pos, lc, l, mid));
	else return max(ans, query(pos, rc, mid + 1, r));
}
//线段树，每个节点是一个堆

void modify(int x, int y, int k, int gx){
	t = 0;
	while(top[x] != top[y]) {
		if(dep[top[x]] < dep[top[y]]) swap(x, y);
		st[++t] = (Range){dfn[top[x]], dfn[x]};
		x = fa[top[x]];
	} if(dfn[x] > dfn[y]) swap(x, y);
	st[++t] = (Range){dfn[x], dfn[y]};
	sort(st + 1, st + t + 1);
	int L = 0;
	for(int i = 1; i <= t; L = max(L, st[i].r), ++i)
		if(L + 1 < st[i].l) update(gx, L + 1, st[i].l - 1, k);
	if(L < n) update(gx, L + 1, tim, k);
	//处理不在区间内的点
}//计算/取消某条边的贡献

int main () {
	freopen("network.in", "r", stdin);
	freopen("network.out", "w", stdout);
	read(n), read(m);
	for(int i = 1, u, v; i < n; ++i)
		read(u), read(v), addEdge(u, v), addEdge(v, u);
	dfs(1), dfs(1, 1);
	int opt, x ,y, k;
	for(int i = 1; i <= m; ++i) {
		read(opt), read(x);
		if(!opt) {
			read(y), read(k);
			d[i] = (Dist){x, y, k};
			modify(x, y, k, 1);
		} else if(opt == 1) modify(d[x].x, d[x].y, d[x].k, 0);
		else printf("%d\n", query(dfn[x]));
	}
	return 0;
} 
