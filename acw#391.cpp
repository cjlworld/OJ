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

const int N=1e6+5,INF=1e9+5;

int one[N],idx;
int Next[N],ver[N];
void AddEdge(int a,int b)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
}

int dep[N],top[N],siz[N],son[N],fat[N];

void dfs1(int x,int fa)
{
	int i,y;
	dep[x]=dep[fa]+1;
	fat[x]=fa;
	siz[x]=1;
	
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		dfs1(y,x);
		if(siz[y]>siz[son[x]]) 
			son[x]=y;
		siz[x]+=siz[y];
	}
}

void dfs2(int x)
{
	if(son[fat[x]]==x) top[x]=top[fat[x]];
	else top[x]=x;
	
	if(son[x]) dfs2(son[x]);
	int i,y;
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(y==son[x]||y==fat[x]) continue;
		dfs2(y);
	}
}

int lca(int x,int y)
{
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]]) 
			swap(x,y);
		x=top[x],x=fat[x];
	}
	if(dep[x]<dep[y]) return x;
	else return y;
}
int dis(int x,int y) { return dep[x]+dep[y]-2*dep[lca(x,y)]; }
int n,m;

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z,t,ans,tmp,ap;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(x,y),AddEdge(y,x);	
	}
	dfs1(1,0),dfs2(1);
	
	while(m--) {
		scanf("%d%d%d",&x,&y,&z);
		ans=INF;
		for(i=1;i<=3;i++) {
			t=lca(x,y),tmp=dep[x]-dep[t]+dep[y]-dep[t]+dis(z,t);
			if(tmp<ans) ans=tmp,ap=t;
			swap(x,z),swap(y,z);
		}
		printf("%d %d\n",ap,ans);
	}
	return 0;
}

