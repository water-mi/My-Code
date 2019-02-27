#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using std::queue;
using std::min; using std::max;
using std::swap; using std::sort;
typedef long long ll;

template<typename T>
void read(T &x) {
    int flag = 1; x = 0; char ch = getchar();
    while(ch < '0' || ch > '9') { if(ch == '-') flag = -flag; ch = getchar(); }
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int _ = 50, N = 3e5 + 10, Inf = 1e9 + 7;
const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};
int p, q, r, d, v[_][_][_], s, t;
int cnt, from[N], to[N], nxt[N], flow[N];
inline void addEdge(int u, int v, int f) {
	to[++cnt] = v, nxt[cnt] = from[u], flow[cnt] = f, from[u] = cnt;
	to[++cnt] = u, nxt[cnt] = from[v], flow[cnt] = 0, from[v] = cnt;
}

namespace Dinic {
	int maxflow, flow, dep[N];
	bool init() {
		memset(dep, 0, sizeof dep);
		queue<int> q; q.push(s), dep[s] = 1;
		while(!q.empty()) {
			int u = q.front(); q.pop();
			for(int i = from[u]; i; i = nxt[i]) {
				int v = to[i];
				if(::flow[i] && !dep[v]) {
					q.push(v), dep[v] = dep[u] + 1;
					if(v == t) return true;
				}
			}
		}
		return false;
	}
	int doit(int u, int flow) {
		if(u == t) return flow;
		int rest = flow, k;
		for(int i = from[u]; i && rest; i = nxt[i]) {
			int v = to[i];
			if(::flow[i] && dep[v] == dep[u] + 1) {
				k = doit(v, min(rest, ::flow[i]));
				if(!k) dep[v] = 0;
				::flow[i] -= k, ::flow[i ^ 1] += k, rest -= k;
			}
		}
		return flow - rest;
	}
	void main() {
		while(init())
			while(flow = doit(s, Inf))
				maxflow += flow;
	}
}

int main () {
    freopen("cake.in", "r", stdin);
    freopen("cake.out", "w", stdout);
	read(p), read(q), read(r), read(d), cnt = 1;
	for(int k = 1; k <= r; ++k)
		for(int i = 1; i <= p; ++i) 
			for(int j = 1; j <= q; ++j)
				read(v[i][j][k]);
	t = p * q * (r + 1) + 1;
	for(int i = 1; i <= p; ++i)
		for(int j = 1; j <= q; ++j) {
			int x = (i - 1) * q + j;
			addEdge(s, x, Inf), addEdge(p * q * r + x, t, Inf);
			for(int k = 1; k <= r; ++k)
				addEdge(p * q * (k - 1) + x, p * q * k + x, v[i][j][k]);
		}
	//建立无d限制连边
	for(int i = 1; i <= p; ++i)
		for(int j = 1; j <= q; ++j)
			for(int f = 0; f < 4; ++f) {
				int x = i + dx[f], y = j + dy[f];
				if(x < 1 || x > p || y < 1 || y > q) continue;
				for(int k = d + 1; k <= r + 1; ++k)
					addEdge(p * q * (k - 1) + (i - 1) * q + j,
							p * q * (k - d - 1) + (x - 1) * q + y, Inf);
			}
	//建立d限制连边
	Dinic::main();
	printf("%d\n", Dinic::maxflow);
    return 0;
} 
