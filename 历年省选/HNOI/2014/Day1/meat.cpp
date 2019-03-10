#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using std::vector;
using std::min; using std::max;
using std::swap; using std::sort;
typedef long long ll;

template<typename T>
void read(T &x) {
    int flag = 1; x = 0; char ch = getchar();
    while(ch < '0' || ch > '9') { if(ch == '-') flag = -flag; ch = getchar(); }
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int N = 5e5 + 10;
const double eps = 1e-8;
int n; double a[N], f[N];
vector<int> to[N];

void dfs(int u, double sum) {
	f[u] = sum + log(1. * a[u]);
	for(int i = 0; i < to[u].size(); ++i) {
		int v = to[u][i];
		dfs(v, sum + log(1. * to[u].size()));
	}
}

int main () {
    freopen("meat.in", "r", stdin);
    freopen("meat.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i) read(a[i]);
	for(int i = 1, u, v; i < n; ++i)
		read(u), read(v), to[u].push_back(v);
	dfs(1, log(1.0)), sort(f + 1, f + n + 1);
	int cnt = 1, ret = 1;
	//寻找众数
	for(int i = 2; i <= n; ++i) {
		if(f[i] - f[i - 1] <= eps) ++cnt;
		else ret = max(cnt, ret), cnt = 1;
	} printf("%d\n", n - max(ret, cnt));
	return 0;
} 
