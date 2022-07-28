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
vector<int> nums;
int numt;

struct Bits
{
	LL c[N];
	inline int lowbit(int x)
	{
		return x&(-x);
	}
	void Update(int x,LL y)
	{
		for(;x<=numt;x+=lowbit(x)) 
			c[x]+=y;
	}
	LL Sum(int x) 
	{
		LL res=0;
		for(;x>=1;x-=lowbit(x)) 
			res+=c[x];
		return res;
	}
}C;

int n;
int a[N];

struct Query
{
	int x,y;
	// count [1,x] <= y , if(y<=x) --;
	bool operator<(const Query &t) const
	{
		return x<t.x;
	}
}q[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	scanf("%d",&n);
	for(i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		if(a[i]>n) nums.push_back(a[i]);
	}
	sort(nums.begin(),nums.end());
	nums.erase(unique(nums.begin(),nums.end()),nums.end());
	numt=nums.size()+n;
	for(i=1;i<=n;i++) {
		if(a[i]>n) a[i]=n+(upper_bound(nums.begin(),nums.end(),a[i])-nums.begin());
		q[i].x=min(a[i],n),q[i].y=i;
	}
	sort(q+1,q+n+1);
	LL ans=0;
	for(i=1;i<=n;i++) {
		for(j=q[i-1].x+1;j<=q[i].x;j++) 
			C.Update(a[j],1);
		ans+=C.Sum(numt)-C.Sum(q[i].y-1);
		if(q[i].x>=q[i].y) ans--;
	}
	printf("%lld\n",ans/2);
	return 0;
}

