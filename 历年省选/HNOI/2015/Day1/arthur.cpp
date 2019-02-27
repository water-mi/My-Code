#include <cstdio>
#include <cstring>
#include <algorithm>
using std::max;

const int N = 230, R = 140;
int t, n, r, d[N];
double p[N], fp[N], pow[N][N], f[N][R];

int main () {
	freopen("arthur.in", "r", stdin);
	freopen("arthur.out", "w", stdout);
    scanf("%d", &t);
    while(t--) {
        scanf("%d%d", &n, &r);
        for(int i = 0; i < n; ++i) scanf("%lf%d", p + i, d + i);
        for(int i = 0; i < n; ++i) {
            pow[i][0] = 1;
            for(int j = 1; j <= r; ++j)
                pow[i][j] = pow[i][j - 1] * (1 - p[i]);//预处理(1-p[i])的幂
        }
        memset(f, 0, sizeof f), memset(fp, 0, sizeof fp);
        f[0][0] = pow[0][r], f[0][1] = fp[0] = 1 - f[0][0];
        for(int i = 1; i < n; ++i)
            for(int j = 0; j <= r; ++j) {
                fp[i] += f[i - 1][j] * (1 - pow[i][r - j]);
                f[i][j] += f[i - 1][j] * pow[i][r - j];
                if(j) f[i][j] += f[i - 1][j - 1] * (1 - pow[i][r - j + 1]);
            }
        double ret = 0;
        for(int i = 0; i < n; ++i) ret += d[i] * fp[i];
        printf("%.10lf\n", ret);
    }
    return 0;
}
