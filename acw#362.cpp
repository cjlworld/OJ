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

int T,n;
struct Bits
{
	int n,c[N];
	inline int lowbit(int x)
	{
		return x&(-x);
	}
	void Update(int x,int y)
	{
		for(;x<=n;x+=lowbit(x)) 
			c[x]+=y;
	}
	int Sum(int x)
	{
		int res=0;
		for(;x>=1;x-=lowbit(x)) 
			res+=c[x];
		return res;
	}
}C;

int par[N];
int Find(int x)
{
	if(par[x]!=x) return par[x]=Find(par[x]);
	else return x;
}

struct Segment
{
	int l,r,sum;
	bool operator<(const Segment &t) const
	{
		return r<t.r;
	}
}a[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int need;
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].sum);
	sort(a+1,a+n+1);
	C.n=a[n].r;
	for(i=1;i<=a[n].r;i++) par[i]=i;
	for(i=1;i<=n;i++) {
		need=a[i].sum-(C.Sum(a[i].r)-C.Sum(a[i].l-1));
		for(j=Find(a[i].r);j>=a[i].l&&need>0;j=Find(j-1)) {
			par[j]=j-1;
			C.Update(j,1);
			need--;
		}
	}
	printf("%d\n",C.Sum(C.n));
	return 0;
}

