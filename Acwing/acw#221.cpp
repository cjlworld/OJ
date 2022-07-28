#include<cstdio>
#include<iostream>
#define rint register int
typedef long long LL;
using namespace std;
LL n;
LL varphi(LL x)
{
    LL i;
    LL res=x;
    for(i=2;i*i<=x;i++) {
        if(x%i==0) {
            while(x%i==0) x/=i;
            res=res/i*(i-1);
        }
    }
    if(x>1) res=res/x*(x-1);
    return res;
}

int main()
{
//	freopen("1.in","r",stdin);
    cin>>n;
    LL ans=0;
    for(LL i=1;i*i<=n;i++) {
        if(n%i==0) {
            ans+=i*varphi(n/i);
            if(i*i!=n)
                ans+=(n/i)*varphi(i);
    //        cout<<i<<endl;
        }
    }
    cout<<ans<<endl;
    return 0;
}
