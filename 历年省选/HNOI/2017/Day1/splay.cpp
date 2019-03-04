#include <map>
#include <set>
#include <cstdio>
#include <cstring>
#include <algorithm>
using std::min; using std::max;
using std::swap; using std::sort;
using std::map; using std::set;
typedef long long ll;

template<typename T>
void read(T &x) {
    int flag = 1; x = 0; char ch = getchar();
    while(ch < '0' || ch > '9') { if(ch == '-') flag = -flag; ch = getchar(); }
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int N = 2e5 + 10;
namespace LCT {
    int rt, poi, ch[N][2], fa[N], siz[N], rev[N];
    inline void pushup(int x) { siz[x] = siz[ch[x][0]] + siz[ch[x][1]] + 1; }
    inline void pushdown(int x) {
        if(rev[x]) {
            int lc = ch[x][0], rc = ch[x][1];
            if(lc) swap(ch[lc][0], ch[lc][1]), rev[lc] ^= 1;
            if(rc) swap(ch[rc][0], ch[rc][1]), rev[rc] ^= 1;
            rev[x] = 0;
        }
    }
    int chk(int); void rotate(int); void splay(int);
    
    inline bool isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
    void access(int x) {
        for(int p = 0; x; p = x, x = fa[x]) splay(x), ch[x][1] = p, pushup(x);
    }
    inline void upt(int x) { if(!isroot(x)) upt(fa[x]); pushdown(x); }
    inline void makeroot(int x) {
        access(x), splay(x), swap(ch[x][0], ch[x][1]), rev[x] ^= 1;
    }
    void split(int x, int y) { makeroot(x), access(y), splay(y); }
    inline void link(int x, int y) { makeroot(x); fa[x] = y; }
    inline void cut(int x, int y) {
        split(x, y); if(ch[y][0] == x) ch[y][0] = 0;
		fa[x] = 0;
    }
	inline int getdep(int x) { split(x, rt); return siz[rt]; }
    
    inline int chk(int x) { return ch[fa[x]][1] == x; }
    inline void rotate(int x) {
        int y = fa[x], z = fa[y], k = chk(x);
        if(!isroot(y)) ch[z][chk(y)] = x;
        ch[y][k] = ch[x][k ^ 1], fa[ch[y][k]] = y;
        ch[x][k ^ 1] = y, fa[y] = x, fa[x] = z;
        pushup(y), pushup(x);
    }
    void splay(int x) {
        upt(x);
        for(; !isroot(x); rotate(x))
            if(!isroot(fa[x])) rotate(chk(fa[x]) == chk(x) ? fa[x] : x);
    }
}
//LCT模板，唯一一个新添的getdep操作已经在题解中解释过了

using namespace LCT;
map<int, int> m; set<int> s;
int Fa[N], lson[N], rson[N];
//各种数据结构

void insert(int x) {
	int now = m[x] = ++poi;
	if(s.empty()) {
		s.insert(x), rt = now;
		puts("1"); return ;
	}
	set<int>::iterator it = s.upper_bound(x);
	//分情况讨论插入左/右儿子
	if(it == s.end() || lson[m[*it]]) {
		--it; int node = m[*it];
		link(now, node);
		Fa[now] = node, rson[node] = now;
	} else {
		int node = m[*it];
		link(now, node);
		Fa[now] = node, lson[node] = now;
	}
	//一定要记得插入set中!!!
	s.insert(x), printf("%d\n", getdep(now));
}
void getmin() {
	int x = m[*s.begin()];
	if(rt == x) { puts("1"); return ; }
	//模拟单旋过程（改变父子关系）
	printf("%d\n", getdep(x)), cut(x, Fa[x]);
	if(rson[x]) cut(x, rson[x]);
	link(x, rt); if(rson[x]) link(Fa[x], rson[x]);
	lson[Fa[x]] = rson[x]; if(rson[x]) Fa[rson[x]] = Fa[x];
	Fa[x] = 0, Fa[rt] = x, rson[x] = rt, rt = x;
}
void getmax() {
	int x = m[*s.rbegin()];
	if(rt == x) { puts("1"); return ; };
	printf("%d\n", getdep(x)), cut(x, Fa[x]);
	if(lson[x]) cut(x, lson[x]);
	link(x, rt); if(lson[x]) link(Fa[x], lson[x]);
	rson[Fa[x]] = lson[x]; if(lson[x]) Fa[lson[x]] = Fa[x];
	Fa[x] = 0, Fa[rt] = x, lson[x] = rt, rt = x;	
}
void delmin() {
	int x = m[*s.begin()];
	if(rt == x) {
		puts("1");
		if(rson[x]) cut(x, rson[x]);
		Fa[rson[x]] = 0, rt = rson[x];
		s.erase(s.begin());
		return ;
	}
	//简化了一些没有必要的单旋过程，顺带着把x给删了
	printf("%d\n", getdep(x)), cut(x, Fa[x]);
	if(rson[x]) cut(x, rson[x]), link(Fa[x], rson[x]);
	lson[Fa[x]] = rson[x]; if(rson[x]) Fa[rson[x]] = Fa[x];
	s.erase(s.begin());
}
void delmax() {
	int x = m[*s.rbegin()];
	if(rt == x) {
		puts("1");
		if(lson[x]) cut(x, lson[x]);
		Fa[lson[x]] = 0, rt = lson[x];
		//这里不能写erase(rbegin())，rbgein()是反迭代器，erase只能接受迭代器
		s.erase(--s.end());
		return ;
	}
	printf("%d\n", getdep(x)), cut(x, Fa[x]);
	if(lson[x]) cut(x, lson[x]), link(Fa[x], lson[x]);
	rson[Fa[x]] = lson[x]; if(lson[x]) Fa[lson[x]] = Fa[x];
	s.erase(--s.end());
}
//上面四个操作都要记得判根

int q, x, y;
int main () {
    freopen("splay.in", "r", stdin);
    freopen("splay.out", "w", stdout);
	read(q);
	while(q--) {
		read(x);
		switch(x) {
		case 1: read(y); insert(y); break;
		case 2: getmin(); break;
		case 3: getmax(); break;
		case 4: delmin(); break;
		case 5: delmax(); break;
		}
	}
    return 0;
} 
