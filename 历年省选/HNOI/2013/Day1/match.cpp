#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using std::map;
using std::min; using std::max;
using std::swap; using std::sort;
typedef long long ll;

template<typename T>
void read(T &x) {
    int flag = 1; x = 0; char ch = getchar();
    while(ch < '0' || ch > '9') { if(ch == '-') flag = -flag; ch = getchar(); }
    while(ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar(); x *= flag;
}

const int N = 1e1 + 10, P = 1e9 + 7, M = 19260817;
int n, sc[N], tmp[N]; map<int, int> s;

int hash(int x) {
	ll ret = x - 1;
	for(int i = 1; i < x; ++i) ret = ret * M + tmp[i];
	return ret;
}

int doit(int x, int y) {
	if(x == y) {
		if(sc[x] != 0) return 0;//结果矩阵非零
		if(x == 1) return 1;
		for(int i = 1; i < x; ++i) tmp[i] = sc[i];
		sort(tmp + 1, tmp + x);//顺序无关
		int index = hash(x);//对数组进行哈希
		return s.count(index) ? s[index] : s[index] = doit(x - 1, 1);
		//记忆化
	}
	int ret = 0;
	//搜索输赢情况
	if(sc[x] >= 3) sc[x] -= 3, (ret += doit(x, y + 1)) %= P, sc[x] += 3;
	if(sc[y] >= 3) sc[y] -= 3, (ret += doit(x, y + 1)) %= P, sc[y] += 3;
	if(sc[x] && sc[y])
		--sc[x], --sc[y], (ret += doit(x, y + 1)) %= P, ++sc[x], ++sc[y];
	return ret;
}

int main () {
    freopen("match.in", "r", stdin);
    freopen("match.out", "w", stdout);
	read(n);
	for(int i = 1; i <= n; ++i) read(sc[i]);
	printf("%d\n", doit(n, 1));
	return 0;
} 
