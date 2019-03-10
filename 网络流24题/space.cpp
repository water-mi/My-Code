#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
using std::vector; using std::queue;
using std::min; using std::max;
using std::swap; using std::sort;
typedef long long ll;

template<typename T>
void read(T &x) {
	int flag = 1; x = 0; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') flag = -flag; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int _ = 8e5 + 10, Inf = 1e9 + 7;
int n, m, val[_], ret, ulen, num, c[_], S, T, flag;
char s[10010]; bool use[_];
vector<int> tools[_];
int cnt = 1, from[_], to[_], nxt[_], flow[_];
inline void addEdge(int u, int v, int f) {
	to[++cnt] = v, nxt[cnt] = from[u], from[u] = cnt, flow[cnt] = f;
	to[++cnt] = u, nxt[cnt] = from[v], from[v] = cnt, flow[cnt] = 0;
}

int dep[_]; queue<int> q;
bool BFS() {
	memset(dep, 0, sizeof (int) * (n + m + 10)), dep[S] = 1;
	while(q.size()) q.pop(); q.push(S);
	while(q.size()) {
		int u = q.front(); q.pop();
		for(int i = from[u]; i; i = nxt[i]) {
			int v = to[i]; if(!flow[i] || dep[v]) continue;
			dep[v] = dep[u] + 1, q.push(v);
			if(v == T) return 1;
		}
	}
	return 0;
}

int dinic(int u, int __) {
	if(u == T) return __;
	int rest = __, k;
	for(int i = from[u]; i; i = nxt[i]) {
		int v = to[i]; if(!flow[i] || dep[v] != dep[u] + 1) continue;
		k = dinic(v, min(rest, flow[i])); if(!k) dep[v] = 0;
		flow[i] -= k, flow[i ^ 1] += k, rest -= k;
	}
	return __ - rest;
}

int main () {
	freopen("space.in", "r", stdin);
	freopen("space.out", "w", stdout);
	read(m), read(n), T = m + n + 1;
	for(int i = 1; i <= m; ++i) {
		read(val[i]), ret += val[i];
		memset(s, 0, sizeof s);
		std::cin.getline(s, 10000);
		ulen = 0;
		while(sscanf(s + ulen, "%d", &num) == 1) {
			tools[i].push_back(num);
			if(!num) ++ulen;
			else while(num) num /= 10, ++ulen;
			++ulen;
		}
	}
	for(int i = 1; i <= m; ++i) addEdge(S, i, val[i]);
	for(int i = 1; i <= n; ++i)
		read(c[i]), addEdge(i + m, T, c[i]);
	vector<int>::iterator it;
	for(int i = 1, j; i <= m; ++i)
		for(it = tools[i].begin(); it != tools[i].end(); ++it)
			j = *it, addEdge(i, j + m, Inf);
	int __;
	while(BFS()) while(__ = dinic(S, Inf)) ret -= __;
	for(int i = 1; i <= m; ++i)
		if(dep[i]) {
			if(flag) printf(" ");
			flag = 1, printf("%d", i);
		}
	puts(""), flag = 0;
	for(int i = 1; i <= n; ++i)
		if(dep[i + m]) {
			if(flag) printf(" ");
			flag = 1, printf("%d", i);
		}
	printf("\n%d\n", ret);
	return 0;
} 
