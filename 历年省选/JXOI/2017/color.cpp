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
#if __cplusplus >= 201103l
template<typename T, typename... V>
void read(T &x, V&... v) { read(x), read(v...); }
#endif

const int _ = 3e5 + 10;
int T, n, m, a[_], lsh[_], L[_], R[_];
int st[_], top; ll ret;

int tag[_ << 2], sum[_ << 2];
void pushdown(int o, int lc, int rc, int len) {
	if(tag[o]) {
		tag[lc] = tag[rc] = 1, tag[o] = 0;
		sum[lc] = (len - (len >> 1)), sum[rc] = len >> 1;
	}
}
void build(int o = 1, int l = 1, int r = n) {
	tag[o] = sum[o] = 0;
	if(l == r) return ; int mid = (l + r) >> 1, lc = o << 1, rc = lc | 1;
	build(lc, l, mid), build(rc, mid + 1, r);
}
void modify(int ml, int mr, int o = 1, int l = 1, int r = n) {
	if(l >= ml && r <= mr) return (void)(tag[o] = 1, sum[o] = r - l + 1);
	int mid = (l + r) >> 1, lc = o << 1, rc = lc | 1;
	pushdown(o, lc, rc, r - l + 1);
	if(ml <= mid) modify(ml, mr, lc, l, mid);
	if(mr > mid) modify(ml, mr, rc, mid + 1, r);
	sum[o] = sum[lc] + sum[rc];
}
int query(int ql, int qr, int o = 1, int l = 1, int r = n) {
	if(l >= ql && r <= qr) return sum[o];
	int mid = (l + r) >> 1, lc = o << 1, rc = lc | 1, ret = 0;
	pushdown(o, lc, rc, r - l + 1);
	if(ql <= mid) ret = query(ql, qr, lc, l, mid);
	if(qr > mid) ret += query(ql, qr, rc, mid + 1, r);
	return ret;
}

int main () {
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
	read(T);
	while(T--) {
		read(n), ret = top = 0;
		for(int i = 1; i <= n; ++i)
			read(a[i]), lsh[i] = a[i];
		sort(lsh + 1, lsh + n + 1);
		m = std::unique(lsh + 1, lsh + n + 1) - lsh - 1;
		for(int i = 1; i <= n; ++i)
			a[i] = std::lower_bound(lsh + 1, lsh + m + 1, a[i]) - lsh;
		n = std::unique(a + 1, a + n + 1) - a - 1;
		for(int i = 1; i <= m; ++i) L[i] = R[i] = 0;
		for(int i = 1; i <= n; ++i) {
			if(!L[a[i]]) L[a[i]] = i;
			R[a[i]] = i;
		}
		build();
		for(int l = n; l >= 1; --l) {
			if(L[a[l]] == l) {
				if(L[a[l]] <= R[a[l]] - 1)
					modify(L[a[l]], R[a[l]] - 1);
			} else st[++top] = l;
			while(top && L[a[st[top]]] >= l) --top;
			int r = top ? st[top] - 1 : n;
			ret += r - l + 1 - query(l, r);
		}
		printf("%lld\n", ret);
	}
	return 0;
} 
