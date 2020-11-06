#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
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

const int N=2e5+5;

int n;
LL s,l;
LL h[N],a[N];

bool check(LL t)
{
	LL sum=s;
	int i;
	for(i=1;i<=n;i++) {
		if(h[i]>=l-a[i]*t) 
			sum-=h[i],sum-=a[i]*t;
		if(sum<=0) return true;
	}
	return false;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	scanf("%d%lld%lld",&n,&s,&l);
	for(i=1;i<=n;i++) 
		scanf("%lld",&h[i]);
	for(i=1;i<=n;i++) 
		scanf("%lld",&a[i]);
		
	LL L=-1,R=max(s/n+1,l),mid; // (L,R]
	while(L+1<R) {
		mid=(L+R)>>1;
		if(check(mid)) R=mid;
		else L=mid;
	}
	printf("%lld\n",R);
	return 0;
}

