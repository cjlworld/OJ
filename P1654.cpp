#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<bitset>
#include<vector>
#include<cstdio>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=1e5+5;

int n;
double a[N]; // 每个操作的成功率
double f[N],g[N],h[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%lf",&a[i]);
	for(i=1;i<=n;i++) {
		g[i]=a[i]*(g[i-1]+1);
		h[i]=a[i]*(h[i-1]+2*g[i-1]+1);
	}
	for(i=1;i<=n;i++) 
		f[i]=a[i]*(f[i-1]+3*h[i-1]+3*g[i-1]+1)+(1-a[i])*f[i-1];
	printf("%.1lf\n",f[n]);
	return 0;
}

