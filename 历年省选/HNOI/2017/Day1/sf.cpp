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
	while(ch < '0' || ch > '9') { if(ch == '-') flag = -flag; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int _ = 5e5 + 10, Log = 10, Inf = 1 << 30;
int n, m, p1, p2, k[_], st[_], top, pre[_], suf[_];
ll ans[_], c1[_], c2[_];
struct Ques { int l, r, x, id, v; } q1[_], q2[_];
inline bool operator < (const Ques &a, const Ques &b) { return a.x < b.x; }

void add(int x, int y) {
	if(x) for(int i = x; i <= n; i += i & -i) c1[i] += y, c2[i] += 1ll * x * y;
}
ll sum(int x) {
	ll ret = 0;
	for(int i = x; i > 0; i -= i & -i) ret += (x + 1) * c1[i] - c2[i];
	return ret;
}

int main () {
	freopen("sf.in", "r", stdin);
	freopen("sf.out", "w", stdout);
	read(n), read(m), read(p1), read(p2);
	for(int i = 1; i <= n; ++i) read(k[i]);
	k[0] = k[n + 1] = Inf;
	for(int i = 1; i <= n; ++i) {
		while(k[st[top]] < k[i]) suf[st[top--]] = i;
		pre[i] = st[top], st[++top] = i;
	}
	while(top) pre[st[top]] = st[top - 1], suf[st[top--]] = n + 1;
	int x, y;
	for(int i = 1; i <= m; ++i) {
		read(x), read(y), ans[i] += (y - x) * p1;
		q1[i] = (Ques){x, y, x - 1, i, -1};
		q1[i + m] = (Ques){x, y, y, i, 1};
	}
	m <<= 1;
	sort(q1 + 1, q1 + m + 1);
	int tot = 0;
	for(int i = 1; i <= n; ++i) {
		if(1 <= pre[i] && suf[i] <= n)
			q2[++tot] = (Ques){pre[i], pre[i], suf[i], 0, p1};
		if(1 <= pre[i] && suf[i] - 1 > i)
			q2[++tot] = (Ques){i + 1, suf[i] - 1, pre[i], 0, p2};
		if(pre[i] + 1 < i && suf[i] <= n)
			q2[++tot] = (Ques){pre[i] + 1, i - 1, suf[i], 0, p2};
	}
	sort(q2 + 1, q2 + tot + 1); int top1 = 1, top2 = 1;
	while(!q1[top1].x) ++top1;
	for(int i = 1; top1 <= m && i <= n; ++i) {
		while(top2 <= tot && q2[top2].x == i) {
			add(q2[top2].r + 1, -q2[top2].v);
			add(q2[top2].l, q2[top2].v);
			++top2;
		}
		while(top1 <= m && q1[top1].x == i) {
			ll now = q1[top1].v * (sum(q1[top1].r) - sum(q1[top1].l - 1));
			ans[q1[top1].id] += now, ++top1;
		}
	}
	m >>= 1;
	for(int i = 1; i <= m; ++i) printf("%lld\n", ans[i]);
	return 0;
} 
