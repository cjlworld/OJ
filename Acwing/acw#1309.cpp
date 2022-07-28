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

const LL MOD=100003;
const int N=4056;

LL fpow(LL x,LL k,LL MOD)
{
	LL res=1; x%=MOD;
	while(k) {
		if(k&1) res=res*x%MOD;
		x=x*x%MOD; k>>=1;
	}
	return res%MOD;
}

LL fac[N],ifac[N];

LL calc(int a,int b,int i)
{
	if(i>a||i>b||i<0) return 0;
	else return fac[a]*fac[b]%MOD*ifac[a-i]%MOD*ifac[b-i]%MOD*ifac[i]%MOD;
}

int a,b,c,d,k,n;
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	
	cin>>a>>b>>c>>d>>k;
	n=a+b+c+d;
	fac[0]=ifac[0]=1;
	for(i=1;i<=n;i++) {
		fac[i]=fac[i-1]*i%MOD;
		ifac[i]=fpow(fac[i],MOD-2,MOD);
	}
	
	LL ans=0;
	for(i=0;i<=k;i++) 
		ans=(ans+calc(a,b,i)*calc(a+c-i,d,k-i))%MOD;
	cout<<ans<<endl;
	return 0;
}

