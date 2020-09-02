#include<bits/stdc++.h>
using namespace std;
const int N=25;
int f[N][N][N],a[N][N];
int n;
int main()
{
//	freopen("1.in","r",stdin);
    int i,j,k;
    int x,y,z;
    cin>>n;
    while(cin>>x>>y>>z) {
        if(x==0&&y==0&&z==0) 
            break;
        a[x][y]=z;
    }
    for(k=1;k<=2*n;k++) {
        for(i=1;i<=n;i++) {
        	if(!(k-i>=1&&k-i<=n)) continue;
            for(j=1;j<=n;j++) {
            	if(!(k-j>=1&&k-j<=n)) continue;
                f[k][i][j]=max(max(f[k-1][i][j],f[k-1][i-1][j]),max(f[k-1][i][j-1],f[k-1][i-1][j-1]));
                if(i==j) f[k][i][j]+=a[i][k-i];
                else f[k][i][j]+=a[i][k-i]+a[j][k-j];
            //    printf("%d %d %d %d : %d\n",i,k-i,j,k-j,f[k][i][j]);
            }
        }
    }
    cout<<f[2*n][n][n];
    return 0;
}
