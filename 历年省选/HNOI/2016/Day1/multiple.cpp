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
inline void ChkMax(int &a, int b) { if(a < b) a = b; }

const int _ = 1e5 + 10;
int n, m, q, size, ans[_];

struct Node { int u, v, a, b, k; } a[_], b[_], c[_], d[_];
inline bool cmpa(const Node &a, const Node &b) {
    return a.a < b.a || (a.a == b.a && a.b < b.b);
}
inline bool cmpb(const Node &a, const Node &b) {
    return a.b < b.b || (a.b == b.b && a.a < b.a);
}

int top, siz[_], fa[_], MXa[_], MXb[_];
int find(int x) { return fa[x] == x ? x : find(fa[x]); }
void unionn(int x, int y, int a, int b) { //y->x
    int fx = find(x), fy = find(y);
    if(siz[fx] < siz[fy]) swap(fx, fy);
    d[++top] = (Node){fx, fy, MXa[fx], MXb[fx], siz[fx]};
    if(fx != fy) {
        fa[fy] = fx, siz[fx] += siz[fy];
        ChkMax(MXa[fx], MXa[fy]);
        ChkMax(MXb[fx], MXb[fy]);
    } ChkMax(MXa[fx], a), ChkMax(MXb[fx], b);
}

int main () {
	freopen("multiple.in", "r", stdin);
	freopen("multiple.out", "w", stdout);
    read(n), read(m), size = sqrt(m);
    for(int i = 1; i <= m; ++i) {
        read(a[i].u), read(a[i].v);
        read(a[i].a), read(a[i].b);
    }
    read(q);
    for(int i = 1; i <= q; ++i) {
        read(b[i].u), read(b[i].v);
        read(b[i].a), read(b[i].b), b[i].k = i;
    }
    sort(a + 1, a + m + 1, cmpa);
    sort(b + 1, b + q + 1, cmpb);
    for(int i = 1; i <= m; i += size) {
        for(int j = 1; j <= n; ++j)
            fa[j] = j, MXa[j] = MXb[j] = -1, siz[j] = 1;
        int tot = 0;
        for(int j = 1; j <= q; ++j)
            if(a[i].a <= b[j].a && (i + size > m || b[j].a < a[i + size].a))
                c[++tot] = b[j];
        if(!tot) continue;
        if(i > 1) sort(a + 1, a + i, cmpb);
        for(int j = 1, k = 1; j <= tot; ++j) {
            for(; k < i && a[k].b <= c[j].b; ++k)
                unionn(a[k].u, a[k].v, a[k].a, a[k].b);
            top = 0;
            for(int l = i; l < i + size && l <= m; ++l)
                if(a[l].a <= c[j].a && a[l].b <= c[j].b)
                    unionn(a[l].u, a[l].v, a[l].a, a[l].b);
            int fu = find(c[j].u), fv = find(c[j].v);
            if(fu == fv && MXa[fu] == c[j].a && MXb[fu] == c[j].b)
                ans[c[j].k] = 1;
            for(int l = top; l >= 1; --l) {
                int u = d[l].u, v = d[l].v; fa[v] = v;
                MXa[u] = d[l].a, MXb[u] = d[l].b;
                siz[u] = d[l].k;
            }
        }
    }
    for(int i = 1; i <= q; ++i) puts(ans[i] ? "Yes" : "No");
    return 0;
} 
