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

ll n, k, m, p;
ll qpow(ll a, ll b) {
	ll ret = 1;
	for(; b; (a *= a) %= p, b >>= 1) if(b & 1) (ret *= a) %= p;
	return ret;
}
int main () {
    freopen("seq.in", "r", stdin);
    freopen("seq.out", "w", stdout);
	read(n), read(k), read(m), read(p), n %= p;//n记得取模
	ll a = qpow(m, k - 1) * n % p;
	ll b = (m * (m + 1) / 2) % p * (k - 1) % p * qpow(m, k - 2) % p;
	printf("%lld\n", (a + p - b) % p);
	return 0;
} 
