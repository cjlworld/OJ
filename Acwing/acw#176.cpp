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

const int N=1e3+5,M=2e4+5,C=105,INF=0x3f3f3f3f;

int one[M],idx;
int Next[M],ver[M],edge[M];
inline void AddEdge(int a,int b,int c)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	edge[idx]=c;
}

struct HeapNode
{
	int city,oil,money;
	inline bool operator<(const HeapNode &t) const
	{
		return money>t.money;
	}
	inline HeapNode(int city,int oil,int money) 
		: city(city),oil(oil),money(money) {}
	HeapNode() {}
};
priority_queue<HeapNode> q;

int dis[N][C];
bool vis[N][C];
int p[N];

int n,m,Q;
int Dijstra(int x,int final,int Con)
{
	int i,y,z;
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	while(q.size()) q.pop();
	
	HeapNode u(0,0,0);
	dis[x][0]=0; q.push(HeapNode(x,0,0));
	while(q.size()) {
		u=q.top(); q.pop();
		if(vis[u.city][u.oil]) continue;
		vis[u.city][u.oil]=true;
		if(u.city==final) return u.money;
		// add oil
		if(u.oil<Con && u.money+p[u.city]<dis[u.city][u.oil+1]) {
			dis[u.city][u.oil+1]=u.money+p[u.city];
			q.push(HeapNode(u.city,u.oil+1,dis[u.city][u.oil+1]));
		}
		// Jump
		for(i=one[u.city];i;i=Next[i]) {
			y=ver[i],z=edge[i];
			if(u.oil>=z && dis[y][u.oil-z]>u.money) {
				dis[y][u.oil-z]=u.money;
				q.push(HeapNode(y,u.oil-z,dis[y][u.oil-z]));
			}
		}
	}
	return -1;
}

int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	int i;
	int x,y,z,t;
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) 
		scanf("%d",&p[i]);
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&x,&y,&z);
		x++,y++;
		AddEdge(x,y,z),AddEdge(y,x,z);
	}
	scanf("%d",&Q);
	while(Q--) {
		scanf("%d%d%d",&z,&x,&y);
		x++,y++;
		t=Dijstra(x,y,z);
		if(t==-1) printf("impossible\n");
		else printf("%d\n",t);
	}
	return 0;
}

