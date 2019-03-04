#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using std::min; using std::max;
using std::swap; using std::sort;
typedef long long ll;

template<typename T>
void read(T &x) {
    int flag = 1; x = 0; char ch = getchar();
    while(ch < '0' || ch > '9') { if(ch == '-') flag = -flag; ch = getchar(); }
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int _ = 3e5 + 10;
int n, q, A, rt[_], tmp;
ll ret, dep[_], sumdep[_], pre[_], sumpre[_];
struct Node { int age, id; } x[_];
inline bool operator < (const Node &a, const Node &b) {
	return a.age < b.age || (a.age == b.age && a.id < b.id);
}

int cnt, from[_], to[_], dis[_], nxt[_];
inline void addEdge(int u, int v, int w) {
	to[++cnt] = v, dis[cnt] = w, nxt[cnt] = from[u], from[u] = cnt;
}

int poi, lson[_ << 7], rson[_ << 7], tag[_ << 7]; ll sum[_ << 7];
int modify(int o, int l, int r, int ml, int mr) {
	int o_ = ++poi, mid = (l + r) >> 1;
	lson[o_] = lson[o], rson[o_] = rson[o];
	sum[o_] = sum[o], tag[o_] = tag[o];
	if(l == ml && r == mr) { ++tag[o_]; return o_; }
	sum[o_] += (sumpre[mr] - sumpre[ml - 1]);
	if(mr <= mid) lson[o_] = modify(lson[o_], l, mid, ml, mr);
	else if(ml > mid) rson[o_] = modify(rson[o_], mid + 1, r, ml, mr);
	else {
		lson[o_] = modify(lson[o_], l, mid, ml, mid);
		rson[o_] = modify(rson[o_], mid + 1, r, mid + 1, mr);
	} return o_;
}

ll query(int o, int l, int r, int ql, int qr) {
	ll ret = 1ll * (sumpre[qr] - sumpre[ql - 1]) * tag[o];
	if(l == ql && r == qr) return ret + sum[o];
	int mid = (l + r) >> 1;
	if(qr <= mid) return ret + query(lson[o], l, mid, ql, qr);
	else if(ql > mid) return ret + query(rson[o], mid + 1, r, ql, qr);
	else return ret + query(lson[o], l, mid, ql, mid) +
			 query(rson[o], mid + 1, r, mid + 1, qr);
}
//主席树套路

int fa[_], son[_], dfn[_], top[_], siz[_], tim;
void dfs(int u) {
	siz[u] = 1;
	for(int i = from[u]; i; i = nxt[i]) {
		int v = to[i]; if(v == fa[u]) continue;
		dep[v] = dep[u] + dis[i], pre[v] = dis[i];
		fa[v] = u, dfs(v), siz[u] += siz[v];
		if(siz[v] > siz[son[u]]) son[u] = v;
	}
}

void dfs(int u, int t) {
	top[u] = t, dfn[u] = ++tim;
	sumpre[dfn[u]] = pre[u];
	if(son[u]) dfs(son[u], t);
	for(int i = from[u]; i; i = nxt[i])
		if(to[i] != fa[u] && to[i] != son[u])
			dfs(to[i], to[i]);
}

int modify(int x) {
	int fx = top[x];
	while(fx != 1) {
		tmp = modify(tmp, 1, n, dfn[fx], dfn[x]);
		x = fa[fx], fx = top[x];
	}
	tmp = modify(tmp, 1, n, dfn[1], dfn[x]);
	return tmp;
}
ll query(int rt, int x) {
	ll ret = 0; int fx = top[x];
	while(fx != 1) {
		ret += query(rt, 1, n, dfn[fx], dfn[x]);
		x = fa[fx], fx = top[x];
	}
	return ret + query(rt, 1, n, dfn[1], dfn[x]);
}
//树链剖分套路

int main () {
    freopen("shop.in", "r", stdin);
    freopen("shop.out", "w", stdout);
	read(n), read(q), read(A);
	for(int i = 1; i <= n; ++i)
		read(x[i].age), x[i].id = i;
	sort(x + 1, x + n + 1);
	for(int i = 1, u, v, w; i < n; ++i) {
		read(u), read(v), read(w);
		addEdge(u, v, w), addEdge(v, u, w);
	}
	dfs(1), dfs(1, 1);
	for(int i = 1; i <= n; ++i) {
		sumdep[i] += sumdep[i - 1] + dep[x[i].id];;
		sumpre[i] += sumpre[i - 1];
	}//预处理出第二项以及链值
	for(int i = 1; i <= n; ++i) rt[i] = modify(x[i].id);
	//对于每个点到根节点的路径覆盖
	for(int i = 1, p, l, r; i <= q; ++i) {
		read(p), read(l), read(r);
		l = (1ll * l + ret) % A;
		r = (1ll * r + ret) % A;
		if(l > r) swap(l, r);
		l = std::lower_bound(x + 1, x + n + 1, (Node){l, 0}) - x;
		r = std::upper_bound(x + 1, x + n + 1, (Node){r, 1 << 30}) - x - 1;
		ret = 1ll * (r - l + 1) * dep[p] + sumdep[r] - sumdep[l - 1]
			- 2ll * (query(rt[r], p) - query(rt[l - 1], p));
		printf("%lld\n", ret);
	}
	return 0;
} 
