#include <vector>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using std::min; using std::max;
using std::swap; using std::sort;
using std::vector; using std::__gcd;
typedef long long ll;

template<typename T>
void read(T &x) {
	int flag = 1; x = 0; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') flag = -flag; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int N = 2e5 + 10, M = 1.2e6 + 10;
const double eps = 1e-10;
int n, m, q, cnt = 1, rt, pos[M], poi;
ll ans1, ans2, fz[M], fm[M];
//分子分母（多么生动形象）就是面积平方和面积
int nxt[M], fa[M], vis[M], ist[M], ques[M];
struct point { int x, y; } p[N];
inline point operator - (const point &a, const point &b) {
	return (point){a.x - b.x, a.y - b.y};
}
inline ll operator * (const point &a, const point &b) {
	return 1ll * a.x * b.y - 1ll * b.x * a.y;
}
struct edge{ int id, x, y; double angle; } e[M];
inline bool operator < (const edge &a, const edge &b) {
	return fabs(a.angle - b.angle) < eps ? a.y < b.y : a.angle < b.angle;
}
vector<edge> g[N], T[M];

inline void addEdge(int u, int v) {
	e[++cnt] = (edge){cnt, u, v, atan2(p[v].y - p[u].y, p[v].x - p[u].x)};
	g[u].push_back(e[cnt]);
	//用vector存边顺便弄一下极角
}

void build() {
	for(int i = 1; i <= n; ++i) sort(g[i].begin(), g[i].end());
	//按照极角排序
	for(int i = 2; i <= cnt; ++i) {
		int v = e[i].y; vector<edge>::iterator it;
		it = lower_bound(g[v].begin(), g[v].end(), e[i ^ 1]);
		if(it == g[v].begin()) it = g[v].end();//记得特判开头
		--it, nxt[i] = it->id;
	}
	//找上一条边
	for(int i = 2; i <= cnt; ++i) {
		if(pos[i]) continue;
		pos[i] = pos[nxt[i]] = ++poi;
		for(int j = nxt[i]; e[j].y != e[i].x; j = nxt[j], pos[j] = poi)
			fm[poi] += (p[e[j].x] - p[e[i].x]) * (p[e[j].y] - p[e[i].x]);
		//计算有向面积
		if(fm[poi] <= 0) rt = poi;//这个时候找到的就是大点
	}//建面
	for(int i = 2; i <= cnt; ++i)
		T[pos[i]].push_back((edge){i, pos[i], pos[i ^ 1]});
	//面之间的连边
}//建立对偶图

void dfs(int u) {
	fz[u] = 1ll * fm[u] * fm[u], fm[u] <<= 1, vis[u] = 1;
	//为了避免出现叉积算面积后除以二出现小数，分子分母同时乘上4
	for(int i = 0; i < T[u].size(); ++i) {
		int v = T[u][i].y; if(vis[v]) continue;
		ist[T[u][i].id] = ist[T[u][i].id ^ 1] = 1;
		//标记一下这条边在生成树上
		fa[v] = u, dfs(v), fm[u] += fm[v], fz[u] += fz[v];
	}//统计生成树上的面积和面积平方之和
}//扣一棵生成树出来

int main () {
	freopen("mine.in", "r", stdin);
	freopen("mine.out", "w", stdout);
	read(n), read(m), read(q);
	int x, y;
	for(int i = 1; i <= n; ++i)
		read(x), read(y), p[i] = (point){x, y};
	for(int i = 1; i <= m; ++i)
		read(x), read(y), addEdge(x, y), addEdge(y, x);
	build(), dfs(rt);
	while(q--) {
		read(x); x = (x + ans1) % n + 1;
		for(int i = 1; i <= x; ++i) read(y), ques[i] = (y + ans1) % n + 1;
		ques[x + 1] = ques[1], ans1 = ans2 = 0;
		for(int i = 1; i <= x; ++i) {
			int u = ques[i], v = ques[i + 1]; vector<edge>::iterator it;
			edge e = (edge){0, u, v, atan2(p[v].y - p[u].y, p[v].x - p[u].x)};
			//找边
			it = lower_bound(g[u].begin(), g[u].end(), e);
			//分类讨论
			int j = it->id; if(!ist[j]) continue;//不在生成树上略过
            if(fa[pos[j]] == pos[j ^ 1]) ans1 += fz[pos[j]], ans2 += fm[pos[j]];//是儿子（即它的父亲正好是反边的出点）
            else ans1 -= fz[pos[j ^ 1]], ans2 -= fm[pos[j ^ 1]];//是父亲
        }
		//转成既约分数
        ll tmp = __gcd(ans1, ans2);
        ans1 /= tmp, ans2 /= tmp;
        printf("%lld %lld\n", ans1, ans2);
	}
	return 0;
} 
