#include<cstdio>
#include<iostream>
#include<cstring>
#define LL long long
using namespace std;
const int N=300+5;
const int M=N;
int n,m;//can,must
int par[N],c[N];
int son[N][N];
int f[N][M];//f[i][j]表示以i为根的子树中选择j门课
void Dp(int x)
{
	int i,j,k;
	int now;
	for(i=1;i<=son[x][0];i++) 
		Dp(son[x][i]);
	f[x][1]=c[x];
	f[x][0]=0;
	for(k=1;k<=son[x][0];k++) { //枚举组k 
		now=son[x][k];
		for(i=m;i>=2;i--) {
			for(j=1;j<=i-1;j++) {
				f[x][i]=max(f[x][i],f[x][i-j]+f[now][j]);
			}
		}
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	int i,j;
	for(i=1;i<=n;i++) {
		scanf("%d%d",&par[i],&c[i]);
		son[par[i]][++son[par[i]][0]]=i;
	}
	m++;
	Dp(0);
	printf("%d\n",f[0][m]);
	return 0;
}

