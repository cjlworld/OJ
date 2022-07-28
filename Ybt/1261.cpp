#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=1000,INF=1e9+5;
int n;
int w[N][N];
int f[N],pre[N];

int Dp(int u)
{
	if(u==1) return f[u]=0;
	if(f[u]!=-1) return f[u];
	f[u]=INF;
	for(int i=1;i<=n;i++) 
		if(w[i][u]&&Dp(i)+w[i][u]<f[u]) {
			f[u]=Dp(i)+w[i][u];
			pre[u]=i;
		}
	return f[u];
}

void print(int u)
{
	if(u!=1) print(pre[u]);
	printf("%d ",u);
}

int main()
{
//	freopen("1.in","r",stdin);
	memset(f,-1,sizeof f);
	cin>>n;
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=n;j++) 
			scanf("%d",&w[i][j]);
	printf("minlong=%d\n",Dp(n));
	print(n);
	return 0;
}

