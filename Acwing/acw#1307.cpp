#include<cstdio>
#include<iostream>

using namespace std;
const int N=1e5+5,MOD=5000011;
int f[N],s[N];
int n,k;
int main()
{
    int i,j;
    scanf("%d%d",&n,&k);
    f[0]=1; s[0]=1;
    // for(i=1;i<=n;i++) {
    //     for(j=i-k-1;j>0;j--) 
    //         f[i]=(f[i]+f[j])%MOD;
    //     f[i]+=f[0];
    // }
    for(i=1;i<=n;i++) {
        f[i]=s[max(0,i-k-1)];
        s[i]=(s[i-1]+f[i])%MOD;
    }
    // int ans=0;
    // for(i=0;i<=n;i++) 
    //     ans=(ans+f[i])%MOD;
    // cout<<ans<<endl;
    cout<<s[n]<<endl;
    return 0;
}
