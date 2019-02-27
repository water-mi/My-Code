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

const int N = 3e5 + 10, Inf = 1e9 + 7;
int n, q, k;
int cnt, from[N], to[N << 1], nxt[N << 1], dis[N << 1];
int f[21][N], dep[N], bel[N], siz[N], dfn[N], tim;
int stk[N], top, cont[N], dist[N];
inline void addEdge(int u, int v, int w = 1) {
	to[++cnt] = v, nxt[cnt] = from[u], dis[cnt] = w, from[u] = cnt;
}
struct Ques {int x, id;} p[N];
inline bool cmpx(const Ques &a, const Ques &b) { return dfn[a.x] < dfn[b.x]; }
inline bool cmpid(const Ques &a, const Ques &b) { return a.id < b.id; }
int intree[N], ans[N], t[N], tot;

void dfs(int u) {
	dep[u] = dep[f[0][u]] + 1, siz[u] = 1, dfn[u] = ++tim;
	for(int i = 1; i <= 20; ++i)
		f[i][u] = f[i - 1][f[i - 1][u]];
	for(int i = from[u]; i; i = nxt[i]) {
		int v = to[i]; if(v == f[0][u]) continue;
		f[0][v] = u, dfs(v), siz[u] += siz[v];
	}
}

int LCA(int x, int y) {
	if(dep[x] < dep[y]) swap(x, y);
	for(int i = 20; ~i; --i) if(dep[f[i][x]] >= dep[y]) x = f[i][x];
	if(x == y) return x;
	for(int i = 20; ~i; --i) if(f[i][x] != f[i][y]) x = f[i][x], y = f[i][y];
	return f[0][x];
}

int jump(int x, int k) {
	if(dep[x] < k) return x;
	for(int i = 20; ~i; --i) if(dep[f[i][x]] >= k) x = f[i][x];
	return x;
}

void build() {
	sort(p + 1, p + k + 1, cmpx), stk[top = 1] = 1;
	for(int i = 1; i <= k; ++i) {
		int x = p[i].x; if(x == 1) continue;
		int lca = LCA(stk[top], x);
		while(top > 1 && dep[stk[top - 1]] > dep[lca]) {
			int dis = dep[stk[top]] - dep[stk[top - 1]];
			addEdge(stk[top], stk[top - 1], dis);
			addEdge(stk[top - 1], stk[top], dis);
			--top;
		}
		if(dep[lca] < dep[stk[top]]) {
			int dis = dep[stk[top]] - dep[lca];
			addEdge(stk[top], lca, dis);
			addEdge(lca, stk[top], dis);
			--top;
		}
		if(dep[lca] > dep[stk[top]]) stk[++top] = lca; stk[++top] = x;
	}
	while(top > 1) {
		int dis = dep[stk[top]] - dep[stk[top - 1]];
		addEdge(stk[top], stk[top - 1], dis);
		addEdge(stk[top - 1], stk[top], dis);
		--top;
	}
}

void dfs1(int u, int f) {
	cont[u] = siz[u]; t[++tot] = u;
	if(intree[u]) dist[u] = 0, bel[u] = u;
	else dist[u] = Inf;
	for(int i = from[u]; i; i = nxt[i]) {
		int v = to[i]; if(v == f) continue; dfs1(v, u);
		if(dist[u] > dist[v] + dis[i] || (dist[u] == dist[v] + dis[i] && bel[u] > bel[v]))
			dist[u] = dist[v] + dis[i], bel[u] = bel[v];
	}
}

void dfs2(int u, int fa) {
	for(int i = from[u]; i; i = nxt[i]) {
		int v = to[i]; if(v == fa) continue;
		if(dist[v] > dist[u] + dis[i] || (dist[v] == dist[u] + dis[i] && bel[v] > bel[u]))
			dist[v] = dist[u] + dis[i], bel[v] = bel[u];
		dfs2(v, u);
		if(bel[v] == bel[u]) cont[u] -= siz[v];
		else {
			int d = dist[v] + dist[u] + dep[v] - dep[u] - 1, k = d / 2 - dist[v];
			int t = jump(v, dep[v] - k);
			if((d & 1) && bel[u] > bel[v] && k >= 0) t = f[0][t];
			cont[v] += siz[t] - siz[v], cont[u] -= siz[t];
		} ans[bel[v]] += cont[v];
	}
	if(u == 1) ans[bel[u]] += cont[u];
}

int main () {
    freopen("worldtree.in", "r", stdin);
    freopen("worldtree.out", "w", stdout);
	read(n);
	for(int i = 1, u, v; i < n; ++i) read(u), read(v), addEdge(u, v), addEdge(v, u);
	dfs(1); read(q), memset(from, 0, sizeof from), cnt = 0;
	while(q--) {
		read(k);
		for(int i = 1; i <= k; ++i) read(p[i].x), intree[p[i].x] = 1, p[i].id = i;
		build(), dfs1(1, 0), dfs2(1, 0);
		sort(p + 1, p + k + 1, cmpid);
		for(int i = 1; i <= k; ++i) printf("%d ", ans[p[i].x]);
		puts(""), cnt = 0;
		for(int i = 1; i <= tot; ++i)
			intree[t[i]] = from[t[i]] = ans[t[i]] = cont[t[i]] = bel[t[i]] = dis[t[i]] = 0;
		tot = 0;
	}
	return 0;
} 
