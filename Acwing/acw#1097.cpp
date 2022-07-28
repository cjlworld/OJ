#include<bits/stdc++.h>

using namespace std;

const int N=1024;
const int dx[]={0,1,1,1,0,-1,-1,-1},dy[]={-1,-1,0,1,1,1,0,-1};

int n,m;
char a[N][N];
int ans;
bool vis[N][N];

bool dfs(int x,int y) 
{
    vis[x][y]=true; 
    for(int i=0,nx,ny;i<8;i++) {
        nx=x+dx[i]; ny=y+dy[i];
        if(nx>=1 && nx<=n && ny>=1 && ny<=m && !vis[nx][ny] && a[nx][ny]=='W') {
            dfs(nx,ny);
        } 
    }
}

int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++) 
        scanf("%s",a[i]+1);
    for(int i=1;i<=n;i++) 
        for(int j=1;j<=m;j++) {
            if(a[i][j]=='W' && !vis[i][j]) {
                ans++;
                dfs(i,j);
            } 
        }
    cout<<ans<<endl;
    return 0;
}

