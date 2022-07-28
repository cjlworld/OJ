#include<cstdio>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;

const LL MOD=1e9+7;

LL quickpow(LL x,LL k,LL MOD)
{
    LL res=1; x%=MOD;
    while(k) {
        if(k&1) res=res*x%MOD;
        x=x*x%MOD; k>>=1;
    }
    return res%MOD;
}

LL C(int n,int m)
{
    LL res=1;
    for(LL i=1,j=n;i<=m;i++,j--) 
        res=res*quickpow(i,MOD-2,MOD)%MOD*j%MOD;
    return res;
}

int main()
{
    int n;
    cin>>n;
    cout<< (C(2*n,n) - C(2*n,n-1)+MOD)%MOD;
}

//Catalan Êý
// h(n) = C(2n,n) - C(2n,n-1)
