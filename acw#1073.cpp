#include<set>
#include<map>
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

const int N=10000+5,M=2*N+5,INF=1e9+5;

int one[N],idx=1;
int Next[M],ver[M],edge[M];
inline void AddEdge(int a,int b,int c)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	edge[idx]=c;
	return;
}

int n;
int f[N][3],g[N];
// f[i][2] 表示 i 节点上行的最长路
// f[i][0]和f[i][1]分别表示 i 节点下行的最长路和次长路

void Dp(int x,int fa)
{
	int i,y;
	for(i=one[x];i>0;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		Dp(y,x);
		if(f[y][0]+edge[i]>f[x][0]) {
			f[x][1]=f[x][0],f[x][0]=f[y][0]+edge[i];
			g[x]=y;
		}
		else if(f[y][0]+edge[i]>f[x][1]) 
			f[x][1]=f[y][0]+edge[i];
	}
	return;
}

int ans,cmax=INF;

void Dp2(int x,int fa,int id)
{
	int i,y;
	
	if(g[fa]==x) f[x][2]=f[fa][1]+edge[id];
	else f[x][2]=f[fa][0]+edge[id];
	f[x][2]=max(f[x][2],f[fa][2]+edge[id]);
	
	if(max(f[x][0],f[x][2])<cmax) 
		ans=x,cmax=max(f[x][0],f[x][2]);
	
	for(i=one[x];i>0;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		Dp2(y,x,i);
	}
//	printf("%d : %d , %d , %d\n",x,f[x][0],f[x][1],f[x][2]);
	return;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,x,y,z;
	scanf("%d",&n);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(x,y,z);
		AddEdge(y,x,z);
	}
	Dp(1,0);
	Dp2(1,0,0);
	cout<<cmax;
	return 0;
}

