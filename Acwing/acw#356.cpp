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
typedef pair<LL,LL> PLL;

const int N=6e5+5;
const LL INF=0x3f3f3f3f3f3f3f3f;

int one[N],idx;
int Next[N],ver[N],edge[N];
void AddEdge(int a,int b,LL c)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	edge[idx]=c;
}

struct Edge
{
	int a,b;
	LL c;
	bool operator<(const Edge &t) const
	{
		return c<t.c;
	}
}e[N];
bool vis[N];
int par[N];
int Find(int x) { return ((par[x]==x) ? x : par[x]=Find(par[x])); }

int n,m,maxk;

LL ans;

void Kruscal()
{
	int i,x,y;
	LL z;
	sort(e+1,e+m+1);
	for(i=1;i<=n;i++) par[i]=i;
	for(i=1;i<=m;i++) {
		x=e[i].a,y=e[i].b,z=e[i].c;
		if(Find(x)==Find(y)) continue;
		par[Find(x)]=Find(y);
		ans+=z;
		AddEdge(x,y,z),AddEdge(y,x,z);
		vis[i]=true;
	}
}

int up[N][21],dep[N];
LL f[N][21],f2[N][21];

void arg(LL &x,LL &y,LL z)
{
	if(z==x) return;
	else if(z>x) y=x,x=z;
	else if(z>y) y=z;
}

void deal_first(int x,int fa,LL edc)
{
	int i,y;
	dep[x]=dep[fa]+1;
	up[x][0]=fa;
	f[x][0]=edc;
	for(i=1;i<=20;i++) {
		if(!up[up[x][i-1]][i-1]) break;
		up[x][i]=up[up[x][i-1]][i-1];
		
		arg(f[x][i],f2[x][i],f[up[x][i-1]][i-1]);
		arg(f[x][i],f2[x][i],f2[up[x][i-1]][i-1]);
		arg(f[x][i],f2[x][i],f[x][i-1]);
		arg(f[x][i],f2[x][i],f2[x][i-1]);
		
		maxk=max(maxk,i);
	}
	
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		deal_first(y,x,edge[i]);
	}
}

PLL query(int x,int y)
{
	int i;
	LL res=-INF,res2=-INF;
	if(dep[x]<dep[y]) swap(x,y);
		 
	for(i=maxk;i>=0;i--) 
		if(dep[up[x][i]]>=dep[y]) {
			arg(res,res2,f[x][i]);
			arg(res,res2,f2[x][i]);
			x=up[x][i];
		}
	
	if(x==y) return PLL(res,res2);
	
	for(i=maxk;i>=0;i--) {
		if(up[x][i]!=up[y][i]) {
			arg(res,res2,f[x][i]);
			arg(res,res2,f2[x][i]);
			arg(res,res2,f[y][i]);
			arg(res,res2,f2[y][i]);
			x=up[x][i],y=up[y][i];
		}
	}
	arg(res,res2,f[x][0]);
	arg(res,res2,f2[x][0]);
	arg(res,res2,f[y][0]);
	arg(res,res2,f2[y][0]);
	return PLL(res,res2);
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y;
	LL z,t;
	PLL h;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++) 
		scanf("%d%d%lld",&e[i].a,&e[i].b,&e[i].c);
	Kruscal();
	memset(f,-0x3f,sizeof f);
	memset(f2,-0x3f,sizeof f2);
	deal_first(1,0,INF);
	
	LL delta=INF;
	for(i=1;i<=m;i++) {
		if(vis[i]) continue;
		x=e[i].a,y=e[i].b,z=e[i].c;
		h=query(x,y);
		
		if(z==h.first) t=h.second;
		else t=h.first;
		
		if(z-t<delta&&z!=t) delta=z-t; 
	}
	printf("%lld\n",ans+delta);
	return 0;
}

