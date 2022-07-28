#include<bits/stdc++.h>
using namespace std;
const int N=124;
int a[N],f[N];
int T,n;
int calc(int n)
{
    int i,j;
    memset(f,0,sizeof f);
    a[0]=1e9;
    for(i=1;i<=n;i++) 
        for(j=0;j<i;j++) 
            if(a[j]>a[i]) 
                f[i]=max(f[i],f[j]+1);
    int res=0;
    for(i=1;i<=n;i++) 
        res=max(res,f[i]);//,cout<<f[i]<<endl;
    return res;
}
int main()
{
    int i,j;
    scanf("%d",&T);
    while(T--) {
        scanf("%d",&n);
        for(i=1;i<=n;i++) 
            scanf("%d",&a[i]);
        int ans=calc(n);
        reverse(a+1,a+n+1);
        ans=max(ans,calc(n));
        cout<<ans<<endl;
    }
    return 0;
}
