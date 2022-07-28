#include<bits/stdc++.h>
using namespace std;
const int N=1024;
int a[N],f[N];
int n;
int main()
{
    int i,j;
    cin>>n;
    for(i=1;i<=n;i++)
        cin>>a[i];
    for(i=1;i<=n;i++) 
        for(j=0;j<=i-1;j++) 
            if(a[j]<a[i]) 
                f[i]=max(f[i],f[j]+a[i]);
    int ans=0;
    for(i=1;i<=n;i++) 
        ans=max(ans,f[i]);
    cout<<ans<<endl;
    return 0;
}
