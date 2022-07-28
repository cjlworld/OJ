#include<map>
#include<cmath>
#include<cstdio>
#include<iostream>

using namespace std;
typedef long long LL;

const LL INF=0x3f3f3f3f3f3f3f3f;

LL exgcd(LL a,LL b,LL& x,LL& y)
{
	if(b==0) {
		x=1,y=0;
		return a;
	}
	LL z=exgcd(b,a%b,y,x);
	y-=(a/b)*x;
	return z;
}

LL gcd(LL a,LL b) 
{
	if(b==0) return a;
	else return gcd(b,a%b);
}

LL inv(LL a,LL p) // 求 a 在 模p 意义下的逆元，保证 a,p 互质。 
{
	LL x,y;
	exgcd(a,p,x,y);
	x=(x%p+p)%p; // 最小正整数解。 
	return x;
}

LL bsgs(LL a,LL b,LL p)
{
	if(1%p==b%p) return 0;
//	unordered_map<LL,LL> mp;
	map<LL,LL> mp;
	LL k=sqrt(p)+1,ak=1;
	for(LL i=0,j=b%p;i<k;i++,j=j*a%p) 
		mp[j]=i;
	for(LL i=0;i<k;i++) ak=ak*a%p;
	for(LL i=1,j=ak;i<=k;i++,j=j*ak%p)
		if(mp.count(j)) return i*k-mp[j];
	return -INF;
}

LL exbsgs(LL a,LL b,LL p)
{
	b=(b%p+p)%p;
	if(1%p==b%p) return 0;
	LL d=gcd(a,p);
	if(d==1) return bsgs(a,b,p);
	else if(b%d) return -INF;
	else return exbsgs(a%(p/d),b/d*inv(a/d,p/d)%(p/d),p/d)+1;
}

int main()
{
//	freopen("1.in","r",stdin);
	LL a,p,b,ans;
	while(cin>>a>>p>>b,a||p||b) {
		ans=exbsgs(a,b,p);
		if(ans<0) puts("No Solution");
		else printf("%lld\n",ans);
	}
	return 0;
}

