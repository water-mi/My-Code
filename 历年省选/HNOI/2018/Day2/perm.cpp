#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
using std::min; using std::max;
using std::swap; using std::sort;
using std::push_heap; using std::pop_heap;
typedef long long ll;

template<typename T>
void read(T &x) {
	int flag = 1; x = 0; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') flag = -flag; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int N = 5e5 + 10;
int n, tim, f[N], fa[N], siz[N], vis[N];
ll ans, w[N];
struct Node { int u, siz; ll w; };
inline bool operator < (const Node &a, const Node &b) {
	return a.siz * b.w < a.w * b.siz;
}
int cnt, from[N], to[N], nxt[N];
inline void addEdge(int u, int v) {
	to[++cnt] = v, nxt[cnt] = from[u], from[u] = cnt;
}
struct Heap {
	Node h[N]; int siz;
	inline int size() { return siz; }
	inline bool empty() { return !siz; }
	inline Node top() { return h[1]; }
	inline void push(Node x) { h[++siz] = x, push_heap(h + 1, h + siz + 1); }
	inline void pop() { pop_heap(h + 1, h + siz + 1), --siz; }
} q;

void dfs(int u) {
	vis[u] = 1, ++tim;
	for(int i = from[u]; i; i = nxt[i]) {
		int v = to[i];
		if(vis[v]) { puts("-1"); exit(0); }
		dfs(v);
	}
}

int find(int x) { return fa[x] == x ? x : (fa[x] = find(fa[x])); }

int main () {
	freopen("perm.in", "r", stdin);
	freopen("perm.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i) read(f[i]), addEdge(f[i], i);
	//连边
	dfs(0); if(tim <= n) { puts("-1"); return 0; }
	//建树
	for(int i = 0; i <= n; ++i) fa[i] = i, siz[i] = 1;
	//初始化并查集和元素组
	for(int i = 1; i <= n; ++i) read(w[i]), q.push((Node){i, 1, w[i]});
	while(q.size()) {
		Node now = q.top(); q.pop(); int u = find(now.u);//找到序列开头
		if(siz[u] != now.siz) continue; //有点类似于Dijkstra去掉无用状态
		fa[u] = find(f[u]);//找到父亲序列的开头
		ans += w[u] * siz[fa[u]], w[fa[u]] += w[u], siz[fa[u]] += siz[u];
		//计算答案，合并
		if(fa[u]) q.push((Node){fa[u], siz[fa[u]], w[fa[u]]});	
		//记得加进去
	}
	printf("%lld\n", ans);
	return 0;
} 
