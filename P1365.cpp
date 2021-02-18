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

const int N=3e5+5;

int n;
char a[N];
double g[N],f[N];

// g[i] 表示以 i 结尾的极长段的期望。 
// f[i] 表示以 1,...,i 的得分的的期望 
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	
	scanf("%d%s",&n,a+1);
	g[0]=0;
	for(i=1;i<=n;i++) {
		if(a[i]=='o') g[i]=g[i-1]+1;
		else if(a[i]=='x') g[i]=0;
		else g[i]=0.5*(g[i-1]+1);
	}
	
	f[0]=0;
	for(i=1;i<=n;i++) {
		if(a[i]=='o') f[i]=f[i-1]+2*g[i-1]+1;
		else if(a[i]=='x') f[i]=f[i-1];
		else f[i]=0.5*(f[i-1]+2*g[i-1]+1)+0.5*f[i-1];
	}
	
	printf("%.4lf\n",f[n]);
	return 0;
}

