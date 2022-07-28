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
#include<complex>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=5e4+5;

bool tag[N];
int p[N],tot;
int miu[N],sum[N];
LL f[N];

void prime(int n)
{
	int i,j,k;
	miu[1]=1;
	for(i=2;i<=n;i++) {
		if(!tag[i]) p[++tot]=i,miu[i]=-1;
		for(j=1;j<=tot && i*p[j]<=n;j++) {
			tag[i*p[j]]=true;
			if(i%p[j]) miu[i*p[j]]=-miu[i];
			else break; 
		}
	}
	for(i=1;i<=n;i++) sum[i]=sum[i-1]+miu[i];
	
	for(k=1;k<=n;k++) 
		for(i=1;i<=k;i=j+1) {
			int t=k/i; j=k/t;
			f[k]+=(j-i+1)*t;
		}
}

LL n,m,T;

int main()
{
//	freopen("1.in","r",stdin);
	
	scanf("%lld",&T);
	prime(N-1);
	LL i,j;
	while(T--) {
		scanf("%lld%lld",&n,&m);
		LL ans=0;
		for(i=1;i<=min(n,m);i=j+1) {
			j=min(n/(n/i),m/(m/i));
			ans+=(sum[j]-sum[i-1])*f[n/i]*f[m/i];
		}
		printf("%lld\n",ans);
	}
	return 0;
}

