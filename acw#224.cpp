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

LL fpow(LL x,LL k,LL MOD)
{
	LL res=1; x%=MOD;
	while(k) {
		if(k&1) res=res*x%MOD;
		x=x*x%MOD; k>>=1;
	}
	return res%MOD;
}

LL exgcd(LL a,LL b,LL &x,LL &y)
{
	if(b==0) {
		x=1,y=0;
		return a;
	}
	LL z=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return z;
}

LL Solve(LL a,LL b,LL c)
{
	LL x,y,z,t;
	z=exgcd(a,b,x,y);
	if(c%z) return -1;
	t=c/z;
	x*=t,y*=t;
	return (x%(b/z)+(b/z))%(b/z);
}

LL BSGS(LL a,LL b,LL MOD)
{
	map<LL,LL> mp;
	b%=MOD;
	LL t=sqrt(MOD)+1;
	LL i,j,val;
	for(j=0;j<t;j++) mp[b*fpow(a,j,MOD)%MOD]=j;
	a=fpow(a,t,MOD);
	if(a==0) return (b==0) ? 1 : (b!=1)*(-1);
	for(i=0;i<=t;i++) {
		val=fpow(a,i,MOD);
		if(mp.count(val)&&i*t-(j=mp[val])>=0) 
			return i*t-j;
	}
	return -1;
}

int T,K;

int main()
{
//	freopen("1.in","r",stdin);
	cin>>T>>K;
	LL y,z,p,ans;
	while(T--) {
		cin>>y>>z>>p;
		if(K==1) ans=fpow(y,z,p);
		else if(K==2) ans=Solve(y,p,z);
		else ans=BSGS(y,z,p);
		if(ans==-1) printf("Orz, I cannot find x!\n");
		else printf("%lld\n",ans);
	}
	return 0;
}

