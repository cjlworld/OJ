#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
template<class T>
inline void read(T &x)
{
	x=0;
	bool sign=false;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar()) 
		if(c=='-') 
			sign=true;
	for(;c>='0'&&c<='9';c=getchar()) 
		x=(x<<1)+(x<<3)+(c-'0');
	if(sign) x=~x+1;
	return;
}
const int N=3e5+5;
int one[N];
int ver[2*N],Next[2*N];
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
int a[N],c[N];
void deal_first(int u,const int &fa)
{
	int i,j,v;
	dep[u]=dep[fa]+1;
	up[u][0]=fa;
	for(i=1;i<=20;i++) {
		if(!up[up[u][i-1]][i-1]) 
			break;
		up[u][i]=up[up[u][i-1]][i-1];
	}
	for(i=one[u];i>0;i=Next[i]) {
		v=ver[i];
		if(v==fa) continue;
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
inline void go(int u,int v)
{
	int tmp=lca(u,v);
	c[u]++;
	c[v]++;
	c[tmp]--;
	c[up[tmp][0]]--;
	return;
}
int sum[N];
void dfs(int u,const int &fa)
{
	int i;
	sum[u]=c[u];
	for(i=one[u];i>0;i=Next[i]) 
		if(ver[i]!=fa) 
			dfs(ver[i],u),sum[u]+=sum[ver[i]];
	return;
}
int n;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	read(n); 
	for(i=1;i<=n;i++) 
		read(a[i]);
	for(i=1;i<=n-1;i++) {
		read(x); read(y);
		AddEdge(x,y);
		AddEdge(y,x);
	}
	deal_first(1,0);
	for(i=1;i<=n-1;i++) {
		go(a[i],a[i+1]);
		c[a[i]]--;
		c[up[a[i]][0]]++;
	}
	dfs(1,0);
	sum[a[1]]++;
	sum[a[n]]--;
	for(i=1;i<=n;i++) 
		printf("%d\n",sum[i]);
	return 0;
}

