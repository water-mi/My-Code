#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using std::min; using std::max;
using std::swap; using std::sort;
using std::priority_queue;
typedef long long ll;

template<typename T>
void read(T &x) {
    int flag = 1; x = 0; char ch = getchar();
    while(ch < '0' || ch > '9') { if(ch == '-') flag = -flag; ch = getchar(); }
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int _ = 1e5 + 10;
int T, n, m, ind[_], ans[_], tot;
int cnt, from[_], to[_], nxt[_];
struct Node { int x, y; } p[_];
priority_queue<int> q;
inline void addEdge(int u, int v) {
	to[++cnt] = v, nxt[cnt] = from[u], from[u] = cnt;
}

int main () {
    freopen("dishes.in", "r", stdin);
    freopen("dishes.out", "w", stdout);
	read(T);
	while(T--) {
		read(n), read(m), cnt = 0;
		for(int i = 1; i <= n; ++i)
			from[i] = ind[i] = 0;
		bool flag = 0;
		for(int i = 1; i <= m; ++i) {
			read(p[i].x), read(p[i].y);
			if(p[i].x == p[i].y) flag = 1;
			addEdge(p[i].y, p[i].x), ++ind[p[i].x];
		}
		if(flag) { puts("Impossible!"); continue; }
		for(int i = 1; i <= n; ++i)
			if(!ind[i]) q.push(i);
		tot = 0;
		while(!q.empty()) {
			int u = q.top(); q.pop(); ans[++tot] = u;
			for(int i = from[u]; i; i = nxt[i])
				if(!(--ind[to[i]])) q.push(to[i]);
		}
		if(tot < n) tot = 0, printf("Impossible!");
		else while(tot--) printf("%d ", ans[tot + 1]);
		puts("");
	}
	return 0;
} 
