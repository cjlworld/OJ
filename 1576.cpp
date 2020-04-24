#include<bits/stdc++.h>
#define rint register int
#define INF 2147483646
using namespace std;
const int N=305;
const int M=305;
int n,m;
int fa[N],val[N],son[N][N];
int f[N][M];//以i为根的子树选择kf[i][k]
int g[N][M];//g[i][j]前i组选j门课； 
void dp(int x)
{
	int i,j,k;
	for(i=1;i<=son[x][0];i++) 
		dp(son[x][i]);
	memset(g,0,sizeof(g));
	for(i=1;i<=son[x][0];i++) {
		int now=son[x][i];
		for(j=0;j<=m;j++) {
			for(k=0;k<=j;k++) {
				g[i][j]=max(g[i][j],g[i-1][j-k]+f[now][k]);
			}
		}
	}
	for(j=1;j<=m;j++) 
		f[x][j]=val[x]+g[son[x][0]][j-1];
} 
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) 
	{
		scanf("%d%d",&fa[i],&val[i]);
		int fat=fa[i];
		son[fat][++son[fat][0]]=i;
	}
	m++;
	dp(0);
	cout<<f[0][m];
	return 0;
}

