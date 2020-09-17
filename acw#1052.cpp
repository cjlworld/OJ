#include<bits/stdc++.h>
using namespace std;
const int N=55,MOD=1e9+7;
char a[N];
int nxt[N];
int n,m;
void dealkmp()
{
    int i,j=0;
    for(i=2;i<=m;i++) {
        while(a[j+1]!=a[i]&&j>0) 
            j=nxt[j];
        if(a[i]==a[j+1]) j++;
        nxt[i]=j;
    }
    // printf("nxt = {0,0");
    // for(i=2;i<=m;i++) 
    //     printf(",%d",nxt[i]);
    // printf("}\n");
    return;
}
int g[N][N]; // g[j][k] = { states path | already j bits , a[j+1] ? next char(k+'A'-1) , the ways }
int f[N][N]; 
int main()
{
    int i,j,k,x;
    scanf("%d%s",&n,a+1);
    m=strlen(a+1);
    dealkmp();
    for(j=0;j<m;j++) {
        for(k=1;k<=26;k++) {
            x=j;
            while(a[x+1]!= char(k+'a'-1) && x>0) 
                x=nxt[x];
            if(a[x+1]== char(k+'a'-1)) x++;
            g[j][k]=x;
//            printf("g[][] %d %c : %d\n",j,char(k+'a'-1),g[j][k]);
        }
    }
//    printf("-------------\n");
    f[0][0]=1;
    for(i=0;i<n;i++) {
        for(j=0;j<m;j++) {
            for(k=1;k<=26;k++) {
                f[i+1][g[j][k]]=(f[i+1][g[j][k]]+f[i][j])%MOD;
            }
                
        }
    }
    // for(i=0;i<=n;i++) 
    //     for(j=0;j<m;j++)
    //         printf("f[][] %d %d : %d\n",i,j,f[i][j]);
    int ans=0;
    for(j=0;j<m;j++)
        ans=(ans+f[n][j])%MOD;
    cout<<ans;
    return 0;
}
