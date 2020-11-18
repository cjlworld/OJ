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

const LL MOD=1e6+3;
const int N=2e6;

LL fac[N],ifac[N];
LL fpow(LL x,LL k,LL MOD)
{
	LL res=1; x%=MOD;
	while(k) {
		if(k&1) res=res*x%MOD;
		x=x*x%MOD; k>>=1;
	}
	return res%MOD;
}
LL C(LL n,LL m,LL MOD)
{
	return fac[n]*ifac[n-m]%MOD*ifac[m]%MOD;
}
LL lucas(LL n,LL m,LL MOD)
{
	if(n<MOD&&m<MOD) return C(n,m,MOD);
	else return C(n%MOD,m%MOD,MOD)*lucas(n/MOD,m/MOD,MOD)%MOD;
}

int main()
{
//	freopen("1.in","r",stdin);
	
	int i;
	fac[0]=ifac[0]=1;
	for(i=1;i<=MOD+2;i++) {
		fac[i]=fac[i-1]*i%MOD;
		ifac[i]=fpow(fac[i],MOD-2,MOD);
	}
	
	int T,n,L,R,r;
	scanf("%d",&T);
	while(T--) {
		cin>>n>>L>>R;
		r=R-L+1;
		cout<<(lucas(r+n,r,MOD)-1+MOD)%MOD<<endl; 
	}
	return 0;
}
// r 个球,分到 n+1 个不同的盒子里,第一个盒子至少一个,其余至少0个。
// r+n 个球，分到 n+1 个不同的盒子里,每个盒子至少一个。
// C(r+n-1,n) = C(r+n-1,r-1)

// sum i : 1-> n | C(r+i-1,r-1)
// +C(r+1-1,r
