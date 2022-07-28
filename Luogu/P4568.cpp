#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=1e5+5,INF=0x3f3f3f3f;

int one[N],idx;
int ver[N],Next[N],edge[N];
void AddEdge(int a,int b,int c)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	edge[idx]=c;
}

int n,m,k;
int start,final;

int dis[N][11];
bool vis[N][11];

struct Node
{
	int x,y;
	int cost;
	bool operator<(const Node &t) const
	{
		return cost>t.cost;
	}
	Node(int x,int y,int z) : x(x),y(y),cost(z) {}
};

priority_queue<Node> q;

void Dijstra(int x)
{
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	while(q.size()) q.pop();
	
	int i,y,z,vx,vy;
	q.push(Node(x,0,0)),dis[x][0]=0;
	
	while(q.size()) {
		x=q.top().x,y=q.top().y;
		q.pop();
		if(vis[x][y]) continue;
		vis[x][y]=true;		
		
		for(i=one[x];i;i=Next[i]) {
			vx=ver[i],z=edge[i];
			if(dis[vx][y]>dis[x][y]+z) {
				dis[vx][y]=dis[x][y]+z;
				q.push(Node(vx,y,dis[vx][y]));
			}
			vy=y+1;
			if(vy<=k&&dis[vx][vy]>dis[x][y]) {
				dis[vx][vy]=dis[x][y];
				q.push(Node(vx,vy,dis[vx][vy]));
			} 
		}
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z;
	scanf("%d%d%d",&n,&m,&k);
	scanf("%d%d",&start,&final);
	start++,final++;
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&x,&y,&z);
		x++,y++;
		AddEdge(x,y,z),AddEdge(y,x,z);
	}
	Dijstra(start);
	int ans=INF;
	for(i=0;i<=k;i++)
		ans=min(ans,dis[final][i]);
	printf("%d\n",ans);
	return 0; 
}

