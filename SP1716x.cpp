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
}

void Addtag(int now,int l,int r,int tag)
{
	t[now].sum=(r-l+1)*tag;
	t[now].tag=tag,t[now].have=true;
	t[now].sl=t[now].sr=t[now].smid=t[now].sum;
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
	Node xt,yt,z;
	if(x<=mid) xt=Query(lc,x,y,l,mid);
	if(y>=mid+1) yt=Query(rc,x,y,mid+1,r);
	
	if(x<=mid&&y>=mid+1) pushup(z,xt,yt);
	else if(x<=mid) z=xt;
	else z=yt;
	return z;
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

int main()
{
///	freopen("1.in","r",stdin);
	int i,opt,x,y;
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	for(i=1;i<=n;i++) 
		modify(1,i,i,a[i],1,n);
	
	scanf("%d",&m);
	while(m--) {
		scanf("%d%d%d",&opt,&x,&y);
		if(opt==1) printf("%d\n",Query(1,x,y,1,n).smid);
		else modify(1,x,x,y,1,n);
	}
	return 0;
}

