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

const int N=1e5+5;

int n,m;

struct Bits
{
	int c[N];
	inline int lowbit(int x)
	{
		return x&(-x);
	}
	void Update(int x,int y)
	{
		for(;x<=n;x+=lowbit(x)) 
			c[x]+=y;
		return;
	}
	int sum(int x)
	{
		int res=0;
		for(;x>=1;x-=lowbit(x)) 
			res+=c[x];
		return res;
	}
}C;

struct Query
{
	int o;
	int l,r;
	int ans;
	inline bool operator<(const Query &t) const
	{
		return r<t.r;
	}
}q[2*N];

inline bool cmp(const Query &a,const Query &b)
{
	return a.o<b.o;
}

int a[N];

int last[(int)1e6+5];
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	
	scanf("%d",&m);
	for(i=1;i<=m;i++)  
		scanf("%d%d",&q[i].l,&q[i].r),
		q[i].o=i;
	
	sort(q+1,q+m+1);
	
	for(i=1;i<=m;i++) {
		for(j=q[i-1].r+1;j<=q[i].r;j++) {
			if(last[a[j]]) 
				C.Update(last[a[j]],-1);
			C.Update(j,1);
			last[a[j]]=j;
		}
		q[i].ans=C.sum(q[i].r)-C.sum(q[i].l-1);
	}
	
	sort(q+1,q+m+1,cmp);
	for(i=1;i<=m;i++) 
		printf("%d\n",q[i].ans);
	return 0;
}

