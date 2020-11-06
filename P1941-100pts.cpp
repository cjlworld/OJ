#include<queue>
#include<ctime>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;

const int N=10000+5,M=1000+5,INF=1e9+5,P=2006;
int n,m,k;
int dis[N][M];
int a[N],b[N],g[N],high[N];
bool lim[N][M],vis[N][M];
int ach;

int q[N][2]; 
void BFS()
{
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	int i,j;
	int x,y,z;
	int hh=1,tt=0;
	for(i=m;i>=1;i--) {
		dis[0][i]=0;
		vis[0][i]=true;
		tt++,q[tt%P][0]=0,q[tt%P][1]=i;
	}
		
	while(hh<=tt) {
		x=q[hh%P][0],y=q[hh%P][1],hh++;
		ach=max(ach,x);
		if(x==n) continue;
		for(i=y+a[x],j=1;i<=high[x+1];i+=a[x],j++) {
			if(!lim[x+1][i]) continue;
			if(!vis[x+1][i]) {
				vis[x+1][i]=true;
				dis[x+1][i]=dis[x][y]+j;
				tt++,q[tt%P][0]=x+1,q[tt%P][1]=i;
			}
			else if(dis[x][y]+j<dis[x+1][i]) dis[x+1][i]=dis[x][y]+j;
			else break;
		}
		
		if(i>=m&&lim[x+1][m]&&dis[x+1][m]>dis[x][y]+j) {
			dis[x+1][m]=dis[x][y]+j;
			if(!vis[x+1][m]) {
				vis[x+1][m]=true;
				tt++,q[tt%P][0]=x+1,q[tt%P][1]=m;
			}
		}
		
		z=y-b[x];
		if(z>0&&lim[x+1][z]&&dis[x+1][z]>dis[x][y]) {
			dis[x+1][z]=dis[x][y];
			if(!vis[x+1][z]) {
				vis[x+1][z]=true;
				tt++,q[tt%P][0]=x+1,q[tt%P][1]=z;
			}
		}
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d%d%d",&n,&m,&k);
	for(i=0;i<=n-1;i++)
		scanf("%d%d",&a[i],&b[i]);
	memset(lim,true,sizeof lim);
	fill(high,high+n+2,m);
	for(i=1;i<=k;i++) {
		scanf("%d%d%d",&x,&y,&z);
		for(j=1;j<=y;j++) lim[x][j]=false;
		for(j=z;j<=m;j++) lim[x][j]=false;
		high[x]=z-1;
		g[++g[0]]=x;
	}
//	cerr<<clock()<<endl;
	sort(g+1,g+g[0]+1);
//	cerr<<clock()<<endl;
	BFS();
	int ans=dis[0][0];
	for(i=1;i<=m;i++) 
		ans=min(ans,dis[n][i]);
	if(ans!=dis[0][0]) printf("1\n%d",ans);
	else {
		for(ans=0,i=1;i<=g[0];i++) 
			if(ach>=g[i]) ans=i;
		printf("0\n%d",ans);
	}
	return 0;
}
