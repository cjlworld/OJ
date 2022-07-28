#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=5000+5;
const LL INF=1e16;
LL a[N],s[N];
LL f[N][N]; // f[i][j] 表示当前以i结尾,上一个决策以j结尾的最小值。
LL g[N][N];
int n,Type;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	scanf("%d%d",&n,&Type);
	for(i=1;i<=n;i++) 
		scanf("%lld",&a[i]),s[i]=s[i-1]+a[i];
	memset(f,0x3f,sizeof f);
	for(i=1;i<=n;i++) {
		f[i][0]=min(f[i][0],s[i]*s[i]);
		for(j=1;j<=i-1;j++) {
			k=(int)(lower_bound(s,s+j,2*s[j]-s[i])-s);
			if(k==j) continue;
			k=g[j][k];
			f[i][j]=min(f[i][j],f[j][k]+(s[i]-s[j])*(s[i]-s[j]));
		}
		g[i][i-1]=i-1;
		for(j=i-2;j>=0;j--) {
			if(f[i][j]<f[i][g[i][j+1]]) 
				g[i][j]=j;
			else g[i][j]=g[i][j+1];
		}	
	}
	LL ans=INF;
	for(i=0;i<=n-1;i++) 
		ans=min(ans,f[n][i]);
	cout<<ans;
	return 0;
}

