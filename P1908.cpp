#include<bits/stdc++.h>
#define rint register int
#define INF 2147483646
#define LL long long 
using namespace std;
const int N=5e5;
LL c[2*N];
int n;
LL a[N],t[N];
inline LL lowbit(LL n)
{
	return n&(-n);
}
inline void update(LL x,LL y)
{
	for(;x<=n;x+=lowbit(x)) c[x]+=y;
	return;
}
inline LL sum(LL x)
{
	LL res=0;
	for(;x;x-=lowbit(x)) res+=c[x];
	return res;
}
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&n);
	LL x,y;
	for(int i=1;i<=n;i++)  {
		scanf("%lld",&a[i]);
		t[i]=a[i];
	}
	sort(t+1,t+n+1);
	for(int i=1;i<=n;i++) 
		a[i]=lower_bound(t+1,t+n+1,a[i])-t;
	LL ans=0;
	for(int i=1;i<=n;i++) {
		ans+=sum(n)-sum(a[i]);
		update(a[i],1);
	}
	printf("%lld",ans);
	return 0;
}

