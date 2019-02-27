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

const int N = 5e2 + 10, M = 5e5 + 10;
const double eps = 1e-10;
int n, m, d[N], cnt, from[N], to[M], nxt[M], u[M], v[M];
inline void addEdge(int u, int v) {
	to[++cnt] = v, nxt[cnt] = from[u], from[u] = cnt;
}
double p[N], a[N][N], b[N], w[M];

inline int fabs(double x) {
	if(x <= eps && x >= -eps) return 0;
	return (x > 0) ? 1 : -1;
}
void Gauss() {
	for(int i = 1; i < n; ++i) {
		int k = i;
		for(int j = i + 1; j < n; ++j)
			if(fabs(a[j][i] - a[k][i]) > 0) k = j;
		for(int j = 1; j <= n; ++j)
			swap(a[i][j], a[k][j]);
		for(int j = i + 1; j < n; ++j)
			if(fabs(a[j][i])) {
				double rate = a[j][i] / a[i][i];
				for(int k = 1; k <= n; ++k)
					a[j][k] -= rate * a[i][k];
			}
	}
	for(int i = n - 1; i >= 1; --i) {
		for(int j = i + 1; j < n; ++j)
			a[i][n] -= a[i][j] * p[j];
		p[i] = a[i][n] / a[i][i];
	}
}

int main () {
    freopen("walk.in", "r", stdin);
    freopen("walk.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= m; ++i) {
		read(u[i]), read(v[i]), ++d[u[i]], ++d[v[i]];
		addEdge(u[i], v[i]), addEdge(v[i], u[i]);
	}
	for(int x = 1; x <= n; ++x) {
		a[x][x] = -1.;//减去单位矩阵
		for(int i = from[x]; i; i = nxt[i])
			if(to[i] != n)
				a[x][to[i]] = 1. / d[to[i]];//构造邻接矩阵
	}
	a[1][n] = -1.;
	Gauss();//求出点的概率
	for(int i = 1; i <= m; ++i)
		w[i] = p[u[i]] / d[u[i]] + p[v[i]] / d[v[i]];
	//计算边的概率
	sort(w + 1, w + m + 1);
	double ret = 0;
	for(int i = 1; i <= m; ++i) ret += w[i] * (m - i + 1);
	printf("%.3lf\n", ret);
	return 0;
} 
