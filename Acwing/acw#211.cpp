#include<cstdio>
#include<iostream>

using namespace std;
typedef long long LL;

const int N=2000+5;
const LL MOD=10007;
LL c[N][N];
LL a,b,k,n,m;
void init()
{
    int i,j;
    c[0][0]=1;
    for(i=1;i<=1000+3;i++)
        for(j=0;j<=i;j++) {
            if(j>=1) c[i][j]=(c[i][j]+c[i-1][j-1])%MOD;
            c[i][j]=(c[i][j]+c[i-1][j])%MOD; 
        }
    return;
}

LL quickpow(LL x,LL k,LL MOD)
{
    LL res=1; x%=MOD;
    while(k) {
        if(k&1) res=res*x%MOD;
        x=x*x%MOD; k>>=1;
    }
    return res%MOD;
}

int main()
{
    init();
    cin>>a>>b>>k>>n>>m;
    cout<<(quickpow(a,n,MOD)*quickpow(b,m,MOD)%MOD)*c[k][n]%MOD;
    return 0;
}
