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

const int N=50000;
int one[N],idx=1;
int Next[N],ver[N];
inline void AddEdge(int a,int b)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
}

int a[N];
int nxt[N];
int f[N]; // f[u] 表示从u出发能挖到的地雷的最大值 
int n;

int Dp(int u)
{
	if(f[u]!=-1) return f[u];
	f[u]=a[u];
	int y;
	for(int i=one[u];i>0;i=Next[i]) {
		y=ver[i];
		if(Dp(y)+a[u]>f[u]) {
			f[u]=Dp(y)+a[u];
			nxt[u]=y;
		}
	}
	return f[u];
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y;
	memset(f,-1,sizeof f);
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	while(scanf("%d%d",&x,&y),max(x,y)) 
		AddEdge(x,y);
	int ans=0,maxp=0;
	for(i=1;i<=n;i++) 
		if(Dp(i)>ans) ans=Dp(i),maxp=i;
	for(i=maxp;nxt[i];i=nxt[i]) 
		printf("%d-",i);
	printf("%d\n%d",i,ans);
	return 0;
}

