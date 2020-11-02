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
int ex,ey,sx,sy,tx,ty; //��ʾÿ����Ϸ�հ׸��ӵ�λ�ã�ָ�����ӵĳ�ʼλ�ú�Ŀ��λ�á�

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
	
	if(sx==tx&&sy==ty) return 0;// ���� 
		
	int i;
	Node u(0,0,0,0),v(0,0,0,0);
	q.push(Node(ex,ey,sx,sy));
	
	dis[ex][ey][sx][sy]=0;
	vis[ex][ey][sx][sy]=true;
	
	while(q.size()) {
		u=q.front(); q.pop();
		for(i=1;i<=4;i++) {
			v.kx=u.kx+dx[i]; 
			v.ky=u.ky+dy[i]; //�ƶ��հ׸���
			
			if(a[v.kx][v.ky]==0) continue; // 0 ��ʾ�ø����ϵ������ǹ̶��� 
			if(v.kx==u.zx&&v.ky==u.zy)  v.zx=u.kx,v.zy=u.ky;// �ƶ��հ׸��Ӳ��պ���֮���� 
			else v.zx=u.zx,v.zy=u.zy; // û�н��� ��ԭ��
				
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

 
