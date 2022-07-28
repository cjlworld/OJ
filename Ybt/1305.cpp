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

const int N=50000+5;
const LL INF=1e16;
LL a[N];
LL fl[N],fr[N],gl[N],gr[N]; 
// fl[i] 表示 1--i 以i结尾的最大子段和（一定有i）
// gl[i] = max( fl[1]...fl[i] ) ;
// fr,gr 同理 .
int n,T;

int main()
{
	int i,j;
	LL cmax=0,ans=-INF;
	scanf("%d",&T);
	while(T--) {
		memset(fl,0,sizeof fl);
		memset(fr,0,sizeof fr);
		memset(gl,0xcf,sizeof gl);
		memset(gr,0xcf,sizeof gr);
		ans=-INF;
		scanf("%d",&n);
		for(i=1;i<=n;i++) 
			scanf("%lld",&a[i]);
		fl[1]=cmax=a[1];
		for(i=2;i<=n;i++) {
			fl[i]=max(a[i],cmax+a[i]);
			cmax=max(a[i],cmax+a[i]);
			gl[i]=max(fl[i],gl[i-1]);
		}
		fr[n]=cmax=a[n];
		for(i=n-1;i>=1;i--) {
			fr[i]=max(a[i],cmax+a[i]);
			cmax=max(a[i],cmax+a[i]);
			gr[i]=max(fr[i],gr[i+1]);
		}
		for(i=1;i<=n-1;i++) 
			ans=max(ans,gl[i]+gr[i+1]);
		printf("%lld\n",ans);
	}
	return 0;
}

