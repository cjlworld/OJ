#include<cstdio>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=1e5+5,K=105;
int f[N][K],a[N],cmax[K];
int n,m;
// f[i][k] 表示选完了第i天的股票，所得到的最大利润，（第i天可选可不选） ;
// f[i][k]=max(f[i-1][k],f[j][k-1]+a[i]-a[j]), 0<j<i;
int main()
{
//	freopen("1.in","r",stdin);
	int i,k;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	fill(cmax,cmax+m+1,-a[1]);
	for(i=2;i<=n;i++) {
		for(k=m;k>=1;k--) { 
			f[i][k]=max(f[i-1][k],a[i]+cmax[k-1]);
			cmax[k]=max(cmax[k],f[i][k]-a[i]);
		}
		cmax[0]=max(cmax[0],-a[i]);
	}
	int ans=0;
	for(i=1;i<=n;i++) 
		for(k=0;k<=m;k++) 
			ans=max(ans,f[i][k]);//,cout<<i<<" "<<k<<":"<<f[i][k]<<endl;
	cout<<ans;
	return 0;
}

