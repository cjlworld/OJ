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

const int N=2e5+5;

struct Node
{
	LL sum,tag;
}t[4*N];

#define lc (now<<1)
#define rc (now<<1|1)

void pushup(int now) { t[now].sum=t[lc].sum+t[rc].sum; }

void Addtag(int now,LL key,int l,int r) 
{
	t[now].tag+=key;
	t[now].sum+=(r-l+1)*key;
//	printf("Addtag %d (%d , %d) : %lld \n",now,l,r,key);
}

void pushdown(int now,int l,int r)
{
	if(!t[now].tag || l==r) return;
	int mid=(l+r)>>1;
	Addtag(lc,t[now].tag,l,mid);
	Addtag(rc,t[now].tag,mid+1,r);
	t[now].tag=0;
}

void Modify(int now,int x,int y,LL key,int l,int r)
{
	if(x<=l && r<=y) 
		return Addtag(now,key,l,r);
		
	pushdown(now,l,r);
	int mid=(l+r)>>1;
	if(x<=mid) Modify(lc,x,y,key,l,mid);
	if(y>=mid+1) Modify(rc,x,y,key,mid+1,r);
	pushup(now);
}

LL query(int now,int x,int y,int l,int r)
{
	if(x<=l && r<=y) 
		return t[now].sum;
		
	int mid=(l+r)>>1; LL res=0;
	pushdown(now,l,r);
	if(x<=mid) res+=query(lc,x,y,l,mid);
	if(y>=mid+1) res+=query(rc,x,y,mid+1,r);
	return res;
}

int n,m;
LL a[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	LL x,y;
	char opt[20];
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) {
		scanf("%lld",&a[i]);
		Modify(1,i,n,a[i],1,n);
	}
	
	while(m--) {
		scanf("%s",opt);
		if(!strcmp(opt,"Query")) {
			scanf("%lld",&x);
			printf("%lld\n",query(1,1,x,1,n));
		}
		else {
			scanf("%lld%lld",&x,&y);
			
			Modify(1,x,n,-a[x],1,n);
			Modify(1,x,n,a[x]=y,1,n);
		}
	}
	return 0;
}

