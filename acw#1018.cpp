#include<bits/stdc++.h>
using namespace std;
const int N=100+5;
int f[N][N],a[N][N];
int n;
int main()
{
    int i,j;
    cin>>n;
    for(i=1;i<=n;i++) 
        for(j=1;j<=n;j++) 
            cin>>a[i][j];
    memset(f,0x3f,sizeof f);
    f[0][1]=0;
    for(i=1;i<=n;i++) 
        for(j=1;j<=n;j++) 
            f[i][j]=min(f[i][j-1],f[i-1][j])+a[i][j];
    cout<<f[n][n];
    return 0;
}
