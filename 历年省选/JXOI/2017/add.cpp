#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using std::upper_bound;
using std::min; using std::max;
using std::swap; using std::sort;
typedef long long ll;
#define lt first
#define rt second

template<typename T>
void read(T &x) {
	int flag = 1; x = 0; char ch = getchar();
	while(ch < '0' || ch > '9') { if(ch == '-') flag = -flag; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int _ = 2e5 + 10, Inf = 1e9 + 7;
int T, n, m, k, inc, a[_];
std::pair<int, int> range[_];
std::priority_queue<int> Ri;

int bit[_], st[_], top;
void add(int x, int y) { for(; x <= top; x += x & -x) bit[x] += y; }
int sum(int x) { int r = 0; for(; x; x -= x & -x) r += bit[x]; return r; }

bool check(int mid) {
	top = 0;
	for(int i = 1; i <= n; ++i)
		if(a[i] < mid) st[++top] = i;
	while(Ri.size()) Ri.pop();
	memset(bit, 0, sizeof(bit[0]) * (top + 5));
	for(int i = 1, j = 1, cnt = 0; i <= top; ++i) {
		while(j <= m && range[j].lt <= st[i])
			Ri.push(upper_bound(st + 1, st + top + 1, range[j].rt) - st - 1), ++j;
		while(a[st[i]] + sum(i) < mid) {
			if(++cnt > k || Ri.empty()) return 0;
			add(i, inc), add(Ri.top() + 1, -inc), Ri.pop();
		}
	}
	return 1;
}

int main () {
	freopen("add.in", "r", stdin);
	freopen("add.out", "w", stdout);
	read(T);
	while(T--) {
		read(n), read(m), read(k), read(inc);
		for(int i = 1; i <= n; ++i) read(a[i]);
		for(int i = 1; i <= m; ++i)
			read(range[i].lt), read(range[i].rt);
		sort(range + 1, range + m + 1);
		int L = Inf, R, ret;
		for(int i = 1; i <= n; ++i) L = min(L, a[i]);
		R = L + inc * k;
		while(L <= R) {
			int mid = (L + R) >> 1;
			if(check(mid)) L = mid + 1, ret = mid;
			else R = mid - 1;
		}
		printf("%d\n", ret);
	}
	return 0;
} 
