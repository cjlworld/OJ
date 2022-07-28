#pragma comment(linker, "/STACK:1024000000,1024000000")
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#define LL long long
using namespace std;
const int N=1e5+5;
const LL INF=1e15;
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
struct node
{
	int l,r;
	LL val; //max
	LL tag;
	#define l(x) t[x].l
	#define r(x) t[x].r
	#define val(x) t[x].val
	#define tag(x) t[x].tag 
};
node t[4*N];
#define lc (now<<1)
#define rc (now<<1|1)
LL a[N];
inline void push_up(const int &now)
{
	val(now)=max(val(lc),val(rc));
	return;
}
inline void push_down(const int &now)
{
	if(l(now)==r(now)) {
		tag(now)=0;
		return;
	}
	if(!tag(now)) return;
	val(lc)+=tag(now);
	val(rc)+=tag(now);
	tag(lc)+=tag(now);
	tag(rc)+=tag(now);
	tag(now)=0;
	return;
}
void Build(int now,int l,int r)
{
	l(now)=l;
	r(now)=r;
	if(l==r) {
		val(now)=a[l];
		tag(now)=0;
		return;
	}
	int mid=(l+r)>>1;
	Build(lc,l,mid);
	Build(rc,mid+1,r);
	push_up(now);
	return;
}
void modify(int now,const int &x,const int &y,const int &key)
{
	if(y<l(now)||x>r(now)) 
		return;
	if(x<=l(now)&&r(now)<=y) {
		val(now)+=key;
		tag(now)+=key;
		return;
	}
	push_down(now);
	modify(lc,x,y,key);
	modify(rc,x,y,key);
	push_up(now);
	return;
}
LL query(int now,const int &x,const int &y)
{
	if(y<l(now)||x>r(now)) 
		return -INF;
	if(x<=l(now)&&r(now)<=y) 
		return val(now);
	push_down(now);
	LL p1,p2,res;
	p1=query(lc,x,y);
	p2=query(rc,x,y);
	res=max(p1,p2);
	return res;
}
int dfn[N],dfnt[N],times=0;
LL cost[N];
void dfs(int now,const int &fa)
{
	dfn[now]=++times;
	a[dfn[now]]=a[dfn[fa]]+cost[now];
	for(int i=one[now];i>0;i=Next[i]) 
		if(ver[i]!=fa) 
			dfs(ver[i],now);
	dfnt[now]=times;
	return;
}
void clear()
{
	memset(one,0,sizeof one);
	memset(ver,0,sizeof ver);
	memset(Next,0,sizeof Next);
	tot=0;
	memset(t,0,sizeof t);
	memset(a,0,sizeof a);
	memset(dfn,0,sizeof dfn);
	memset(dfnt,0,sizeof dfnt);
	times=0;
	memset(cost,0,sizeof cost);
	return;
}
int T;
int n,m;
int main()
{
//	freopen("1.in","r",stdin);
	int t,i,j;
	int opt,x,y;
	LL z;
	scanf("%d",&T);
	for(t=1;t<=T;t++) {
		printf("Case #%d:\n",t);
		clear();
		scanf("%d%d",&n,&m);
		for(i=1;i<=n-1;i++) {
			scanf("%d%d",&x,&y);
			x++; y++;
			AddEdge(x,y);
			AddEdge(y,x);
		}		
		for(i=1;i<=n;i++) 
			scanf("%lld",&cost[i]);
		dfs(1,0);
		Build(1,1,n);
		while(m--) {
			scanf("%d%d",&opt,&x);
			x++;
			if(opt==0) {
				scanf("%lld",&z);
				modify(1,dfn[x],dfnt[x],z-cost[x]);
				cost[x]=z;
			}
			else 
				printf("%lld\n",query(1,dfn[x],dfnt[x]));
		}
	}
	return 0;
}

