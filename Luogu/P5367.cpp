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

const int N=1e6+5;
const LL MOD=998244353;

LL a[N],n,jc[N];

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
	}
	int Sum(int x)
	{
		int res=0;
		for(;x>=1;x-=lowbit(x)) 
			res+=c[x];
		return res;
	}
}C;

int main()
{
	int i;
	LL ans=1; // 注意为 1 ，因为排名=比它小的排列数+1 
	scanf("%lld",&n);
	jc[0]=1;
	for(i=1;i<=n;i++) 
		C.Update(i,1),jc[i]=jc[i-1]*i%MOD;
	for(i=1;i<=n;i++) {
		scanf("%lld",&a[i]);
		ans=(ans+jc[n-i]*C.Sum(a[i]-1))%MOD;
		C.Update(a[i],-1);
	}
	cout<<ans<<endl;
	return 0;
}

