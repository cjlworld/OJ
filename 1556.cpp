#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
const int N=2e4+5;
const int LG=25;
int one[N];
int ver[2*N],Next[2*N],edge[2*N];
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
int n,m;
int w[N],dep[N];
int fa[N][LG];
void deal_first(int u,int father)
{
	int i,v;
	dep[u]=dep[father]+1;
	fa[u][0]=father;
	for(i=1;i<=21;i++) {
		if(fa[u][i-1]==0||fa[fa[u][i-1]][i-1]==0) break;
		fa[u][i]=fa[fa[u][i-1]][i-1];
	}
	for(i=one[u];i>0;i=Next[i]) {
		v=ver[i];
		if(v==father) 
			continue;
		w[v]=w[u]+edge[i];
		deal_first(v,u);
	}
	return;
}
inline int lca(int x,int y)
{
	int i,j;
	if(dep[x]<dep[y]) //let dep[x]>=dep[y]
		swap(x,y);
	for(i=21;i>=0;i--) {
		if(dep[fa[x][i]]>=dep[y])
			x=fa[x][i];
	}
	if(x==y) 
		return x;
	for(i=21;i>=0;i--) {
		if(fa[x][i]!=fa[y][i]) {
			x=fa[x][i];
			y=fa[y][i];
		}
	}
	return fa[x][0];
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(x,y,z);
		AddEdge(y,x,z);
	}
	deal_first(1,0);
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		z=w[x]+w[y]-2*w[lca(x,y)];
		printf("%d\n",z);
	}
	return 0;
}

