#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int f[N][2][2],a[N];
int n;
int main()
{
//	freopen("1.in","r",stdin);
    int i;
    scanf("%d",&n);
    f[0][1][1]=f[0][1][0]=f[0][0][1]=-1e9;
    for(i=1;i<=n;i++) 
        scanf("%d",&a[i]);
    for(i=1;i<=n;i++) {
        f[i][1][1]=f[i-1][0][0]-a[i];
        f[i][0][1]=max(f[i-1][1][1],f[i-1][1][0])+a[i];
        f[i][0][0]=max(f[i-1][0][0],f[i-1][0][1]);
        f[i][1][0]=max(f[i-1][1][0],f[i-1][1][1]);
    }
    cout<<max(max(f[n][1][1],f[n][0][0]),max(f[n][1][0],f[n][0][1]));
    return 0;
}
