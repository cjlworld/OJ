#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
int n,m;
int root;
int one[N];
int ver[2*N],Next[2*N];
int tot=0;
void add(int a,int b)
{
	tot++;
	Next[tot]=one[a];
	one[a]=tot;
	ver[tot]=b;
	return;
}
int dep[N];
int up[N][21];
void deal_first(int u,int fa)
{
	dep[u]=dep[fa]+1;
	int i,j;
	up[u][0]=fa;
	for(i=1;i<=20;i++) {
		if(up[u][i-1]==0||up[up[u][i-1]][i-1]==0) 
			break;
		up[u][i]=up[up[u][i-1]][i-1];
	}
	int v;
	for(i=one[u];i>0;i=Next[i]) {
		v=ver[i];
		if(v==fa) continue;
		deal_first(v,u);
	}
	return;
}
int lca(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y);
	int i,j;
	for(i=20;i>=0;i--) {
		if(dep[up[x][i]]>=dep[y]) 
			x=up[x][i];
		if(dep[x]==dep[y]) break;
 	}
	if(x==y) return x;
	for(i=20;i>=0;i--) {
		if(up[x][i]!=up[y][i]) {
			x=up[x][i];
			y=up[y][i];
		}
	}
	return up[x][0];
}
int main()
{
	scanf("%d%d%d",&n,&m,&root);
	int i,j;
	int x,y,z;
	for(i=1;i<=n-1;i++) {
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	deal_first(root,0);
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		printf("%d\n",lca(x,y));
	}
	return 0;
}
