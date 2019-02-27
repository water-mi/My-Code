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
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int _ = 5e3 + 10, Inf = 1e9 + 7;
int T, a, b, c, MN, poi, x[_], y[_], z[_], ans, cnt, from[_];
bool level[_];
struct Edge { int to, nxt; } e[_];
inline void addEdge(int u, int v) { e[++cnt] = (Edge){v, from[u]}, from[u] = cnt; }
#define Rg register

int vis[_], match[_];
bool Hungary(int u, int tim) {
	for(Rg int i = from[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		if(vis[v] != tim) {
			vis[v] = tim;//卡常使用时间戳，减少清空数组带来的常数增大
			if(!match[v] || Hungary(match[v], tim)) { match[v] = u; return 1; }
		}
	} return 0;
}


void doit(int now) {
	for(Rg int i = 1; i <= b; ++i) from[i] = 0;
	for(Rg int i = 1; i <= c; ++i) match[i] = vis[i] = 0;
	cnt = 0; int ret = a;
	for(Rg int i = now; i; i -= i & -i) --ret;
	for(Rg int i = 1; i <= poi; ++i)
		if((1 << (x[i] - 1)) & now) addEdge(y[i], z[i]);
	//拍扁后建立二分图模型
	for(Rg int i = 1; i <= b; ++i) {
		if(Hungary(i, i)) ++ret;//二分图匹配
		if(ret >= ans) return ;//最优性剪枝
	} ans = ret;
}

int main () {
    freopen("clear.in", "r", stdin);
    freopen("clear.out", "w", stdout);
	read(T);
	while(T--) {
		read(a), read(b), read(c);
		ans = Inf, MN = min(a, min(b, c)), poi = 0;
		for(Rg int i = 1; i <= a; ++i)
			for(Rg int j = 1; j <= b; ++j)
				for(Rg int k = 1; k <= c; ++k) {
					Rg int tmp; read(tmp);
					if(!tmp) continue; ++poi;
					if(MN == a) x[poi] = i, y[poi] = j, z[poi] = k;
					else if(MN == b) x[poi] = j, y[poi] = i, z[poi] = k;
					else if(MN == c) x[poi] = k, y[poi] = j, z[poi] = i;	
				}
		if(MN == b) swap(a, b);
		else if(MN == c) swap(a, c);
		//调整使得a<b<c
		for(Rg int i = 0; i < (1 << a); ++i) doit(i);//状压枚举删去哪一层
		printf("%d\n", ans);
	}
	return 0;
}
