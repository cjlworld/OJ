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

const LL MOD=1e9+7;
const int N=1e6+5;

LL fpow(LL x,LL k,LL MOD)
{
    LL res=1; x%=MOD;
    while(k) {
        if(k&1) res=res*x%MOD;
        x=x*x%MOD; k>>=1;
    }
    return res%MOD;
}

LL fac[N],ifac[N],f[N];
LL C(int n,int m) { return fac[n]*ifac[n-m]%MOD*ifac[m]%MOD; }

int n,m,T;

int main()
{
//	freopen("1.in","r",stdin);
    int i;

    fac[0]=ifac[0]=1;
    for(i=1;i<=N-1;i++) {
        fac[i]=fac[i-1]*i%MOD;
        ifac[i]=fpow(fac[i],MOD-2,MOD);
    }
	
	f[0]=1,f[1]=0,f[2]=1;
	for(i=3;i<=N-1;i++) 
		f[i]=(f[i-1]+f[i-2])*(i-1)%MOD;
	
    scanf("%d",&T);
    while(T--) {
    	scanf("%d%d",&n,&m);
    	printf("%lld\n",C(n,m)*f[n-m]%MOD);
	}
    return 0;
}
