#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
#define LL long long
using namespace std;
const int N=1e4+5;
const int INF=(-1u)>>1;
int one[N];
int Next[10*N],ver[10*N],edge[10*N];
int tot=0;
inline void AddEdge(int a,int b,int c)
{
	tot++;
	Next[tot]=one[a];
	one[a]=tot;
	ver[tot]=b;
	edge[tot]=c;
	return;
}
struct Edge
{
	int x,y,w;
}a[5*N];
inline bool cmp(const Edge &a,const Edge &b)
{
	return a.w>b.w;
}
int par[N];
int Find(int x)
{
	if(x!=par[x]) return par[x]=Find(par[x]);
	return x;
}
int n,m,q;
void Krucal()
{
	int i,j;
	int x,y,z;
	int pool=0;
	for(i=1;i<=n;i++) 
		par[i]=i;
	sort(a+1,a+m+1,cmp);
	for(i=1;i<=m;i++) {
		x=Find(a[i].x);
		y=Find(a[i].y);
		if(x==y) continue;
		pool++;
		AddEdge(a[i].x,a[i].y,a[i].w);
		AddEdge(a[i].y,a[i].x,a[i].w);
		par[x]=y;
		if(pool==n-1) return; 
	}
	return;
}
int up[N][21];
int Min[N][21];
int dep[N];
void deal_first(int u,const int &fa)
{
	int i,j,v,e;
	dep[u]=dep[fa]+1;
	up[u][0]=fa;
	for(i=1;i<=20;i++) {
		if(up[up[u][i-1]][i-1]==0||up[u][i-1]==0) 
			break;
		up[u][i]=up[up[u][i-1]][i-1];
		Min[u][i]=min(Min[u][i-1],Min[up[u][i-1]][i-1]);
	}
	for(i=one[u];i>0;i=Next[i]) {
		v=ver[i]; e=edge[i];
		if(v==fa) continue;
		Min[v][0]=e;
		deal_first(v,u);
	}
	return;
}
inline int lca(int x,int y)
{
	int i,j;
	int res=INF;
	if(dep[x]<dep[y]) 
		swap(x,y);
	for(i=20;i>=0;i--) {
		if(dep[up[x][i]]>=dep[y]) 
			res=min(res,Min[x][i]),x=up[x][i];
	}
	if(x==y) 
		return res;
	for(i=20;i>=0;i--) {
		if(up[x][i]==up[y][i]) 
			continue;
		res=min(res,Min[x][i]);
		res=min(res,Min[y][i]);
		x=up[x][i];
		y=up[y][i];
	}
	res=min(res,Min[x][0]);
	res=min(res,Min[y][0]);
	return res;
}
bool vis[N];
void rebuild()
{
	int i,j;
	for(i=1;i<=n;i++) 
		par[i]=Find(i);
	memset(Min,0x3f,sizeof Min);
	for(i=1;i<=n;i++) 
		if(!vis[par[i]]) 
			deal_first(par[i],0),vis[par[i]]=true;
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++) 
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].w);
	Krucal();
	rebuild();
	scanf("%d",&q);
	while(q--) {
		scanf("%d%d",&x,&y);
		if(par[x]!=par[y]) 
			puts("-1");
		else printf("%d\n",lca(x,y));
	}
	return 0;
}

