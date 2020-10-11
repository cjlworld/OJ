#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=1e5+5;
int f[N],g[N],a[N];
int n;
int main()
{
	int i,T,cmax,cmin,ans;
	cin>>T;
	while(T--) {
		memset(a,0,sizeof a);
		memset(f,0,sizeof f);
		memset(g,0,sizeof g);
		scanf("%d",&n);
		for(i=1;i<=n;i++) 
			scanf("%d",&a[i]);
		cmin=a[1];
		for(i=2;i<=n;i++) {
			f[i]=max(f[i-1],a[i]-cmin);
			cmin=min(a[i],cmin);
		}
		cmax=a[n];
		for(i=n-1;i>=1;i--) {
			g[i]=max(g[i+1],cmax-a[i]);
			cmax=max(cmax,a[i]);
		}
		ans=0;
		for(i=2;i<=n-1;i++) 
			ans=max(ans,f[i]+g[i]);
		cout<<ans<<endl;
	}
	return 0;
}

