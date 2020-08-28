#include<cstdio>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=1e5+5;
int f[N],g[N],a[N];
int n;
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	int cmin=a[1];
	for(i=2;i<=n;i++) {
		f[i]=max(f[i-1],a[i]-cmin);
		cmin=min(a[i],cmin);
	}
	int cmax=a[n];
	for(i=n-1;i>=1;i--) {
		g[i]=max(g[i+1],cmax-a[i]);
		cmax=max(cmax,a[i]);
	}
	int ans=0;
	for(i=2;i<=n-1;i++) 
		ans=max(ans,f[i]+g[i]);
	cout<<ans;
	return 0;
}

