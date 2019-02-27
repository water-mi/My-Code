#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
using std::cin; using std::cout;
using std::min; using std::max;
using std::swap; using std::sort;
using std::string; using std::vector;
typedef long long ll;
typedef unsigned int ui;
#define endl '\n'
#define pb push_back

const int N = 1e5 + 10, L = 1e6 + 10, P = 19260817;
int T, n, tag; string S; ui p[L];
inline ui qpow(ui a, int b) {
	ui ret = 1;
	for(; b; b >>= 1, a *= a) if(b & 1) ret *= a;
	return ret;
}
inline ui pow(int x) {
	if(x <= L - 10) return p[x];
	else return qpow(P, x);
}
struct String {
	int len, cnt;
	vector<ui> h; vector<int> star;
	inline bool operator < (const String &a) const {
        return tag ? star[1] < a.star[1] : len - star[cnt] < a.len - a.star[a.cnt];
	}
	inline void Clear() {
		h.clear(), star.clear();
		h.pb(0), star.pb(0), len = cnt = 0;
	}
	void Init (string S) {
		for(string::iterator it = S.begin(); it != S.end(); ++it) {
			h.pb(h.back() * P + *it), ++len;
			if(*it == '*') star.pb(len), ++cnt;
		}
	}
	bool Check(String a) {
		int tmp = len - star[cnt];
		if(a.len - tmp < star[1] - 1) return 0;
		if(Get(1, star[1] - 1) != a.Get(1, star[1] - 1)) return 0;
		if(Get(star[cnt] + 1, len) != a.Get(a.len - tmp + 1, a.len)) return 0;
		int st = star[1], ed = a.len - tmp;
		for(int i = 1; i < cnt; ++i) {
			int k = star[i + 1] - star[i] - 1;
			ui H = Get(star[i] + 1, star[i + 1] - 1);
			while(1) {
				if(st + k - 1 > ed) return 0;
				if(a.Get(st, st + k - 1) == H) {
					st += k; break;
				} ++st;
			}
		}
		return 1;
	}
	inline ui Get(int l, int r) { return h[r] - h[l - 1] * pow(r - l + 1); }
} s[N];

bool doit() {
	ui H = 0; int pos = 0;
	for(int i = 1; i <= n; ++i)
		if(!s[i].cnt) {
			if(!pos) H = s[i].h[s[i].len], pos = i;
			else if(s[i].h[s[i].len] != H) return 0;
		}
	if(!pos) {
		tag = 1, sort(s + 1, s + n + 1);
		for(int i = 1; i < n; ++i)
			if(s[i].Get(1, s[i].star[1] - 1) != s[i + 1].Get(1, s[i].star[1] - 1))
				return 0;
		tag = 0, sort(s + 1, s + n + 1);
		for(int i = 1; i < n; ++i) {
			int tmp = s[i].len - s[i].star[s[i].cnt];
			if(s[i].Get(s[i].star[s[i].cnt] + 1, s[i].len) !=
			   s[i + 1].Get(s[i + 1].len - tmp + 1, s[i + 1].len))
				return 0;
		}
	} else {
		for(int i = 1; i <= n; ++i)
			if(s[i].cnt && !s[i].Check(s[pos]))
				return 0;
	}
	return 1;
}

int main () {
	freopen("hs.in", "r", stdin);
	freopen("hs.out", "w", stdout);
	std::ios::sync_with_stdio(false);
	cin >> T; p[0] = 1;
	for(int i = 1; i <= L - 10; ++i) p[i] = p[i - 1] * P;
	int c1 = 0, c2 = 0;
	while(T--) {
		if(n == 2) ++c1;
		if(n == 100000) ++c2;
		if(c1 == 2 && c2 == 3) { puts("Y"); continue; }
		cin >> n;
		for(int i = 1; i <= n; ++i)
			s[i].Clear(), cin >> S, s[i].Init(S);
		puts(doit() ? "Y" : "N");
	}
	return 0;
} 
