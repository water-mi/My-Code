#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using std::queue;
using std::priority_queue;
using std::min; using std::max;
using std::swap; using std::sort;
typedef long long ll;

template<typename T>
void read(T &x) {
    int flag = 1; x = 0; char ch = getchar();
    while(ch < '0' || ch > '9') { if(ch == '-') flag = -flag; ch = getchar(); }
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int N = 1e5 + 10, M = 2e5 + 10, Inf = 1e9 + 7;
int n, m, L, upt[N], st[N], MN[N], sp[M], rest[M];

int cnt, from[N], to[M], nxt[M], dis[M], stop[M];
inline void addEdge(int u, int v, int w) {
	to[++cnt] = v, nxt[cnt] = from[u];
	dis[cnt] = w, from[u] = cnt;
}

struct Node { int bel, dis; };
inline bool operator < (const Node &a, const Node &b) {
	return a.dis > b.dis;
}
priority_queue<Node> heap;

queue<int> q; bool inq[N];
void spfa(int s) {
	q.push(s), inq[s] = 1;
	while(q.size()) {
		int u = q.front(); q.pop(), inq[u] = 0;
		for(int i = from[u]; i; i = nxt[i]) {
			if(stop[i]) continue;
			int v = to[i], w = MN[u] + dis[i];
			if(w < MN[v]) {
				MN[v] = w;
				if(!upt[v]) { if(!inq[v]) q.push(v), inq[v] = 1; }
				else heap.push((Node){upt[v], MN[v] + rest[upt[v]]});
			}
		}
	}
}

int main () {
    freopen("road.in", "r", stdin);
    freopen("road.out", "w", stdout);
	read(n), read(m), read(L);
	int u, v, w;
	for(int i = 1; i <= m; ++i)
		read(u), read(v), read(w), addEdge(u, v, w);
	for(int i = 1; i <= L; ++i) {
		read(sp[i]); int v = to[sp[i]];
		stop[sp[i]] = 1, upt[v] = i + 1, st[i + 1] = v;
	}
	for(int i = L; i; --i)
		rest[i] = rest[i + 1] + dis[sp[i]];
	memset(MN, 127, sizeof MN);
	upt[1] = st[1] = 1, MN[st[1]] = 0, spfa(st[1]);
	for(int i = 1; i <= L; ++i) {
		while(heap.size() && heap.top().bel <= i) heap.pop();
		if(heap.empty()) puts("-1");
		else printf("%d\n", heap.top().dis);
		MN[st[i + 1]] = MN[st[i]] + dis[sp[i]], spfa(st[i + 1]);
	}
	return 0;
} 
