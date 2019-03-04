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

const int _ = 1e5 + 10;
int P, n, m, L, R, tot, cnt[_];
ll hash[_], Pow[_], ans[_], now; 
char s[_];

struct Ques { int l, r, k, id; } q[_];
inline bool operator < (const Ques &a, const Ques &b) {
	return a.k < b.k || (a.k == b.k && (a.k & 1 ? a.r > b.r : a.r < b.r));
}
struct Node { ll val; int id; } f[_];
inline bool operator < (const Node &a, const Node &b) {
	return a.val < b.val;
}

inline void push(int x) { now += (cnt[hash[x]]++); }
inline void pop(int x) { now -= (--cnt[hash[x]]); }
inline void pushL(int x) { if(!((s[x] - '0') % P)) ++tot; now += tot; }
inline void popL(int x) { now -= tot; if(!((s[x] - '0') % P)) --tot; }
inline void pushR(int x) { if(!((s[x] - '0') % P)) ++tot, now += R - L + 1; }
inline void popR(int x) { if(!((s[x] - '0') % P)) now -= R - L + 1, --tot; }

int main () {
	freopen("number.in", "r", stdin);
	freopen("number.out", "w", stdout);
	read(P), scanf("%s", s + 1), read(m);
	n = strlen(s + 1), Pow[0] = 1;
	for(int i = 1; i <= n; ++i) Pow[i] = Pow[i - 1] * 10 % P;
	//预处理10的幂
	for(int i = n; i >= 1; --i)
		f[i] = (Node){(f[i + 1].val + (s[i] - '0') * Pow[n - i]) % P, i};
	sort(f + 1, f + n + 1);
	for(int i = 1; i <= n; ++i) {
		if(f[i].val != f[i - 1].val) ++tot;
		hash[f[i].id] = tot;
	}
	//离散化
	int size = sqrt(n);
	for(int i = 1; i <= m; ++i)
		read(L), read(R), q[i] = (Ques){L, R, L / size, i};
	sort(q + 1, q + m + 1);
	L = q[1].l, R = q[1].l - 1;
	if(P != 2 && P != 5) {
		for(int i = 1; i <= m; ++i) {
			int x = q[i].l, y = q[i].r + 1;
			while(L > x) push(--L);
			while(R < y) push(++R);
			while(L < x) pop(L++);
			while(R > y) pop(R--);
			ans[q[i].id] = now;
		}
	} else {
		tot = 0;
		for(int i = 1; i <= m; ++i) {
			int x = q[i].l, y = q[i].r;
			while(L > x) --L, pushL(L);
			while(R < y) ++R, pushR(R);
			while(L < x) popL(L), ++L;
			while(R > y) popR(R), --R;
			ans[q[i].id] = now;
		}
	}
	//分情况搞两个莫队。
	for(int i = 1; i <= m; ++i) printf("%lld\n", ans[i]);
	return 0;
} 
