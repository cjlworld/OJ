#include<bits/stdc++.h>
using namespace std;
int n,m;//n*m
int a[256][256];
int b[256][256][8];
const int dx[]={0,0,-1,0,1};
const int dy[]={0,-1,0,1,0};
int Max=0;
int sum=0,ans=0;
/*
1（西墙 west）
2（北墙 north）
4（东墙 east）
8（南墙 south）*/
void deal(int k,int x,int y)
{
	b[x][y][0]=1;
	if(k>=8) b[x][y][4]=1,k-=8;
	if(k>=4) b[x][y][3]=1,k-=4;
	if(k>=2) b[x][y][2]=1,k-=2;
	if(k>=1) b[x][y][1]=1,k-=1;
	return;
} 
void dfs(int x,int y)
{
	for(int i=1;i<=4;i++) {
		int u=x+dx[i]; int v=y+dy[i];//;
		if(b[x][y][i]==0&&b[u][v][0]==1&&u>=1&&u<=n&&v>=1&&v<=m) {
			sum++;
			b[u][v][0]=0;
			dfs(x+dx[i],y+dy[i]);
		}
	}
}
int main()
{
//	freopen("1.in","r",stdin);
	cin>>n>>m;
	int i,j;
	for(i=1;i<=n;i++) {
		for(j=1;j<=m;j++) {
			cin>>a[i][j];
			deal(a[i][j],i,j);
		}
	}
	for(i=1;i<=n;i++) {
		for(j=1;j<=m;j++) {
			if(b[i][j][0]==1) {
				ans++;
				b[i][j][0]=0; sum=1;
				dfs(i,j);
//				if(sum>Max) Max=sum;
				Max=max(Max,sum);
			}
		}
	}
	cout<<ans<<endl<<Max;
	return 0;
}

