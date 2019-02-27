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
int T, F, n, s, sg[_], f[_];
bool mex[_];

int SG(int x) {
	if(~sg[x]) return sg[x];
	if(x < F) return sg[x] = 0
	for(int l = 2, r; l <= x; l = r + 1) {
		r = x / (x / l);
		for(int j = l; j <= min(l + 1, r); ++j) {
			int a = x % j, b = x / j + 1, c = j - x % j, d = x / j, s = 0;
			if(a & 1) s ^= SG(b);
			if(c & 1) s ^= SG(d);
			f[s] = x;
		}
	}
	int t = 0;
	while(f[t] == x) ++t;
	return sg[x] = t;
}

int main () {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
	memset(sg, -1, sizeof sg);
	read(T), read(F);
	while(T--) {
		read(n); int ret = 0;
		while(n--) read(s), ret ^= SG(s);
		printf(ret ? "1 " : "0 ");
	} puts("");
	return 0;
} 
