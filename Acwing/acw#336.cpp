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

const int N=300+5,INF=0x3f3f3f3f;

int n,m;
int a[N];

int f[N][N]; // f[i][j] 表示最后一个邮局在i，已经建了j个邮局。
int dis[N][N];

int s[N];

int pp(int l,int r)
{
	if(l==1) return a[r+1]*r-s[r];
	if(~dis[l][r]) return dis[l][r];
	int res=0;
	for(int i=l;i<=r;i++) 
		res+=min(a[i]-a[l-1],a[r+1]-a[i]);
	return dis[l][r]=res;
}
 
int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	sort(a+1,a+n+1);
	for(i=1;i<=n;i++) 
		s[i]=s[i-1]+a[i];
	memset(f,0x3f,sizeof f);
	memset(dis,-1,sizeof dis);
	f[0][0]=0;
	for(i=1;i<=n;i++) 
		for(j=1;j<=m;j++) {
			for(k=0;k<=i-1;k++) 
				f[i][j]=min(f[i][j],f[k][j-1]+pp(k+1,i-1));
		}
	
	int ans=INF;
	for(i=1;i<=n;i++) 
		ans=min(ans,f[i][m]+(s[n]-s[i])-a[i]*(n-i));
	printf("%d\n",ans);
	return 0;
}

