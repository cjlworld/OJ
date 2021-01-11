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
#include<complex>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=2e5+5;

int n,m,siz;
int a[N];
vector<int> nums;

struct Query
{
	int l,r,id;
	inline bool operator<(const Query& t) const
	{
		if(l/siz!=t.l/siz) return l<t.l;
		else return r<t.r;
	}
}q[N];

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
//		printf("C.sum( %d ) is ",x);
		int res=0;
		for(;x>=1;x-=lowbit(x))
			res+=c[x];
//		printf("%d\n",res);
		return res;
	}
}C;

LL ans[N],cur;

inline void Add(int v,bool flag)
{
//	printf("now Add val %d\n",v);
	if(flag) cur+=C.Sum(n)-C.Sum(v);
	else cur+=C.Sum(v-1);
	C.Update(v,1);
//	printf("after that ,cur is %lld\n",cur);
}

inline void Sub(int v,bool flag)
{
	if(flag) cur-=C.Sum(n)-C.Sum(v);
	else cur-=C.Sum(v-1);
	C.Update(v,-1);
}

int main()
{
	freopen("1.in","r",stdin);
	int i;
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		nums.push_back(a[i]);
	}
	sort(nums.begin(),nums.end());
	nums.erase(unique(nums.begin(),nums.end()),nums.end());
	for(i=1;i<=n;i++) 
		a[i]=upper_bound(nums.begin(),nums.end(),a[i])-nums.begin();
		
	for(i=1;i<=m;i++) {
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].id=i;
	}
	siz=sqrt(n);
	sort(q+1,q+m+1);
	
	int hh=1,tt=0;
	for(i=1;i<=m;i++) {
		while(hh>q[i].l) Add(a[--hh],false);
		while(tt<q[i].r) Add(a[++tt],true);
		while(hh<q[i].l) Sub(a[hh++],false);
		while(tt>q[i].r) Sub(a[tt--],true);
		
		ans[q[i].id]=cur;
//		for(int j=1;j<=n;j++) 
//			printf("%d ",C.Sum(j)-C.Sum(j-1));
//		printf("\n");
	}
	
	for(i=1;i<=m;i++) 
		printf("%lld\n",ans[i]);
	return 0;
}

