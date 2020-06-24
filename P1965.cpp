#include<cstdio>
#include<iostream>
#define LL long long
#define rint register int
using namespace std;
LL quickpow(LL x,LL k,const LL &MOD)
{
	LL res=1%MOD;
	x=x%MOD;
	while(k>0) {
		if(k&1) res=res*x%MOD;
		x=x*x%MOD; k>>=1;
	}	
	return res%MOD;
}
LL n,m,k,x;
int main()
{
//	freopen("1.in","r",stdin);
	cin>>n>>m>>k>>x;
	cout<<(quickpow(10ll,k,n)*m%n+x)%n;
	return 0;
}

