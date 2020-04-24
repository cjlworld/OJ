#include<bits/stdc++.h>
using namespace std;
const int M=1000+5;
const int N=100+5;
int t;
int n,m;
int tot=0;
int one[N],adj[N],ver[2*M],edge[2*M],Next[2*M];
int dis[N];
bool vis[N],exist[N];
void add(int a,int b,int c)
{
	tot++;
	if(one[a]==0) one[a]=tot;
	else Next[adj[a]]=tot;
	adj[a]=tot;
	ver[tot]=b;
	edge[tot]=c;
	return;
}
void Init()
{
	tot=0;
	memset(dis,0,sizeof(dis));
	memset(vis,0,sizeof(vis));
	memset(one,0,sizeof(one));
	memset(adj,0,sizeof(adj));
	memset(ver,0,sizeof(ver));
	memset(edge,0,sizeof(edge));
	memset(Next,-1,sizeof(Next));
	memset(exist,0,sizeof(exist));
	scanf("%d%d",&n,&m);
	int x,y,z;
	for(int i=1;i<=m;i++) {
		scanf("%d%d%d",&y,&x,&z);
		add(y-1,x,z);
		add(x,y-1,-z);
	}
	return;
}
bool spfa(int u)
{
	vis[u]=true; exist[N]=true;
	for(int i=one[u];i!=-1;i=Next[i]) {
		int v=ver[i],l=edge[i];
		if(dis[u]+l>dis[v]) {
			dis[v]=dis[u]+l;
			if(vis[v]) return false;
			if(!spfa(v)) return false;
		}
	}
	vis[u]=false;
	return true;
}
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&t);
	int i,j;
	while(t--) {
		Init();
		for(i=0;i<=n;i++) {
			if(exist[i]) continue;
			if(!spfa(i)) break;
		}
		if(i==n+1) puts("true");
		else puts("false");
	}
	return 0;
}

