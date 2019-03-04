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

const int N = 3e5 + 10;
const double Pi = acos(-1);
int n, m, A[N], B[N], lg, r[N];
struct C { double x, y; } a[N], b[N];
C operator + (C a, C b) { return (C){a.x + b.x, a.y + b.y}; }
C operator - (C a, C b) { return (C){a.x - b.x, a.y - b.y}; }
C operator * (C a, C b) { return (C){a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x}; }

void FFT(C f[], int opt) {
    for(int i = 0; i < n; ++i) if(i < r[i]) swap(f[i], f[r[i]]);
    for(int len = 1, nl = 2; len < n; len = nl, nl <<= 1) {
        C rot = (C){cos(Pi / len), opt * sin(Pi / len)};
        for(int l = 0; l < n; l += nl) {
            C w = (C){1, 0}; int r = l + len;
            for(int k = l; k < r; ++k, w = w * rot) {
                C x = f[k], y = w * f[k + len];
                f[k] = x + y, f[k + len] = x - y;
            }
        }
    }
}

ll part1, part2, part3;
#define pow2(x) (x * x)
int main () {
	freopen("gift.in", "r", stdin);
	freopen("gift.out", "w", stdout);
    read(n), read(m);
    for(int i = 1; i <= n; ++i) read(A[i]);
    for(int i = 1; i <= n; ++i) read(B[i]);
    for(int i = 1; i <= n; ++i) {
        part1 += pow2(A[i]) + pow2(B[i]);
        part2 += A[i] - B[i];//这里借用一下part2
    } ll x1 = -floor(1. * part2 / n), x2 = -ceil(1. * part2 / n);
	//求解第一部分定值
    part3 = min(n * pow2(x1) + 2 * x1 * part2, n * pow2(x2) + 2 * x2 * part2);
	//求解第三部分二次函数最小值（有误差，所以顶点上下取整后的函数值都要计算一下）
    for(int i = 1; i <= n; ++i) A[i + n] = A[i];
    m = n, n <<= 1; std::reverse(B + 1, B + m + 1);
    int tmpm = m, tmpn = n;
    for(int i = 1; i <= n; ++i) a[i].x = A[i];
    for(int i = 1; i <= m; ++i) b[i].x = B[i];
    for(m += n, n = 1; n <= m; n <<= 1, ++lg);
    for(int i = 0; i < n; ++i)
        r[i] = (r[i >> 1] >> 1) | ((i & 1) << (lg - 1));
    FFT(a, 1), FFT(b, 1);
    for(int i = 0; i < n; ++i) a[i] = a[i] * b[i]; 
    FFT(a, -1), part2 = 0;//如果你也借用了part2记得清零
    for(int i = tmpm + 1; i <= tmpn; ++i)
        part2 = max(part2, (ll)(a[i].x / n +.5));
	//FFT求解第二部分的值
    printf("%lld\n", part1 + part3 - 2 * part2);
    return 0;
}
