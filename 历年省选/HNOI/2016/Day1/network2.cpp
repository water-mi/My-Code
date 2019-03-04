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
int n, m, u[M], v[M], w[M], MX;

int cnt, from[N], to[N << 1], nxt[N << 1];
inline void addEdge(int u, int v) {
	to[++cnt] = v, nxt[cnt] = from[u], from[u] = cnt;
}

struct Node { int op, id, x, ret; } q[M], ql[M], qr[M];
inline bool operator < (const Node &a, const Node &b) { return a.id < b.id; }

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

int c[N];
void add(int x, int y) { for(; x <= n; x += x & -x) c[x] += y; }
int query(int x) { int o = 0; for(; x; x -= x & -x) o += c[x]; return o; }
int query(int l, int r) { return query(r) - query(l - 1); }

int lca(int x, int y) {
	int fx = top[x], fy = top[y];
	while(fx != fy) {
		if(dep[fx] > dep[fy]) x = fa[fx], fx = top[x];
		else y = fa[fy], fy = top[y];
	} return dep[x] < dep[y] ? x : y;
}

void modify(int x, int y, int v) {
	int z = lca(x, y);
	add(dfn[x], v), add(dfn[y], v), add(dfn[z], -v);
	if(fa[z]) add(dfn[fa[z]], -v);
}//树上点覆盖，x,y+v,lca(x,y)与它的父亲-v，不多做解释。

void Div(int lval, int rval, int st, int ed) {
	if(lval == rval) {
		for(int i = st; i <= ed; ++i)
			if(q[i].op == 2) q[i].ret = lval;
		return ;
	}
	int mid = (lval + rval) >> 1, cntl = 0, cntr = 0, dist = 0;
	for(int i = st; i <= ed; ++i)
		if(q[i].op == 2) {
			if(query(dfn[q[i].x], dfn[q[i].x] + siz[q[i].x] - 1) == dist)
				ql[++cntl] = q[i];
			else qr[++cntr] = q[i];
		} else {
			if(w[q[i].x] <= mid) ql[++cntl] = q[i];
			else {
				int op = q[i].op ? -1 : 1;
				dist += op;
				modify(u[q[i].x], v[q[i].x], op);
				qr[++cntr] = q[i];
			}
		}
	for(int i = 1; i <= cntr; ++i)
		if(qr[i].op != 2) {
			int op = qr[i].op ? 1 : -1;
			modify(u[qr[i].x], v[qr[i].x], op);
		}
	for(int i = 1; i <= cntl; ++i) q[st + i - 1] = ql[i];
	for(int i = 1; i <= cntr; ++i) q[st + cntl + i - 1] = qr[i];
	if(cntl) Div(lval, mid, st, st + cntl - 1);
	if(cntr) Div(mid + 1, rval, st + cntl, ed);
}//整体二分，该讲的细节详见题解

int main () {
	freopen("network.in", "r", stdin);
	freopen("network.out", "w", stdout);
	read(n), read(m);
	for(int i = 1, x, y; i < n; ++i)
		read(x), read(y), addEdge(x, y), addEdge(y, x);
	dfs(1), dfs(1, 1);//树链剖分套路
	for(int i = 1; i <= m; ++i) {
		read(q[i].op), q[i].id = i;
		if(!q[i].op) {
			read(u[i]), read(v[i]), read(w[i]);
			q[i].x = i, MX = max(MX, w[i]);//寻找二分上界
		} else read(q[i].x);
	}
	Div(-1, MX, 1, m), sort(q + 1, q + m + 1);
	for(int i = 1; i <= m; ++i)
	  if(q[i].op == 2) printf("%d\n", q[i].ret);
	return 0;
} 
