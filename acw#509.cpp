#include<map>
#include<cmath>
#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;
typedef pair<int,int> PII;

const int N=30+2,INF=0x3f3f3f3f;
const int dx[]={0,1,-1,0,0},dy[]={0,0,0,1,-1};

int n,m,Q;

int a[N][N];
int g[N][N][N][N]; // g[a][b][c][d] 其中(a,b)是空白格子,(c,d)是起点。 
int id;

namespace Graph
{
	const int M=429600;
	int one[M],idx;
	int ver[M],Next[M],edge[M];
	void AddEdge(int a,int b,int c)
	{
		Next[++idx]=one[a];
		one[a]=idx;
		ver[idx]=b;
		edge[idx]=c;
///		printf("%d ---> %d : %d\n",a,b,c);
	}
	
	int dis[M];
	bool vis[M];
	void Dijstra(int x)
	{
		priority_queue<PII,vector<PII>,greater<PII> > q;
		memset(dis,0x3f,sizeof dis);
		memset(vis,0,sizeof vis);
		
		int i,y,z;
		q.push(PII(0,x)),dis[x]=0;
		while(q.size()) {
			x=q.top().second; q.pop();
			if(vis[x]) continue;
			vis[x]=true;
			
			for(i=one[x];i;i=Next[i]) {
				y=ver[i],z=edge[i];
				if(dis[y]>dis[x]+z) {
					dis[y]=dis[x]+z;
					q.push(PII(dis[y],y));
				}
			}
		}
	}
}

namespace Init
{
	bool vis[N][N][N][N];
	int dis[N][N][N][N];
	struct Node
	{
		int kx,ky; // empty 
		int zx,zy; // now
		Node(int kx,int ky,int zx,int zy) : kx(kx),ky(ky),zx(zx),zy(zy) {}
	};
	
	void BFS(int ex,int ey,int sx,int sy)
	{
		queue<Node> q;
		memset(vis,0,sizeof vis);
		memset(dis,0x3f,sizeof dis);
			
		int i;
		bool flag;
		Node u(0,0,0,0),v(0,0,0,0);
		q.push(Node(ex,ey,sx,sy));
		
		int cur=g[ex][ey][sx][sy];
		dis[ex][ey][sx][sy]=0;
		vis[ex][ey][sx][sy]=true;
		
		while(q.size()) {
			u=q.front(); q.pop();
			for(i=1;i<=4;i++) {
				v.kx=u.kx+dx[i]; 
				v.ky=u.ky+dy[i]; //移动空白格子
				
				flag=false;
				if(!a[v.kx][v.ky]) continue; // 0 表示该格子上的棋子是固定的 
				if(v.kx==u.zx&&v.ky==u.zy)  v.zx=u.kx,v.zy=u.ky,flag=true;// 移动空白格子并刚好与之交换 
				else v.zx=u.zx,v.zy=u.zy; // 没有交换 在原地
					
				if(vis[v.kx][v.ky][v.zx][v.zy]) continue;
				vis[v.kx][v.ky][v.zx][v.zy]=true;
				dis[v.kx][v.ky][v.zx][v.zy]=dis[u.kx][u.ky][u.zx][u.zy]+1;
				
				if(flag) Graph::AddEdge(cur,g[v.kx][v.ky][v.zx][v.zy],dis[v.kx][v.ky][v.zx][v.zy]);
				else q.push(v);
			}
		}
	}
	int d[N][N];
	void bfs(int sx,int sy,int lx,int ly)
	{
		memset(d,0x3f,sizeof d);
		queue<PII> q;
		
		int i,x,y,vx,vy;
		q.push(PII(sx,sy)),d[sx][sy]=0;
		while(q.size()) {
			x=q.front().first,y=q.front().second;
			q.pop();
			for(i=1;i<=4;i++) {
				vx=x+dx[i],vy=y+dy[i];
				if(vx>=1&&vx<=n&&vy>=1&&vy<=m&&a[vx][vy]&&(vx!=lx||vy!=ly)&&d[vx][vy]==INF) {
					d[vx][vy]=d[x][y]+1;
					q.push(PII(vx,vy));
				}
			}
		}
	}
	
	void main()
	{
		int i,j,k,x,y;
		for(i=1;i<=n;i++) 
			for(j=1;j<=m;j++) {
				if(!a[i][j]) continue;
				for(k=1;k<=4;k++) {
					x=i+dx[k],y=j+dy[k];
					if(x>=1&&x<=n&&y>=1&&y<=m&&a[x][y]) 
						g[i][j][x][y]=++id;
						//printf("%d %d %d %d : %d\n",i,j,x,y,g[i][j][x][y]);
				}
			}
				
		for(i=1;i<=n;i++) 
			for(j=1;j<=m;j++) {
				if(!a[i][j]) continue;
				for(k=1;k<=4;k++) {
					x=i+dx[k],y=j+dy[k];
					if(g[i][j][x][y]) 
						BFS(i,j,x,y);
				}
			}
	}
}

int Query(int ex,int ey,int sx,int sy,int tx,int ty)
{
	if(sx==tx&&sy==ty) return 0;
	int res=INF;
	int i,j,x,y,u;
	vector<int> v;
	for(i=1;i<=4;i++) {
		x=tx+dx[i],y=ty+dy[i];
		if(a[x][y]) v.push_back(g[x][y][tx][ty]);
		//,printf("%d %d %d %d : %d\n",x,y,tx,ty,g[x][y][tx][ty]);
	}
	Init::bfs(ex,ey,sx,sy);
	for(i=1;i<=4;i++) {
		x=sx+dx[i],y=sy+dy[i];
		if(!a[x][y]) continue;
		u=g[x][y][sx][sy];
		Graph::Dijstra(u);
		for(j=0;j<(int)v.size();j++) {
			res=min(res,Init::d[x][y]+Graph::dis[v[j]]);
//			printf("%d\n",Init::f[ex][ey][x][y]);
		}
	}
	return res;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int ans;
	int ex,ey,sx,sy,tx,ty; //表示每次游戏空白格子的位置，指定棋子的初始位置和目标位置。
	scanf("%d%d%d",&n,&m,&Q);
	for(i=1;i<=n;i++) 
		for(j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	Init::main();
	while(Q--) {
		scanf("%d%d%d%d%d%d",&ex,&ey,&sx,&sy,&tx,&ty);
		ans=Query(ex,ey,sx,sy,tx,ty);
		if(ans>=INF) printf("-1\n");
		else printf("%d\n",ans);
	}
	return 0;
}

 
