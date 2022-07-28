#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;

const int N=10000+5,M=1000+5,INF=1e9+5;
int n,m,k;
int dis[N][M];
int a[N],b[N],g[N];
bool lim[N][M],vis[N][M];
int ach;

struct Node
{
	int x,y;
	int cost;
	Node(int x,int y,int cost) : x(x),y(y),cost(cost) {}
	inline bool operator<(const Node &t) const 
	{
		return cost>t.cost;
	}
};

priority_queue<Node> q;
void BFS()
{
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	int i,j;
	int x,y;
	for(i=m;i>=1;i--) 
		q.push(Node(0,i,0)),dis[0][i]=0;
	while(q.size()) {
		x=q.top().x,y=q.top().y;
		q.pop();
//		if(x>ach) printf("%d %d\n",x,y);
		ach=max(ach,x);
		if(vis[x][y]) continue;
		if(x==n) return;
		vis[x][y]=true;
		for(i=y+a[x],j=1;i<m;i+=a[x],j++) {
			if(!lim[x+1][i]) continue;
			if(dis[x+1][i]>dis[x][y]+j) {
				dis[x+1][i]=dis[x][y]+j;
				q.push(Node(x+1,i,dis[x+1][i]));
			}
			else break;
		}
		
		if(i>=m&&lim[x+1][m]&&dis[x+1][m]>dis[x][y]+j) {
			dis[x+1][m]=dis[x][y]+j;
			q.push(Node(x+1,m,dis[x+1][m]));
		}
		
		if(y-b[x]>0&&lim[x+1][y-b[x]]&&dis[x+1][y-b[x]]>dis[x][y]) {
			dis[x+1][y-b[x]]=dis[x][y];
			q.push(Node(x+1,y-b[x],dis[x+1][y-b[x]]));
		}
	}
	return;
}
int main()
{
// 	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d%d%d",&n,&m,&k);
	for(i=0;i<=n-1;i++)
		scanf("%d%d",&a[i],&b[i]);
	memset(lim,true,sizeof lim);
	for(i=1;i<=k;i++) {
		scanf("%d%d%d",&x,&y,&z);
		for(j=1;j<=y;j++) lim[x][j]=false;
		for(j=z;j<=m;j++) lim[x][j]=false;
		g[++g[0]]=x;
	}
	sort(g+1,g+g[0]+1);
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
