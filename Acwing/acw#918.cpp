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
int ver[M],Next[M];
void AddEdge(int a,int b)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
}
//======================================
int sum[4*N],tag[4*N];
#define lc (now<<1)
#define rc (now<<1|1)
inline void pushup(int now)
{
	sum[now]=sum[lc]+sum[rc];
}
inline void pushdown(int now,int l,int r)
{
	if(tag[now]==-1||l==r) return;
	int mid=(l+r)>>1;
	tag[lc]=tag[rc]=tag[now];
	sum[lc]=tag[lc]*(mid-l+1);
	sum[rc]=tag[rc]*(r-mid);
	tag[now]=-1;
}

int Query(int now,int x,int y,int l,int r)
{
	if(x<=l&&r<=y) return sum[now];
	pushdown(now,l,r);
	int mid=(l+r)>>1,res=0;
	if(x<=mid) res+=Query(lc,x,y,l,mid);
	if(y>=mid+1) res+=Query(rc,x,y,mid+1,r);
	return res;
}
void Color(int now,int x,int y,int key,int l,int r)
{
	if(x<=l&&r<=y) {
		tag[now]=key;
		sum[now]=tag[now]*(r-l+1);
		return;
	}
	pushdown(now,l,r);
	int mid=(l+r)>>1;
	if(x<=mid) Color(lc,x,y,key,l,mid);
	if(y>=mid+1) Color(rc,x,y,key,mid+1,r);
	pushup(now);
}
//==============================================
int siz[N],son[N],dep[N],fat[N];
int top[N],dfn[N],dfnt[N],times;

void dfs1(int x,int fa)
{
	int i,y;
	fat[x]=fa,dep[x]=dep[fa]+1,siz[x]=1;
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		dfs1(y,x);
		siz[x]+=siz[y];
		if(siz[y]>siz[son[x]]) son[x]=y;
	}
}

void dfs2(int x)
{
	int i,y;
	dfn[x]=++times;
	if(son[fat[x]]==x) top[x]=top[fat[x]];
	else top[x]=x;
	if(son[x]) dfs2(son[x]);
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(y==fat[x]||y==son[x]) continue;
		dfs2(y);
	}
	dfnt[x]=times;
}
//==================================
int n,m;
int TQuery(int x)
{
	LL res=0;
	while(x) {
		res+=(dfn[x]-dfn[top[x]]+1)-Query(1,dfn[top[x]],dfn[x],1,n);
		Color(1,dfn[top[x]],dfn[x],1,1,n);
		x=top[x],x=fat[x];
	}
	return res;
}

int main()
{
	int i,x;
	char opt[20];
	scanf("%d",&n);
	for(i=2;i<=n;i++) {
		scanf("%d",&x),x++;
		AddEdge(i,x),AddEdge(x,i);
	}
	dfs1(1,0),dfs2(1);
	memset(tag,-1,sizeof tag);
	scanf("%d",&m);
	while(m--) {
		scanf("%s%d",opt,&x),x++;
		if(!strcmp(opt,"install")) printf("%d\n",TQuery(x));
		else {
			printf("%d\n",Query(1,dfn[x],dfnt[x],1,n));
			Color(1,dfn[x],dfnt[x],0,1,n);
		}
	//	if(m%1000==0) cerr<<m<<endl;
	}
	return 0;
}

