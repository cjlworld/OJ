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

LL n,h,a,b;
template<class T> inline T mabs(T a) { return ((a<0) ? -a : a); }
LL Judge(LL x,LL y,LL aimx,LL aimy)
{
	if((aimx-x)%a||(aimy-y)%b) return -1ll;
	LL sta=mabs(aimx-x)/a,stb=mabs(aimy-y)/b;
	if(mabs(sta-stb)&1) return -1ll;
	return max(sta,stb);
}

int main()
{
//	freopen("1.in","r",stdin);
	int T,i;
	LL x,y,ans[4],fans;
	cin>>T;
	while(T--) {
		scanf("%lld%lld%lld%lld%lld%lld",&n,&h,&x,&y,&a,&b);
		ans[0]=Judge(x,y,n,1);
		ans[1]=Judge(x,y,n,h);
		ans[2]=Judge(x,y,1,1);
		ans[3]=Judge(x,y,1,h);
		fans=ans[0];
		for(i=1;i<4;i++) 
			if(fans==-1||(ans[i]!=-1&&ans[i]<fans)) 
				fans=ans[i];
		printf("%lld\n",fans);
	}
	return 0;
}

