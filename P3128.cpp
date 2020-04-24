#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
template<class T>
inline void read(T &x)
{
	x=0;
	bool sign=false;
	char c=getchar();
	while(c<'0'||c>'9') {
		if(c=='-') sign=true;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		x=(x<<1)+(x<<3)+(c-'0');
		c=getchar();
	}
	if(sign) x=~x+1;
	return;
}
//=============================
const int N=50000+5;
const int INF=(-1u)>>1;
int one[N];
int Next[2*N],ver[2*N];
int tot=0;
inline void AddEdge(int a,int b)
{
	tot++;
	Next[tot]=one[a];
	one[a]=tot;
	ver[tot]=b;
	return;
}
int up[N][21],dep[N];
int c[N];
void deal_first(int u,const int &fa)
{
	int i,j,v;
	dep[u]=dep[fa]+1;
	up[u][0]=fa;
	for(i=1;i<=20;i++) {
		if(up[up[u][i-1]][i-1]==0) 
			break;
		up[u][i]=up[up[u][i-1]][i-1];
	}
	for(i=one[u];i>0;i=Next[i]) {
		v=ver[i];
		if(v==fa) 
			continue;
		deal_first(v,u);
	}
	return;
}
inline int lca(int x,int y)
{
	int i;
	if(dep[x]<dep[y]) 
		swap(x,y);
	for(i=20;i>=0;i--) {
		if(dep[up[x][i]]>=dep[y]) 
			x=up[x][i];
	}
	if(x==y) 
		return x;
	for(i=20;i>=0;i--) {
		if(up[x][i]!=up[y][i]) {
			x=up[x][i];
			y=up[y][i];
		}
	}
	return up[x][0];
}
int a[N];
int ans=-INF;
void dfs(int u,int fa)
{
	a[u]=c[u];
	for(int i=one[u];i>0;i=Next[i]) 
		if(ver[i]!=fa) 
			dfs(ver[i],u),a[u]+=a[ver[i]];
	ans=max(ans,a[u]);
	return;
}
int n,m;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	read(n); read(m);
	for(i=1;i<=n-1;i++) {
		read(x); read(y);
		AddEdge(x,y);
		AddEdge(y,x);
	}
	deal_first(1,0);
	for(i=1;i<=m;i++) {
		read(x); read(y);
		z=lca(x,y);
		c[x]++;
		c[y]++;
		c[z]--;
		c[up[z][0]]--;
	}
	dfs(1,0);
	cout<<ans;
	return 0;
}

