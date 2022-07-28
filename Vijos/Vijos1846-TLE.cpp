#include<cmath>
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;

const int N=30+2,INF=2147483646;
const int dx[]={0,1,-1,0,0},dy[]={0,0,0,1,-1};

int n,m,Q;
int a[N][N];
bool vis[N][N][N][N];
int dis[N][N][N][N];
int ex,ey,sx,sy,tx,ty; //表示每次游戏空白格子的位置，指定棋子的初始位置和目标位置。

struct Node
{
	int kx,ky; // empty 
	int zx,zy; // now
	Node(int kx,int ky,int zx,int zy) : kx(kx),ky(ky),zx(zx),zy(zy) {}
};
queue<Node> q;

int BFS()
{
	memset(vis,0,sizeof vis);
	memset(dis,0x3f,sizeof dis);
	while(q.size()) q.pop();
	
	if(sx==tx&&sy==ty) return 0;// 特判 
		
	int i;
	Node u(0,0,0,0),v(0,0,0,0);
	q.push(Node(ex,ey,sx,sy));
	
	dis[ex][ey][sx][sy]=0;
	vis[ex][ey][sx][sy]=true;
	
	while(q.size()) {
		u=q.front(); q.pop();
		for(i=1;i<=4;i++) {
			v.kx=u.kx+dx[i]; 
			v.ky=u.ky+dy[i]; //移动空白格子
			
			if(a[v.kx][v.ky]==0) continue; // 0 表示该格子上的棋子是固定的 
			if(v.kx==u.zx&&v.ky==u.zy)  v.zx=u.kx,v.zy=u.ky;// 移动空白格子并刚好与之交换 
			else v.zx=u.zx,v.zy=u.zy; // 没有交换 在原地
				
			if(vis[v.kx][v.ky][v.zx][v.zy]) continue;
			vis[v.kx][v.ky][v.zx][v.zy]=true;
			dis[v.kx][v.ky][v.zx][v.zy]=dis[u.kx][u.ky][u.zx][u.zy]+1;
			
			q.push(v);
			if(v.zx==tx&&v.zy==ty) return dis[v.kx][v.ky][v.zx][v.zy];// arrive 
		}
	}
	return -1;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	scanf("%d%d%d",&n,&m,&Q);
	for(i=1;i<=n;i++) 
		for(j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	while(Q--) {
		scanf("%d%d%d%d%d%d",&ex,&ey,&sx,&sy,&tx,&ty);
		printf("%d\n",BFS());
	}
	return 0;
}

 
