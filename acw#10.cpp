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

const int N=105,M=256;
int one[N],idx=1;
int Next[M],ver[M];
inline void AddEdge(int a,int b)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	return;
}

int n,m;
int f[N][N]; // f[i][j] 表示以i号节点为根的子树内，选容量为j的物品的 最大价值
int v[N],w[N];
int root=0;

void Dp(int x)
{
	int i,j,k,y;
	
	memset(f[x],0xc0,sizeof f[x]);
	f[x][v[x]]=w[x];
	
	for(i=one[x];i>0;i=Next[i]) {
		y=ver[i];
		Dp(y);
		for(j=m;j>=0;j--) 
			for(k=0;k<=j;k++) 
				f[x][j]=max(f[x][j],f[x][j-k]+f[y][k]);
	}
//	printf("%d : ",x);
//	for(j=0;j<=m;j++) 
//		printf("%d ",f[x][j]);
//	printf("\n");
	return;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,z;
	cin>>n>>m;
	for(i=1;i<=n;i++) {
		cin>>v[i]>>w[i]>>z;
		if(z==-1) root=i;
		else AddEdge(z,i);
	}
	Dp(root);
	int ans=0;
	for(i=0;i<=m;i++) 
		ans=max(ans,f[root][i]);
	cout<<ans;
	return 0;
}

