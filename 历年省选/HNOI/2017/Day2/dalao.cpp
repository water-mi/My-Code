#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using std::queue; using std::pair;
using std::min; using std::max;
using std::swap; using std::sort;
typedef long long ll;
typedef pair<int, int> pii;

template<typename T>
void read(T &x) {
	int flag = 1; x = 0; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') flag = -flag; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int _ = 1e2 + 10, MAX = 11111111, P = 1e6 + 7;
int n, m, mc, a[_], w[_], c[_], MX, Day, f[_][_];
struct Node { int i, F, L; };
pii zt[MAX]; int tot;
inline void ChkMax(int &a, int b) { if(a < b) a = b; }
struct Hash {
	struct Line { int x, y, next; } e[MAX];
	int h[P + 1], cnt;
	void add(int x, int y) {
		int pos = (1ll * x * 101 + y) % P;
		e[++cnt] = (Line){x, y, h[pos]}, h[pos] = cnt;
	}
	bool query(int x, int y) {
		int pos = (1ll * x * 101 + y) % P;
		for(int i = h[pos]; i; i = e[i].next)
			if(e[i].x == x && e[i].y == y) return 1;
		return 0;
	}
} Map;//哈希表判重

void BFS() {
	queue<Node> Q; Q.push((Node){1, 1, 0});
	while(!Q.empty()) {
		Node u = Q.front(); Q.pop();
		if(u.i == Day) continue;
		Q.push((Node){u.i + 1, u.F, u.L + 1});//提升等级
		if(u.L > 1 && 1ll * u.F * u.L <= 1ll * MX &&
		   !Map.query(u.F * u.L, u.i + 1)) {
			//判重然后计算F*L
			Q.push((Node){u.i + 1, u.F * u.L, u.L});
			zt[++tot] = (pii){u.F * u.L, u.i + 1};
			Map.add(u.F * u.L, u.i + 1);
		}
	}
}
//BFS+Hash找出可用的FL搭配

int main () {
	freopen("dalao.in", "r", stdin);
	freopen("dalao.out", "w", stdout);
	read(n), read(m), read(mc);
	for(int i = 1; i <= n; ++i) read(a[i]);
	for(int i = 1; i <= n; ++i) read(w[i]);
	for(int i = 1; i <= m; ++i) read(c[i]), MX = max(MX, c[i]);
	for(int i = 1; i <= n; ++i)
		for(int j = a[i]; j <= mc; ++j) {
			ChkMax(f[i][j - a[i]], f[i - 1][j] + 1);
			ChkMax(f[i][min(j - a[i] + w[i], mc)], f[i - 1][j]);
		}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= mc; ++j)
			ChkMax(Day, f[i][j]);
	//动态规划找出能剩下的最大空闲天数
	BFS(); sort(zt + 1, zt + tot + 1);
	for(int i = 1; i <= m; ++i) {
		if(c[i] <= Day) { puts("1"); continue; }
		//不释放大招
		bool fl = 0; int MN = 1e9;
		for(int j = tot, k = 1; j; --j) {
			while(k < tot && zt[k].first + zt[j].first <= c[i])
				MN = min(MN, zt[k].second - zt[k].first), ++k;
			if(MN + c[i] - zt[j].first <= Day - zt[j].second) { fl = 1; break; }
			if(zt[j].first <= c[i] && c[i] - zt[j].first <= Day - zt[j].second) {
				fl = 1; break;
			}//释放一次大招
		}//two-pointers找出释放两次大招（顺便处理一下释放一次）
		puts(fl ? "1" : "0");
	}
	return 0;
} 
