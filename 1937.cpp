#include<cmath>
#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
LL k,n;
LL ans=0;
LL quickpow(LL x,LL k)
{
	LL res=1;
	while(k) {
		if(k&1) res=res*x;
		x=x*x; k>>=1;
	}
	return res;
}
int main()
{
//	freopen("1.in","r",stdin);
	cin>>k>>n;
	int cnt=-1;
	while(n) {
		cnt++;
		if(n&1) ans+=quickpow(k,cnt);
		n>>=1;
	}
	cout<<ans;
	return 0;
}

