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

const int N=5e4+5;

struct Cow
{
	LL w,s;
	bool operator<(const Cow &t) const
	{
		return w+s<t.w+t.s;
	}
}a[N];

int n;

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%lld%lld",&a[i].w,&a[i].s);
	sort(a+1,a+n+1);
	LL sum=0,ans=-1e9;
	for(i=1;i<=n;i++) {
		ans=max(ans,sum-a[i].s);
		sum+=a[i].w;
	}
	printf("%lld\n",ans);
	return 0;
}

