#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<bitset>
#include<vector>
#include<cstdio>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;

const int N=1e5+5;

struct Edge
{
	int u,v,w;
	bool operator<(Edge other) const { return w<other.w; }
	Edge(int x=0,int y=0,int z=0) : u(x),v(y),w(z) {}
}e[N];

int par[N];
int Find(int x) 
{
	if(par[x]==x) return x;
	else return par[x]=Find(par[x]);
}
void Join(int x,int y) { par[Find(x)]=Find(y); }


int n,m,cnt;
int ans;

int main()
{
//	freopen("1.in","r",stdin);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) par[i]=i;
	for(int i=1,x,y,z,opt;i<=m;i++) {
		scanf("%d%d%d%d",&opt,&x,&y,&z);
		if(opt==1) {
			ans+=z;
			Join(x,y);
		}
		else e[cnt++]=Edge(x,y,z);
	}
	
	sort(e,e+cnt);
	
	for(int i=0;i<cnt;i++) {
		if(Find(e[i].u)!=Find(e[i].v)) {
			ans+=e[i].w;
			Join(e[i].u,e[i].v);
		}
	}
	
	printf("%d\n",ans);
	return 0;
}

