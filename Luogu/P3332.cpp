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

const int N=15450000,M=5e4+5;

int n,m;

vector<LL> nums;
struct quiz
{
	int opt,a,b;
	LL c;
}q[M];

struct Node
{
	int lc,rc;
	LL sum,tag;
}t[N];
int idx;

inline void newnode(int &now) { if(!now) now=++idx; }
inline void pushup(int now) { t[now].sum=t[t[now].lc].sum+t[t[now].rc].sum; }

void pushdown(int now,int l,int r)
{
	if(!t[now].tag||l==r) return;
	newnode(t[now].lc); newnode(t[now].rc);
	int mid=(l+r)>>1;
	t[t[now].lc].sum+=(mid-l+1)*t[now].tag;
	t[t[now].rc].sum+=(r-(mid+1)+1)*t[now].tag;
	t[t[now].lc].tag+=t[now].tag,t[t[now].rc].tag+=t[now].tag;
	t[now].tag=0;
	return;
}

void Update(int &now,int x,int y,int l,int r)
{
	newnode(now);
	if(x<=l&&r<=y) {
		t[now].tag++;
		t[now].sum+=r-l+1;
		return;	
	}
	pushdown(now,l,r);
	
	int mid=(l+r)>>1;
	if(x<=mid) Update(t[now].lc,x,y,l,mid);
	if(y>=mid+1) Update(t[now].rc,x,y,mid+1,r);
	
	pushup(now);
	return;
}

LL Getsum(int now,int x,int y,int l,int r)
{
	if(!now) return 0;
	if(x<=l&&r<=y) 
		return t[now].sum;
	pushdown(now,l,r);
	
	int mid=(l+r)>>1; LL res=0;
	if(x<=mid) res+=Getsum(t[now].lc,x,y,l,mid);
	if(y>=mid+1) res+=Getsum(t[now].rc,x,y,mid+1,r);
	
	return res;
}

#define lc (now<<1)
#define rc (now<<1|1)
int rt[N];

void Insert(int now,int key,int x,int y,int l,int r)
{
	Update(rt[now],x,y,1,n);
	if(l==r) return;
	int mid=(l+r)>>1;
	if(key<=mid) Insert(lc,key,x,y,l,mid);
	else Insert(rc,key,x,y,mid+1,r);
	return;
}

int Findkth(int now,LL rank,int x,int y,int l,int r)
{
	if(l==r) return l;
	LL tmp=Getsum(rt[rc],x,y,1,n); int mid=(l+r)>>1;
	if(rank>tmp) return Findkth(lc,rank-tmp,x,y,l,mid);
	else return Findkth(rc,rank,x,y,mid+1,r);
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++) {
		scanf("%d%d%d%lld",&q[i].opt,&q[i].a,&q[i].b,&q[i].c);
		if(q[i].opt==1) nums.push_back(q[i].c);
	}
	sort(nums.begin(),nums.end());
	nums.erase(unique(nums.begin(),nums.end()),nums.end());
	for(i=1;i<=m;i++) 
		if(q[i].opt==1)
			q[i].c=(int)(lower_bound(nums.begin(),nums.end(),q[i].c)-nums.begin())+1;
	
	for(i=1;i<=m;i++) {
		if(q[i].opt==1) Insert(1,q[i].c,q[i].a,q[i].b,1,nums.size());
		else printf("%lld\n",nums[Findkth(1,q[i].c,q[i].a,q[i].b,1,nums.size())-1]);
	} 
	return 0;
}
// DeBug 
// 1. 把 k 大也离散化了
// 2. 第k大不是第k小 , 要注意反过来 
// 3. long long 
