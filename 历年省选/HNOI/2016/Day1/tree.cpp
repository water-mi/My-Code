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

const int _ = 1e5 + 10, Log = 20;

struct SegmentTree {
	int poi, rt[_], lson[_ * Log], rson[_ * Log], siz[_ * Log];
	void build(int &o, int l, int r) {
		o = ++poi; if(l == r) return ;
		int mid = (l + r) >> 1;
		build(lson[o], l, mid);
		build(rson[o], mid + 1, r);
	}
	int modify(int o, int l, int r, int k) {
		int o_ = ++poi;
		lson[o_] = lson[o], rson[o_] = rson[o], siz[o_] = siz[o] + 1;
		if(l == r) return o_; int mid = (l + r) >> 1;
		if(k <= mid) lson[o_] = modify(lson[o_], l, mid, k);
		else rson[o_] = modify(rson[o_], mid + 1, r, k);
		return o_;
	}
	int query (int x, int y, int l, int r, int k) {
		int val, mid = (l + r) >> 1, delta = siz[lson[y]] - siz[lson[x]];
		if(l == r) return l;
		if(delta >= k) val = query(lson[x], lson[y], l, mid, k);
		else val = query(rson[x], rson[y], mid + 1, r, k - delta);
		return val;
	}
} tree;
//主席树区间第k大打板子，没有什么不同的地方。

namespace temp {
	int n, fa[Log][_], dep[_], S[_], T[_], tim, sta[_];
	int cnt, from[_], to[_ << 1], nxt[_ << 1];
	inline void addEdge(int u, int v) {
		to[++cnt] = v, nxt[cnt] = from[u], from[u] = cnt;
	}
	void dfs(int u, int f) {
		S[u] = ++tim, sta[tim] = u, fa[0][u] = f, dep[u] = dep[f] + 1;
		for(int i = 1; i <= 16; ++i)
			fa[i][u] = fa[i - 1][fa[i - 1][u]];
		for(int i = from[u]; i; i = nxt[i])
			if(to[i] != f) dfs(to[i], u);
		T[u] = tim;
	}//同样是预处理，没什么好讲的，理解每个数组的含义照着含义模拟即可
	void Init() {
		int u, v;
		for(int i = 1; i < n; ++i)
			read(u), read(v), addEdge(u, v), addEdge(v, u);
		dfs(1, 0);
		tree.build(tree.rt[0], 1, n);
		for(int i = 1; i <= n; ++i)
			tree.rt[i] = tree.modify(tree.rt[i - 1], 1, n, sta[i]);
		//预处理一些该处理的东西，比如主席树之类的
	}
	int getdist(int x, int y) {
		int ret = 0;
		if(dep[x] < dep[y]) swap(x, y);
		for(int i = 16; i >= 0; --i)
			if(dep[fa[i][x]] >= dep[y])
				ret += (1 << i), x = fa[i][x];
		if(x == y) return ret;
		for(int i = 16; i >= 0; --i)
			if(fa[i][x] != fa[i][y]) {
				ret += (1 << (i + 1));
				x = fa[i][x], y = fa[i][y];
			}
		return ret + 2;
	}//这里不是求LCA,是在求解LCA的时候顺带着把距离给算出来了
}
//模板树

namespace big {
	int n, m, fa[Log][_], dep[_], pre[_];
	ll dist[Log][_], S[_], T[_], lnk[_], poi;
	int getrt(ll x) {
		int L = 1, R = n;
		while(L <= R) {
			int mid = (L + R) >> 1;
			if(S[mid] > x) R = mid - 1;
			else L = mid + 1;
		} return R;
	}
	int getpre(ll x) {
		int rt = getrt(x);
		int l = tree.rt[temp::S[pre[rt]] - 1],
			r = tree.rt[temp::T[pre[rt]]];
		return tree.query(l, r, 1, temp::n, x - S[rt] + 1);
	}
	//以上两个函数题解中讲的应该很清楚了
	void Init() {
		n = dep[1] = pre[1] = 1, S[1] = 1ll;
		poi = T[1] = temp::n;
		int x; ll to;
		for(int i = 1; i <= m; ++i) {
			read(x), read(to); int rt = getrt(to);
			++n, dep[n] = dep[rt] + 1, lnk[n] = to, pre[n] = x;
			S[n] = poi + 1, T[n] = poi + temp::T[x] - temp::S[x] + 1, poi = T[n];
			fa[0][n] = rt;
			//fa,dep，dist这些数组都是大点相关，跟小的结点无关
			dist[0][n] = temp::dep[getpre(to)] - temp::dep[pre[rt]] + 1;
			for(int j = 1; j <= 16; ++j) {
				fa[j][n] = fa[j - 1][fa[j - 1][n]];
				dist[j][n] = dist[j - 1][n] + dist[j - 1][fa[j - 1][n]];
			}//倍增更新信息
		}
	}
	ll doit(ll x, ll y) {
		ll ret = 0; int fx = getrt(x), fy = getrt(y);
		if(fx == fy) return temp::getdist(getpre(x), getpre(y));
		//如果在同一个大点内直接求解，否则在大点上倍增
		if(dep[fx] < dep[fy]) swap(x, y), swap(fx, fy);
		ret += temp::dep[getpre(x)] - temp::dep[pre[fx]], x = fx;
		//计算出小结点x到所在大点的根的距离
		for(int i = 16; i >= 0; --i)
			if(dep[fa[i][x]] > dep[fy])
				ret += dist[i][x], x = fa[i][x];
		//在大点上倍增
		if(getrt(lnk[x]) == fy)
			return ret + 1 + temp::getdist(getpre(lnk[x]), getpre(y));
		//此时如果此时就在fy这个大点的下方（即lnk[x]就在fy内），计算一下lnk[x]到它所在大点的根的距离+1+ret
		ret += temp::dep[getpre(y)] - temp::dep[pre[fy]], y = fy;
		//计算出小结点y到所在大点的根的距离，然后两个大点一起跳
		if(dep[x] > dep[y]) ret += dist[0][x], x = fa[0][x];
		//之前可能还没有跳到同一深度，补跳一次
		for(int i = 16; i >= 0; --i)
			if(fa[i][x] != fa[i][y]) {
				ret += dist[i][x] + dist[i][y];
				x = fa[i][x], y = fa[i][y];
			}
		//在大点上一起跳
		x = lnk[x], y = lnk[y]; ret += 2;
		//此时再往上跳一次就进入了同一个大点，然后求一下在大点这棵子树内的距离即可
		return ret + temp::getdist(getpre(x), getpre(y));
	}
}

int main () {
	freopen("tree.in", "r", stdin);
	freopen("tree.out", "w", stdout);
	int q; ll x, y;
	read(temp::n), read(big::m), read(q);
	temp::Init(), big::Init();
	while(q--)
		read(x), read(y), printf("%lld\n", big::doit(x, y));
	return 0;
} 
