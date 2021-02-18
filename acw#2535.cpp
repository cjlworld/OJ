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

const int N=1e5+5;

int n,m,k,siz;
int a[N];
vector<int> nums;

struct Query
{
	int l,r;
	int id;
	inline bool operator<(const Query& t) const
	{
		if(l/siz!=t.l/siz) return l<t.l;
		else return r<t.r;
	}
}q[N];

struct Range
{
	int posl,posr;
	int id,sign;
	Range(int posl,int posr,int id,int sign) :
		posl(posl),posr(posr),id(id),sign(sign) {}
};
vector<Range> quiz[N];

int f[N],g[N];
// f[i] 表示 [1,i] 中与 a[i] match 的数的个数。
// g[i] 表示当前与 i match 的数的个数。 
LL ans[N];

inline int count_bit(int num)
{
	int res=0;
	while(num) {
		if(num&1) res++;
		num>>=1;
	}
	return res;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	
	scanf("%d%d%d",&n,&m,&k);
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	
	for(i=0;i<(1<<14);i++) 
		if(count_bit(i)==k) 
			nums.push_back(i);
	
	// a[i]^a[j]=nums[]
	// a[i]=nums[]^a[j]
	for(i=1;i<=n;i++) {
		for(j=0;j<(int)nums.size();j++) 
			g[a[i]^nums[j]]++;
		f[i]=g[a[i]];
	}
	
	for(i=1;i<=m;i++) {
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].id=i;
	}
	
	siz=sqrt(n);
	sort(q+1,q+m+1);
	int hh=1,tt=0;
	for(i=1;i<=m;i++) {
		if(hh>q[i].l) quiz[tt].push_back(Range(q[i].l,hh-1,q[i].id,1));
		while(hh>q[i].l) ans[q[i].id]-=f[--hh]; 
		
		if(tt<q[i].r) quiz[hh-1].push_back(Range(tt+1,q[i].r,q[i].id,-1));
		while(tt<q[i].r) ans[q[i].id]+=f[++tt]-(k==0);
		
		if(hh<q[i].l) quiz[tt].push_back(Range(hh,q[i].l-1,q[i].id,-1));
		while(hh<q[i].l) ans[q[i].id]+=f[hh++];
		
		if(tt>q[i].r) quiz[hh-1].push_back(Range(q[i].r+1,tt,q[i].id,1));
		while(tt>q[i].r) ans[q[i].id]-=f[tt--]-(k==0);
	}
	
	memset(g,0,sizeof g);
	for(i=1;i<=n;i++) {
		for(j=0;j<(int)nums.size();j++) 
			g[a[i]^nums[j]]++;
		
		vector<Range>& v=quiz[i];
		for(;v.size();v.pop_back()) {
			Range& t=v.back();
			for(j=t.posl;j<=t.posr;j++)
				ans[t.id]+=t.sign*g[a[j]];
		}
	}
	
	for(i=1;i<=m;i++) ans[q[i].id]+=ans[q[i-1].id];
	for(i=1;i<=m;i++) 
		printf("%lld\n",ans[i]);
	return 0;
}

