#include<bits/stdc++.h>
using namespace std;
const int px[]={0,-2,-1,1,2,2,1,-1,-2};
const int py[]={0,1,2,2,1,-1,-2,-2,-1};
const int dx[]={0,1,0};
const int dy[]={0,0,1};
long long ans=0;
bool a[256][256];
unsigned long long f[256][256];
int n,m;//n*m
int mx,my;
inline bool ok(int x,int y)
{
	if(x>=0&&y>=0&&x<=n&&y<=m) return true;
	return false;
}
inline void Init()
{
	scanf("%d %d %d %d",&n,&m,&mx,&my);
	n++;m++;mx++;my++;
	a[mx][my]=1;
	for(int i=1;i<=8;i++) {
		if(ok(mx+px[i],my+py[i])) a[mx+px[i]][my+py[i]]=1;
	}
//	for(int i=1;i<=n;i++) {
//		for(int j=1;j<=n;j++) {
//			if(a[i][j]) cout<<"#";
//			else cout<<'O';
//			cout<<" ";
//		}
//		cout<<endl;
//	}
}
inline void dp()
{
	int i,j,t;
	f[1][0]=1;
	for(i=1;i<=n;i++) {
		for(j=1;j<=m;j++) {
			if(a[i][j]) {
				f[i][j]=0;
				continue;
			}
			f[i][j]=f[i][j-1]+f[i-1][j];
		}		
	}
}
//inline void dfs(int x,int y)
//{
//	
//	for(int i=1;i<=2;i++) {
//		int u=x+dx[i],v=y+dy[i];
//		if(u>=0&&v>=0&&u<=n&&v<=m&&a[u][v]==0) {
//			if(u==n&&v==m) ans++;
//			else dfs(x+dx[i],y+dy[i]);
//		}
//	}
//}
int main()
{
//	freopen("1.in","r",stdin);
	Init();
	
//	dfs(0,0);
//	cout<<ans<<endl;
	
	dp();
	cout<<f[n][m];
	
	return 0;
}

