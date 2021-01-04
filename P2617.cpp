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

const int N=4e5+5;

int n,m;

struct Bits
{
	int c[N];
	inline int lowbit(int x) { return x&(-x); }
	inline void Update(int x,int y) 
	{
		for(;x<=n;x+=lowbit(x)) 
			c[x]+=y;
	}
	inline int Sum(int x) 
	{
		int res=0;
		for(;x>=1;x-=lowbit(x))
			res+=c[x];
		return res;
	}
}C;

struct Query
{
	int id; 
	int l,r,k;
	// id=0 , insert
	// id=-1 , erase
	// id=1 , query
}q[N],wl[N],wr[N];
int ans[N];

void solve(int l,int r,int ql,int qr)
{
	if(ql>qr) return;
	if(l==r) {
		for(int i=ql;i<=qr;i++) 
			if(q[i].id>0) ans[q[i].id]=l;
		return;
	}
	int mid=(l+r)>>1,cntl=0,cntr=0;
	for(int i=ql;i<=qr;i++) {
		if(q[i].id==0) {
			if(q[i].k<=mid) C.Update(q[i].l,1),wl[++cntl]=q[i];
			else wr[++cntr]=q[i];
		}
		else if(q[i].id==-1) {
			if(q[i].k<=mid) C.Update(q[i].l,-1),wl[++cntl]=q[i];
			else wr[++cntr]=q[i];
		}
		else {
			int t=C.Sum(q[i].r)-C.Sum(q[i].l-1);
			if(t>=q[i].k) wl[++cntl]=q[i];
			else q[i].k-=t,wr[++cntr]=q[i];
		}
	}
	
	for(int i=ql;i<=qr;i++) {
		if(q[i].id==0 && q[i].k<=mid) C.Update(q[i].l,-1);
		else if(q[i].id==-1 && q[i].k<=mid) C.Update(q[i].l,1); 
	}
	
	for(int j=1;j<=cntl;j++) q[ql+j-1]=wl[j];
	for(int j=1;j<=cntr;j++) q[ql+cntl+j-1]=wr[j];
	solve(l,mid,ql,ql+cntl-1),solve(mid+1,r,ql+cntl,qr);
}

int tot;
int a[N];
bool isquery[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y;
	char opt[2];
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		q[i].k=a[i],q[i].l=i,q[i].id=0;
	}
	
	for(tot=n,i=1;i<=m;i++) {
		scanf("%s",opt);
		if(*opt=='Q') {
			tot++;
			scanf("%d%d%d",&q[tot].l,&q[tot].r,&q[tot].k);
			q[tot].id=i;
			isquery[i]=true;
		}
		else {
			scanf("%d%d",&x,&y);
			tot++;
			q[tot].k=a[x],q[tot].id=-1,q[tot].l=x;
			tot++;
			q[tot].k=y,q[tot].id=0,q[tot].l=x;
			a[x]=y;
		}
	}
	
	solve(0,1e9,1,tot);
	
	for(i=1;i<=m;i++)
		if(isquery[i])
			printf("%d\n",ans[i]);
	return 0;
}

