#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
const int dx[]={0,-1,0,1, 0};
const int dy[]={0, 0,1,0,-1};
const int N=256;
int n,m;
int a[N][N];
int dis[N][N];
bool vis[N][N];
int b[N][N];
queue< pair<int,int> > q;
void spfa(int xx,int yy)
{
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	while(q.size()) q.pop();
	int i,j;
	int x,y,z;
	int u,v;
	bool sign;
	dis[xx][yy]=0;
	vis[xx][yy]=true;
	q.push(pair<int,int>(xx,yy));
	while(q.size()) {
		x=q.front().first; y=q.front().second;
		if(a[x][y]) z=a[x][y];
		else z=b[x][y],b[x][y]=0;
		q.pop();
		vis[x][y]=false;
		for(i=1;i<=4;i++) {
			sign=false;
			u=x+dx[i]; v=y+dy[i];
			if(u<1||u>m||v<1||v>m) continue;
			if(a[u][v]==z) {
				if(dis[u][v]>dis[x][y]) 
					dis[u][v]=dis[x][y],sign=true;
			}
			else if(a[u][v]!=0) {
				if(dis[u][v]>dis[x][y]+1)
					dis[u][v]=dis[x][y]+1,sign=true;
			}
			else if(a[x][y]!=0){
				if(dis[u][v]>dis[x][y]+2)
					dis[u][v]=dis[x][y]+2,sign=true,b[u][v]=z;
			}
			if(sign&&(!vis[u][v])) {
				q.push(pair<int,int>(u,v)); 
				vis[u][v]=true;
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
	scanf("%d%d",&m,&n);
	for(i=1;i<=n;i++) {
		scanf("%d%d%d",&x,&y,&z);
		a[x][y]=++z;
	}
	spfa(1,1);
	if(dis[m][m]==dis[0][0]) {
		dis[m][m]=min(dis[m][m-1],dis[m-1][m])+2;
		if(dis[m][m]>dis[0][0])
			printf("-1\n");
		else printf("%d\n",dis[m][m]);
	}
	else printf("%d\n",dis[m][m]);
	return 0;
}

