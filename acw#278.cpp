#include<bits/stdc++.h>
using namespace std;
const int N=10000+5;
long long f[N];
int n,m;
int a[N];
int main()
{
    int i,j;
    cin>>n>>m;
    for(i=1;i<=n;i++) 
        cin>>a[i];
    f[0]=1;
    for(i=1;i<=n;i++) 
        for(j=m;j>=a[i];j--) 
            f[j]+=f[j-a[i]];
    cout<<f[m];
    return 0;
}
