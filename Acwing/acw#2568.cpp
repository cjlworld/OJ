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

const int N=1e5+5,M=2*N;
int one[N],idx=1;
int Next[M],ver[M];
void AddEdge(int a,int b)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
}

int n,m;

struct Bits
{
	LL c[N];
	inline int lowbit(int x)
	{
		return x&(-x);
	}
	void Update(int x,LL y)
	{
		for(;x<=n;x+=lowbit(x)) 
			c[x]+=y;
	}
	LL Sum(int x)
	{
		LL res=0;
		for(;x>=1;x-=lowbit(x)) 
			res+=c[x];
		return res;
	}
}C1,C2;
// C1 : c[]
// C2 : i*c[]
void Modify(int l,int r,LL z)
{
	C1.Update(l,z),C1.Update(r+1,-z);
	C2.Update(l,l*z),C2.Update(r+1,-(r+1)*z);
}
LL Prefix(LL x) { return C1.Sum(x)*(x+1)-C2.Sum(x); }

int top[N],dfn[N],dfnt[N],times,org[N];
int dep[N],fat[N],son[N],siz[N];
void dfs1(int x,int fa)
{
	int i,y;
	fat[x]=fa,siz[x]=1,dep[x]=dep[fa]+1;
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		dfs1(y,x);
		if(siz[y]>siz[son[x]]) son[x]=y;
	}
}
void dfs2(int x)
{
	int i,y;
	dfn[x]=++times,org[times]=x;
	if(son[fat[x]]==x) top[x]=top[fat[x]];
	else top[x]=x;
	if(son[x]) dfs2(son[x]);
	for(i=one[x];i>0;i=Next[i]) {
		y=ver[i];
		if(y==fat[x]||y==son[x]) continue;
		dfs2(y);	
	}
	dfnt[x]=times;
}

LL TQuery(int x,int y)
{
	LL res=0;
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		res+=Prefix(dfn[x])-Prefix(dfn[top[x]]-1);
		x=top[x],x=fat[x];
	}
	if(dep[x]<dep[y]) swap(x,y);
	res+=Prefix(dfn[x])-Prefix(dfn[y]-1);
	return res;
}

void TModify(int x,int y,LL k)
{
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		Modify(dfn[top[x]],dfn[x],k);
		x=top[x],x=fat[x];
	}
	if(dep[x]<dep[y]) swap(x,y);
	Modify(dfn[y],dfn[x],k);
}

LL a[N];
int main()
{
//	freopen("1.in","r",stdin);
	int i,x,y,opt;
	LL z;
	scanf("%d",&n);
	for(i=1;i<=n;i++)	
		scanf("%lld",&a[i]);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(x,y),AddEdge(y,x);
	}
	dfs1(1,0),dfs2(1);
	for(i=1;i<=n;i++) 
		Modify(dfn[i],dfn[i],a[i]);
	scanf("%d",&m);
	while(m--) {
		scanf("%d%d",&opt,&x);
		if(opt==1) {
			scanf("%d%lld",&y,&z);
			TModify(x,y,z);
		}
		else if(opt==2) {
			scanf("%lld",&z);
			Modify(dfn[x],dfnt[x],z);
		}
		else if(opt==3) {
			scanf("%d",&y);
			printf("%lld\n",TQuery(x,y));
		}
		else printf("%lld\n",Prefix(dfnt[x])-Prefix(dfn[x]-1));
	}
	return 0;
}

