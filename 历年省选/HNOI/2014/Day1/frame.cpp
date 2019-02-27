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

const int N = 1e2 + 10, Inf = 1 << 30;
int n, a[N][N], b[N][N], ans = Inf;
struct vector { int x, y; };
inline vector operator - (const vector &a, const vector &b) {
	return (vector){a.x - b.x, a.y - b.y};
}
inline int operator * (const vector &a, const vector &b) {
	return a.x * b.y - a.y * b.x;
}
inline void ChkMax(int &a, int b) { if(a < b) a = b; }
inline void ChkMin(int &a, int b) { if(a > b) a = b; }

namespace KM {
	int match[N], w[N][N], lx[N], ly[N], reta, retb;
	bool visx[N], visy[N];
	void build(int _a, int _b) {
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				w[i][j] = -(_a * a[i][j] + _b * b[i][j]);
	}
	bool Hungary(int x) {
		visx[x] = 1;
		for(int y = 1; y <= n; ++y)
			if(!visy[y] && lx[x] + ly[y] == w[x][y]) {
				visy[y] = 1;
				if(!match[y] || Hungary(match[y])) {
					match[y] = x; return 1;
				}
			}
		return 0;
	}
	vector Main() {
		reta = 0, retb = 0;
		for(int i = 1; i <= n; ++i) {
			lx[i] = -Inf, ly[i] = 0;
			for(int j = 1; j <= n; ++j)
				ChkMax(lx[i], w[i][j]);
		}
		memset(match, 0, sizeof match);
		for(int x = 1; x <= n; ++x)
			while(1) {
				memset(visx, 0, sizeof visx), memset(visy, 0, sizeof visy);
				if(Hungary(x)) break;
				int inc = Inf;
				for(int i = 1; i <= n; ++i)
					if(visx[i])
						for(int j = 1; j <= n; ++j)
							if(!visy[j]) ChkMin(inc, lx[i] + ly[j] - w[i][j]);
				for(int i = 1; i <= n; ++i) {
					if(visx[i]) lx[i] -= inc;
					if(visy[i]) ly[i] += inc;
				}
			}
		for(int i = 1; i <= n; ++i)
			if(match[i])
				reta += a[match[i]][i], retb += b[match[i]][i];
		return (vector){reta, retb};
	}
}//KM求解二分图带权最小匹配（有些细节不同）

void doit(const vector &A, const vector &B) {
	KM::build(A.y - B.y, B.x - A.x);
	vector C = KM::Main();
	ans = min(ans, C.x * C.y);
	if((B - A) * (C - A) >= 0) return ;
	doit(A, C), doit(C, B);
}//不断寻找最远的C

int T;
int main () {
	freopen("frame.in", "r", stdin);
	freopen("frame.out", "w", stdout);
	read(T);
	while(T--) {
	    read(n);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				read(a[i][j]);
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j)
				read(b[i][j]);
		vector A, B;
		KM::build(1, 0), A = KM::Main();
		KM::build(0, 1), B = KM::Main();
		ans = min(A.x * A.y, B.x * B.y);
		doit(A, B), printf("%d\n", ans);
	}
	return 0;
} 
