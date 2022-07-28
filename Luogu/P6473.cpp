#include<cstdio>
#include<iostream>
#include<algorithm>
#define LL long long
using namespace std;
const int N=2e5+5;
LL v,m;
int n,q;
LL a[N];
LL f[N];
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	LL x,y,z;
	scanf("%d%lld%lld",&n,&m,&v);
	for(i=1;i<=n;i++) 
		scanf("%lld",&a[i]);
	sort(a+1,a+n+1,greater<int>());
	f[0]=m;
	for(i=1;i<=n;i++) 
		f[i]=f[i-1]+a[i];
	scanf("%d",&q);
	for(i=1;i<=q;i++) {
		scanf("%lld",&x);
		if(f[n]<=v*x) {
			printf("-1\n");
			continue;
		}
		z=upper_bound(f,f+n+1,x*v)-f;
		printf("%lld\n",z);
	}
	return 0;
}

