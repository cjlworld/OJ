#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const LL N=1e4+5;
LL varphi(LL n)
{
    LL res=n;
    for(LL i=2;i*i<=n;i++) {
        if(n%i==0) {
            res=res/i*(i-1);
            while(n%i==0) n/=i;
        }
    }
    if(n>1) res=res/n*(n-1);
    return res;
}
LL p[N],tot=0;
void divide(LL x)
{
    tot=0;
    LL i;
    for(i=1;i*i<x;i++) 
        if(x%i==0) 
            p[++tot]=i,p[++tot]=x/i;
    if(i*i==x) p[++tot]=i;
    sort(p+1,p+tot+1);
    return;
}
LL gmul(LL x,LL k,LL mod)
{
	LL res=0;
	while(k) {
		if(k&1) res=(res+x)%mod;
		x=(x+x)%mod; k>>=1;
	}
	return res;
}
LL quickpow(LL x,LL k,LL mod)
{
    LL res=1;
    while(k) {
        if(k&1) res=gmul(res,x,mod);
        x=gmul(x,x,mod); k>>=1;
    }
    return res;
}
int main()
{
    LL i,j;
    LL x,y;
    LL n,t=0;
    while(cin>>n,n) {
        for(j=0,y=9*n;y%2==0;y/=2,j++);
        if(j>3||y%5==0) {
            printf("Case %lld: 0\n",++t);
            continue;
        }
        x=varphi(y);
        divide(x);
        for(i=1;i<=tot;i++) {
            if(quickpow(10,p[i],y)==1)
                break;
        }
        printf("Case %lld: %lld\n",++t,p[i]);
    }
    return 0;
}
