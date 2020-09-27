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

const int N=1024,MOD=1e9+7;

int n,m;
int f[N][N],g[N][N];
int v[N],w[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	cin>>n>>m;
	for(i=1;i<=n;i++) 
		cin>>v[i]>>w[i];
		
	memset(f,0xc0,sizeof f);
	f[0][0]=0;
	
	for(i=1;i<=n;i++) 
		for(j=0;j<=m;j++) {
			f[i][j]=f[i-1][j];
			if(j>=v[i]) f[i][j]=max(f[i][j],f[i-1][j-v[i]]+w[i]);
		}
	int ans=0;
	for(i=0;i<=m;i++)
		ans=max(ans,f[n][i]);
		
	g[0][0]=1;
	for(i=1;i<=n;i++) 
		for(j=0;j<=m;j++) {
			if(f[i][j]==f[i-1][j]) g[i][j]=(g[i][j]+g[i-1][j])%MOD;
			if(j>=v[i]&&f[i][j]==f[i-1][j-v[i]]+w[i]) 
				g[i][j]=(g[i][j]+g[i-1][j-v[i]])%MOD;
		}
	int cnt=0;
	for(i=0;i<=m;i++)
		if(f[n][i]==ans) 
			cnt=(cnt+g[n][i])%MOD;
	cout<<cnt;
	return 0;
}

