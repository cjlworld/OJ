#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=2000+5;
const LL INF=0x3f3f3f3f3f3f3f3f;

int n;
LL a[N],f[N][N],c[N];
inline LL mabs(LL x) { return ((x<0) ? -x : x); }
// f[i][j] 表示已经构造了前 i 项，最后一项为 c[j] 的最小价值。 
// f[i][j] = min{f[i-1][k]+|c[j]-a[i]|},k<=j;
// c[] 是 a[] 排序后的序列。 

LL Dp()
{
	int i,j;
	LL cmin,res=INF;
	for(i=1;i<=n;i++)  {
		cmin=INF;
		for(j=1;j<=n;j++) {
			cmin=min(cmin,f[i-1][j]);
			f[i][j]=cmin+mabs(c[j]-a[i]);
		}
	}
	for(i=1;i<=n;i++) 
		res=min(res,f[n][i]);
	return res;
}

int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	memcpy(c,a,sizeof c);
	sort(c+1,c+n+1);
	LL ans=Dp();
	reverse(a+1,a+n+1);
	ans=min(ans,Dp());
	printf("%lld\n",ans);
	return 0;
}

