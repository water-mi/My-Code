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

const int _ = 1e6 + 10;
int n, m, p, key[_], st[_], top, l[_], r[_];
int L[_], R[_], t[_ << 2];

void build(int o = 1, int l = 1, int r = n) {
	if(l == r) { t[o] = key[l]; return ; }
	int mid = (l + r) >> 1, lc = o << 1, rc = lc | 1;
	build(lc, l, mid), build(rc, mid + 1, r);
	t[o] = max(t[lc], t[rc]);
}

int get(int pos, int o = 1, int l = 1, int r = n) {
	if(t[o] <= pos) return 0;
	if(l == r) return l;
	int mid = (l + r) >> 1, lc = o << 1, rc = lc | 1;
	if(t[rc] > pos) return get(pos, rc, mid + 1, r);
	else return get(pos, lc, l, mid);
}

int query(int ql, int qr, int k, int o = 1, int l = 1, int r = n) {
	if(l >= ql && r <= qr) return get(k, o, l, r);
	int mid = (l + r) >> 1, pos = 0, lc = o << 1, rc = lc | 1;
	if(qr > mid) pos = query(ql, qr, k, rc, mid + 1, r);
	if(pos) return pos;
	//因为是在左侧寻找，所以右儿子要先找（最近）
	if(ql <= mid) pos = query(ql, qr, k, lc, l, mid);
	return pos;
}

int find_pos(int l, int r, int k) {
	if(l > r) return l;
	int pos = query(l, r, k);
	return pos ? pos + 1 : l;//找不到就说明只能到此达止
}//查找key[x]>r[i]的第一个位置，然后返回+1值（不然就变成到不了的地方了）

int main () {
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	read(n), read(m), read(p);
	int x, y; 
	for(int i = 1; i <= m; ++i)
		read(x), read(key[x]);
	build(), key[n] = n + 1, key[0] = -1;
	for(int i = 1; i <= n; ++i)
		L[i] = key[i - 1] && key[i - 1] <= i - 1 ? i : L[i - 1];
	for(int i = n; i >= 1; --i)
		R[i] = key[i] && key[i] > i ? i : R[i + 1];
	//找到左右侧的限制
	for(int i = n; i >= 1; --i) {
		l[i] = r[i] = i;
		l[i] = find_pos(L[i], l[i] - 1, r[i]);//找到目前能够到达的最远的l
		st[++top] = i;
		while(top && ((l[i] <= key[st[top]] && key[st[top]] <= r[i]) || !key[st[top]])) {
			r[i] = st[--top];
			l[i] = find_pos(L[i], l[i] - 1, r[i]);
		}//利用单调栈不断更新l,r
	}
	while(p--) {
		read(x), read(y);
		puts(l[x] <= y && y <= r[x] ? "YES" : "NO");
	}
	return 0;
} 
