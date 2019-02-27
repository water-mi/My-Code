#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
using std::multiset;
using std::min; using std::max;
using std::swap; using std::sort;
using std::unique; using std::lower_bound;
typedef long long ll;

template<typename T>
void read(T &x) {
    int flag = 1; x = 0; char ch = getchar();
    while(ch < '0' || ch > '9') { if(ch == '-') flag = -flag; ch = getchar(); }
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int N = 2e5 + 10;
int n, m, P, Q, h[N];
int fa[N], dep[N], son[N], top[N], siz[N];
int L[N], R[N], tim, tot, ans[N];

int cnt, from[N], to[N << 1], nxt[N << 1];
inline void addEdge(int u, int v) {
	to[++cnt] = v, nxt[cnt] = from[u], from[u] = cnt;
}

struct Line { int x, L, R, w, val; } p[N], tp[N];
inline bool operator < (const Line &a, const Line &b) {
	return a.x < b.x;
}

struct Que { int x, y, k, id; } q[N], tq[N];
inline bool operator < (const Que &a, const Que &b) {
	return a.x < b.x;
}

void dfs(int u) {
	siz[u] = 1, dep[u] = dep[fa[u]] + 1;
	for(int i = from[u]; i; i = nxt[i]) {
		int v = to[i]; if(v == fa[u]) continue;
		fa[v] = u, dfs(v), siz[u] += siz[v];
		if(siz[v] > siz[son[u]]) son[u] = v;
	}
}
void dfs(int u, int t) {
	L[u] = ++tim, R[u] = L[u] + siz[u] - 1, top[u] = t;
	if(son[u]) dfs(son[u], t);
	for(int i = from[u]; i; i = nxt[i])
		if(to[i] != fa[u] && to[i] != son[u])
			dfs(to[i], to[i]);
}

int Find(int x, int y) {
	while(top[x] != top[y]) {
		if(fa[top[y]] == x) return top[y];
		y = fa[top[y]];
	} return son[x];
}

int c[N];
void upt(int x, int y) { for(; x <= n; x += x & -x) c[x] += y; }
int query(int x) { int y = 0; for(; x; x -= x & -x) y += c[x]; return y; }
void add(int l, int r, int w) { upt(l, w), upt(r + 1, -w); }
void Div(int l, int r, int st, int ed, int lval, int rval) {
	if(l > r || st > ed) return ;
	if(lval == rval) {
		for(int i = st; i <= ed; ++i)
			ans[q[i].id] = h[lval];
		return ;
	}
	int mid = (lval + rval) >> 1, j = l;
	int pl = l, pr = r, ql = st, qr = ed, tmp;
	for(int i = st; i <= ed; ++i) {
		for(; j <= r && p[j].x <= q[i].x; ++j)
			if(p[j].val > h[mid]) tp[pr--] = p[j];
			else add(p[j].L, p[j].R, p[j].w), tp[pl++] = p[j];
		q[i].k > (tmp = query(q[i].y)) ?
			q[i].k -= tmp, tq[qr--] = q[i] : tq[ql++] = q[i];
	}
	for(; j <= r; ++j)
		if(p[j].val > h[mid]) tp[pr--] = p[j];
		else add(p[j].L, p[j].R, p[j].w), tp[pl++] = p[j];
	for(int i = l; i <= pr; ++i) add(tp[i].L, tp[i].R, -tp[i].w);
	for(int i = l; i <= pr; ++i) p[i] = tp[i];
	for(int i = pl; i <= r; ++i) p[r + pl - i] = tp[i];
	for(int i = st; i <= qr; ++i) q[i] = tq[i];
	for(int i = ql; i <= ed; ++i) q[ed + ql - i] = tq[i];
	Div(l, pr, st, qr, lval, mid);
	Div(pl, r, ql, ed, mid + 1, rval);
}

int main () {
    freopen("fruit.in", "r", stdin);
    freopen("fruit.out", "w", stdout);
	read(n), read(P), read(Q);
	int x, y, z;
	for(int i = 1; i < n; ++i)
		read(x), read(y), addEdge(x, y), addEdge(y, x);
	dfs(1), dfs(1, 1);
	for(int i = 1; i <= P; ++i) {
		read(x), read(y), read(h[i]);
		if(L[x] > L[y]) swap(x, y);
		if(L[x] <= L[y] && L[y] <= R[x]) {
			z = Find(x, y);
			p[++m] = (Line){1, L[y], R[y], 1, h[i]};
			p[++m] = (Line){L[z], L[y], R[y], -1, h[i]};
			if(R[z] < n) {
				p[++m] = (Line){L[y], R[z] + 1, n, 1, h[i]};
				p[++m] = (Line){R[y] + 1, R[z] + 1, n, -1, h[i]};
			} 
		} else {
			p[++m] = (Line){L[x], L[y], R[y], 1, h[i]};
			p[++m] = (Line){R[x] + 1, L[y], R[y], -1, h[i]};
		}
	}
	sort(p + 1, p + m + 1), sort(h + 1, h + P + 1);
	tot = unique(h + 1, h + P + 1) - h - 1;
	for(int i = 1; i <= Q; ++i) {
		read(x), read(y), read(z);
		if(L[x] > L[y]) swap(x, y);
		q[i] = (Que){L[x], L[y], z, i};
	}
	sort(q + 1, q + Q + 1);
	Div(1, m, 1, Q, 1, tot);
	for(int i = 1; i <= Q; ++i) printf("%d\n", ans[i]);
	return 0;
} 
