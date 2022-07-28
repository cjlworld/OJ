#include<cstdio>
#include<iostream>
#define rint register int
typedef long long LL;
using namespace std;
const int N=256;
int f[N],g[N]; // f left --> right ; g right ---> left  最长上升子序列 
int a[N];
int n;
int main()
{
//  freopen("1.in","r",stdin);
    rint i,j;
    cin>> n;
    for(i=1;i<=n;i++) 
        cin>>a[i];
    for(i=1;i<=n;i++) {
        for(j=0;j<=i-1;j++) {
            if(a[j]<a[i]) 
                f[i]=max(f[i],f[j]+1);
        }
    }
    for(i=n;i>=1;i--) {
        for(j=n+1;j>=i+1;j--) 
            if(a[j]<a[i])
                g[i]=max(g[i],g[j]+1);
    }
    int ans=0;
    for(i=1;i<=n;i++) 
        ans=max(ans,f[i]+g[i]-1);
    cout<<n-ans;
    return 0;
}


