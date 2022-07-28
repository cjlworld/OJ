#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
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

const int N=2e5+5;

int one[N],idx;
int ver[N],Next[N];
void AddEdge(int a,int b)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
}

int dfn[N],org[N],times;
int son[N],fat[N],dep[N],top[N],siz[N];

void dfs1(int x,int fa)
{
	fat[x]=fa,dep[x]=dep[fa]+1,siz[x]=1;
	int i,y;
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		dfs1(y,x);
		if(siz[y]>siz[son[x]]) son[x]=y;	
		siz[x]+=siz[y];
	}	
}

void dfs2(int x)
{
	dfn[x]=++times,org[times]=x;
	if(x==son[fat[x]]) top[x]=top[fat[x]];
	else top[x]=x;
	
	int i,y;
	if(son[x]) dfs2(son[x]);
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(y==son[x]||y==fat[x]) continue;
		dfs2(y);
	}
}

struct Node
{
	int smid,sl,sr,sum;
	int tag;
	bool have;
	Node(int a,int b,int c,int d) : smid(a),sl(b),sr(c),sum(d) {}
	Node() {}
}t[4*N];
#define lc (now<<1)
#define rc (now<<1|1)

void pushup(Node &x,Node ls,Node rs)
{
	x.sum=ls.sum+rs.sum;
	x.sl=max(ls.sl,ls.sum+rs.sl);
	x.sr=max(rs.sr,rs.sum+ls.sr);
	x.smid=max(max(ls.smid,rs.smid),ls.sr+rs.sl);
	x.sl=max(x.sl,0),x.sr=max(x.sr,0),x.smid=max(x.smid,0);
}

void Addtag(int now,int l,int r,int tag)
{
	t[now].sum=(r-l+1)*tag;
	t[now].tag=tag,t[now].have=true;
	t[now].sl=t[now].sr=t[now].smid=max(t[now].sum,0);
}

void pushdown(int now,int l,int r)
{
	if((!t[now].have)||l==r) return;
	int mid=(l+r)>>1;
	Addtag(lc,l,mid,t[now].tag),Addtag(rc,mid+1,r,t[now].tag);
	t[now].have=false;
}

Node Query(int now,int x,int y,int l,int r)
{
	if(x<=l&&r<=y) return t[now];
	pushdown(now,l,r);
	int mid=(l+r)>>1;
	Node res(0,0,0,0);
	if(x<=mid) pushup(res,Query(lc,x,y,l,mid),res);
	if(y>=mid+1) pushup(res,res,Query(rc,x,y,mid+1,r));
	return res;
}

void modify(int now,int x,int y,int key,int l,int r)
{
	if(x<=l&&r<=y) return Addtag(now,l,r,key);
	pushdown(now,l,r);
	int mid=(l+r)>>1;
	if(x<=mid) modify(lc,x,y,key,l,mid);
	if(y>=mid+1) modify(rc,x,y,key,mid+1,r);
	pushup(t[now],t[lc],t[rc]);
}

int n,m;
int a[N];

int TQuery(int x,int y)
{
	Node r1(0,0,0,0),r2(0,0,0,0);
	while(top[x]!=top[y]) {
		if(dep[top[x]]>=dep[top[y]]) {
			pushup(r1,Query(1,dfn[top[x]],dfn[x],1,n),r1);
			x=top[x],x=fat[x];
		}
		else {
			pushup(r2,Query(1,dfn[top[y]],dfn[y],1,n),r2);
			y=top[y],y=fat[y];
		}
	}
	if(dep[x]>dep[y]) 
		pushup(r1,Query(1,dfn[y],dfn[x],1,n),r1);
	else pushup(r2,Query(1,dfn[x],dfn[y],1,n),r2);
	
	swap(r2.sl,r2.sr);
	pushup(r1,r2,r1);
	return r1.smid;
}

void TModify(int x,int y,int key)
{
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		modify(1,dfn[top[x]],dfn[x],key,1,n);
		x=top[x],x=fat[x];
	}
	if(dep[x]<dep[y]) swap(x,y);
	modify(1,dfn[y],dfn[x],key,1,n);
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,opt,x,y,z;
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(x,y),AddEdge(y,x);
	}
	dfs1(1,0),dfs2(1);
	for(i=1;i<=n;i++) 
		modify(1,dfn[i],dfn[i],a[i],1,n);
	
	scanf("%d",&m);
	while(m--) {
		scanf("%d%d%d",&opt,&x,&y);
		if(opt==1) printf("%d\n",TQuery(x,y));
		else scanf("%d",&z),TModify(x,y,z);
	}
	return 0;
}

