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

const int N=200+5,M=2000+5,INF=0x3f3f3f3f;

int w[N][N],a[M];
int n,m;
int f[N][N],g[N][N];
// f[i][j][k] 表示已经满足了 [1,i] 的服务， 一个点在 a[i],其余两个点分别在 j,k 的最小费用 

inline void tense(int &t,int b) { if(b<t) t=b; }

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) 
		for(j=1;j<=n;j++) 
			scanf("%d",&w[i][j]);
	for(i=1;i<=m;i++) 
		scanf("%d",&a[i]);
	a[0]=1;
	memset(f,0x3f,sizeof f);
	f[2][3]=f[3][2]=0;
	
	for(i=1;i<=m;i++) {
		memcpy(g,f,sizeof g);
		memset(f,0x3f,sizeof f);
		for(j=1;j<=n;j++) {
			if(j==a[i]) continue;
			for(k=1;k<=n;k++) {
				if(k!=a[i]&&k!=j) tense(f[j][k],g[j][k]+w[a[i-1]][a[i]]);
				if(a[i-1]!=a[i]&&j!=a[i-1]) tense(f[a[i-1]][j],g[k][j]+w[k][a[i]]),
								tense(f[j][a[i-1]],g[j][k]+w[k][a[i]]);
			}
		}
	}
	
	int ans=INF;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++) 
			tense(ans,f[i][j]);
	printf("%d\n",ans);
	return 0;
}

