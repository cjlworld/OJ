#include<bits/stdc++.h>
using namespace std;
const int N=1e3+5;
int a[N],f[N];
int n;
int main()
{
    int i,j;
    cin>>n;
    for(i=1;i<=n;i++) 
        scanf("%d",&a[i]);
    a[0]=-(1e9+5);
    for(i=1;i<=n;i++) 
        for(j=0;j<i;j++) 
            if(a[j]<a[i]) 
                f[i]=max(f[i],f[j]+1);
    int ans=0;
    for(i=1;i<=n;i++) 
        ans=max(ans,f[i]);
    cout<<ans;
    return 0;
}
