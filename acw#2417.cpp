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
#include<complex>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<double,double> PDD;
typedef PDD Point;
typedef PDD Vector;

#define x first
#define y second

Vector operator-(Vector a,Vector b) { return Vector(a.x-b.x,a.y-b.y); }
double length(Vector a) { return sqrt(a.x*a.x+a.y*a.y); }
double dist(Point a,Point b) { return length(a-b); }

const int N=256,M=1e4+5;
const double INF=1e9;

struct Edges
{
	int u,v;
	double val;
	Edges(int u=0,int v=0,double val=0) :
		u(u),v(v),val(val) {}
}e[M];

Point a[N];

int n,m,rt;
int fa[N];
double min_pre[N];
int col[N],all;
int vis[N];

double DMST()
{
	double res=0;
	while(true) {
		all=0;
		memset(fa,0,sizeof fa);
		memset(col,0,sizeof col);
		memset(vis,0,sizeof vis);
		for(int i=1;i<=n;i++) min_pre[i]=INF;
		
		for(int i=1;i<=m;i++) 
			if(min_pre[e[i].v]>e[i].val)
				fa[e[i].v]=e[i].u,min_pre[e[i].v]=e[i].val;
				
		for(int i=1;i<=n;i++) 
			if(i!=rt && min_pre[i]==INF) return -1;
		for(int i=1;i<=n;i++) {
			if(i==rt) continue;
			res+=min_pre[i];
			
			int u=i;
			while(u!=rt && !vis[u] && !col[u]) 
				vis[u]=i,u=fa[u];
			if(u!=rt && vis[u]==i) {
				col[u]=++all;
				for(int v=fa[u];v!=u;v=fa[v]) 
					col[v]=all;
			}
		}
		if(!all) return res;
		
		for(int i=1;i<=n;i++) 
			if(!col[i]) col[i]=++all;
		int tot=0;
		for(int i=1;i<=m;i++) {
			int u=col[e[i].u],v=col[e[i].v];
			if(u==v) continue;
			e[++tot]=Edges(u,v,e[i].val-min_pre[e[i].v]);
		}
		n=all; m=tot; rt=col[rt];
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,x,y;
	
	while(scanf("%d%d",&n,&m)==2) {
		for(i=1;i<=n;i++) 
			scanf("%lf%lf",&a[i].x,&a[i].y);
		for(i=1;i<=m;i++) {
			scanf("%d%d",&x,&y);
			e[i]=Edges(x,y,dist(a[x],a[y]));
		}
		rt=1;
		double ans=DMST();
		if(ans<0) puts("poor snoopy");
		else printf("%.2lf\n",ans); 
	}
	return 0;
}

