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

const int N=6e5+5;

int n,m,Q;

struct Bits
{
	LL c[N];
	inline int lowbit(int x) { return x&(-x); }
	inline void Update(int x,LL y)
	{
		for(;x<=m;x+=lowbit(x)) 
			c[x]+=y;
	}
	inline LL Sum(int x)
	{
		LL res=0;
		for(;x>=1;x-=lowbit(x)) 
			res+=c[x];
		return res;
	}
}C;

struct Query
{
	int id;
	int l,r;
	LL k;
}q[N],wl[N],wr[N],a[N];
int ans[N];
vector<int> v[N];

void solve(int l,int r,int ql,int qr)
{
	if(ql>qr) return;
	if(l==r) {
		for(int i=ql;i<=qr;i++)
			ans[q[i].id]=l;
		return;
	}
	int mid=(l+r)>>1,cntl=0,cntr=0;
	for(int i=l;i<=mid;i++) {
		if(a[i].l<=a[i].r) C.Update(a[i].l,a[i].k),C.Update(a[i].r+1,-a[i].k);
		else C.Update(a[i].l,a[i].k),C.Update(1,a[i].k),C.Update(a[i].r+1,-a[i].k);
	}
	for(int i=ql;i<=qr;i++) {
		LL t=0,x=q[i].id;
		for(int j=v[x].size()-1;j>=0;j--) {
			t+=C.Sum(v[x][j]);
			if(t>=q[i].k) break;
		}
		if(t>=q[i].k) wl[++cntl]=q[i];
		else q[i].k-=t,wr[++cntr]=q[i];
	}
	
	for(int i=l;i<=mid;i++) {
		if(a[i].l<=a[i].r) C.Update(a[i].l,-a[i].k),C.Update(a[i].r+1,a[i].k);
		else C.Update(a[i].l,-a[i].k),C.Update(1,-a[i].k),C.Update(a[i].r+1,a[i].k);
	}
	
	for(int i=1;i<=cntl;i++) q[ql+i-1]=wl[i];
	for(int i=1;i<=cntr;i++) q[ql+cntl+i-1]=wr[i];
	solve(l,mid,ql,ql+cntl-1),solve(mid+1,r,ql+cntl,qr);
}

int main()
{
	int i,x;
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++) {
		scanf("%d",&x);
		v[x].push_back(i);
	}
	for(i=1;i<=n;i++) {
		scanf("%lld",&q[i].k);
		q[i].id=i;
	}
	
	scanf("%d",&Q);
	for(i=1;i<=Q;i++) 
		scanf("%d%d%lld",&a[i].l,&a[i].r,&a[i].k);
	solve(1,Q+1,1,n);
	
	for(i=1;i<=n;i++) {
		if(ans[i]<=Q) printf("%d\n",ans[i]);
		else printf("NIE\n");
	} 
		
	return 0;
}

