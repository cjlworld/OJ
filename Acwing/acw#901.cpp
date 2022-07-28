#include<bits/stdc++.h>
using namespace std;
const int dx[]={0,1,-1,0,0};
const int dy[]={0,0,0,1,-1};
const int N=300+10;
int a[N][N];
int n,m;
int f[N][N];
int Dp(int x,int y)
{
    if(x<1||x>n||y<1||y>m) 
        return 0;
    if(f[x][y]!=-1) 
        return f[x][y];
    f[x][y]=1;
    for(int i=1;i<=4;i++) 
        if(a[x+dx[i]][y+dy[i]]<a[x][y])
            f[x][y]=max(f[x][y],Dp(x+dx[i],y+dy[i])+1);
    return f[x][y];
}
int main()
{
    int i,j;
    cin>>n>>m;
    memset(a,-1,sizeof a);
    for(i=1;i<=n;i++) 
        for(j=1;j<=m;j++)
            cin>>a[i][j];
    memset(f,-1,sizeof f);
    int ans=0;
    for(i=1;i<=n;i++) 
        for(j=1;j<=m;j++) 
            ans=max(ans,Dp(i,j));
    cout<<ans<<endl;
    return 0;
}
