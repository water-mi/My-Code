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

const int N = 5e5 + 10;
int n, m, ans, a[N], b[N], sum[N], cnt[N], tot;
struct Node { int l, r, val; } p[N << 1];//链表元素
inline int newnode(int l, int r, int val) {
	p[++tot] = (Node){l, r, val};
	return tot;
} 
struct deque {
	int head, tail, len;
	inline void push_back(int x) {
		if(!len) head = tail = newnode(0, 0, x);
		else p[tail].r = newnode(tail, 0, x), tail = p[tail].r;
		++len;
	}
	inline int empty() { return !len; }
	inline int front() { return p[head].val; }
	inline int back() { return p[tail].val; }
	inline void pop_front() { head = p[head].r, --len; }
	inline void pop_back() { tail = p[tail].l, --len; }
	inline void push(int x) {
		while(!empty() && a[back()] > a[x]) pop_back();
		push_back(x);
	}
} que[N << 1], que1[N << 1], *q = que + N, *q1 = que1 + N;
inline int min(const int &x, const int &y) {
	return a[x] < a[y] ? x : y;
}

int main () {
    freopen("travel.in", "r", stdin);
    freopen("travel.out", "w", stdout);
	read(n), read(m);
	for(int i = 1; i <= n; ++i) {
		read(a[i]), read(b[i]);
		if(!b[i]) b[i] = -1;
	}
	for(int i = n; ~i; --i) sum[i] = sum[i + 1] + b[i];
	for(int i = n; i; --i) {
		cnt[i] = cnt[i + 1];
		if(!sum[i]) ++cnt[i];
	} cnt[n + 1] = -1;
	int S = sum[0];
	ans = S ? (abs(S) - 1) / m + 1 : cnt[1] < m;
	//分类讨论计算答案。
	if(ans) {
		a[n + 1] = n + 1; int la = 0;
		for(int i = 2; i <= n; ++i)
			q1[sum[i]].push_back(i - 1);
		for(int i = 1; i < m; ++i) {
			int aa = n + 1;
			for(int j = sum[la + 1] - ans; j <= sum[la + 1] + ans; ++j) {
				if((abs(j) + m - i - 1) / (m - i) > ans) continue;
				while(!q1[j].empty() && n - q1[j].front() >= m - i) {
					if(q1[j].front() > la) q[j].push(q1[j].front());
					q1[j].pop_front();
				}
				while(!q[j].empty() && q[j].front() <= la) q[j].pop_front();
				if(!q[j].empty()) aa = min(aa, q[j].front());
			}
			la = aa;
			printf("%d ", a[aa]);
		}
	} else { //ans为0即有>=m个区间和为0的区间
		for(int i = 1, j = 2; i < m; ++i) {
			for(; cnt[j + 1] >= m - i; ++j)
				if(!sum[j + 1]) q[0].push(j);
			printf("%d ", a[q[0].front()]);
			q[0].pop_front();
		}
	} printf("%d\n", a[n]);
	return 0;
} 
