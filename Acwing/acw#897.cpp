#include<bits/stdc++.h>
using namespace std;
const int N=1024;
int f[N][N];
char a[N],b[N];
int n,m;
int main()
{
    int i,j;
    scanf("%d%d",&n,&m);
    scanf("%s %s",a+1,b+1);
    for(i=1;i<=n;i++) 
        for(j=1;j<=m;j++) {
            f[i][j]=max(f[i][j-1],f[i-1][j]);
            if(a[i]==b[j]) 
                f[i][j]=max(f[i][j],f[i-1][j-1]+1);//,cout<<a[i]<<" "<<b[j]<<endl;
//            cout<<i<<" "<<j<<" "<<f[i][j]<<endl;
        }
    cout<<f[n][m];
    return 0;
}
