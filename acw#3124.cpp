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

LL BSGS(LL a,LL b,LL p)
{
	if(1%p==b%p) return 0;
	LL k=sqrt(p)+1,ak=1;
	map<LL,LL> mp;
	for(LL i=0,j=b%p;i<k;i++,j=j*a%p)
		mp[j]=i;
	for(LL i=1;i<=k;i++) ak=ak*a%p;
	for(LL i=1,j=ak;i<=k;i++,j=j*ak%p) 
		if(mp.count(j)) return i*k-mp[j];
	return -1;
}

int main()
{
//	freopen("1.in","r",stdin);
	LL a,p,b,ans;
	while(cin>>a>>p>>b,a||p||b) {
		ans=BSGS(a,b,p);
		if(ans==-1) puts("No Solution");
		else printf("%lld\n",ans);
	}
	return 0;
}

