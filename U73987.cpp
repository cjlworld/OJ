#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
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

LL n;
LL sum;

int main()
{
//	freopen("1.in","r",stdin);
	scanf("%lld",&n);
	sum=n*(n+1)/2;
	LL x;
	for(int i=1;i<=n-1;i++)
		scanf("%lld",&x),sum-=x;
	cout<<sum;
	return 0;
}

