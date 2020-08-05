#include<queue>
#include<bitset>
#include<cstdio>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=105;
const int M=2e4+5;
int one[N];
int Next[M],ver[M],edge[M];
int tot=0;
inline void AddEdge(const int &a,const int &b,const int &c)
{
	Next[++tot]=one[a];
	one[a]=tot;
	ver[tot]=b;
	edge[tot]=c;
	return;
}
//==========================================
struct Node
{
	bitset<102> vis;
	int now;
	int cost;
	friend inline bool operator<(const Node &a,const Node &b)
	{
		return a.cost>b.cost;
	}
};
priority_queue<Node> q;
bitset<102> cul[N];
int a[N];
int n,k,m,s,t;
int Dijstra()
{
	Node u,v;
	int i;
	int x,y,z;
	u.vis[a[t]]=true;
	u.now=t;
	u.cost=0;
	q.push(u);
	while(q.size()>0) {
		u=q.top(); q.pop();
		x=u.now; 
		if(x==s) return u.cost;
		for(i=one[x];i>0;i=Next[i]) {
			y=ver[i]; z=edge[i];
			if((cul[a[y]]&u.vis).any()) continue; // ≈≈≥‚ 
			if(u.vis[a[y]]) continue; // —ßπ˝¡À 
			v.cost=u.cost+z;
			v.now=y;
			v.vis=u.vis;
			v.vis[a[y]]=true;
			q.push(v);
		}
	}
	return -1;
}
bool w[N][N];
int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	int x,y,z;
	scanf("%d%d%d%d%d",&n,&k,&m,&s,&t);
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	for(i=1;i<=k;i++) {
		for(j=1;j<=k;j++) {
			scanf("%d",&x);
			if(x==1) cul[i][j]=true;
			else cul[i][j]=false;
		}
	}
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(x,y,z);
		AddEdge(y,x,z);
		w[x][y]=w[y][x]=true;
	}
	for(k=1;k<=n;k++) 
		for(i=1;i<=n;i++) 
			for(j=1;j<=n;j++) 
				w[i][j]=w[i][j]|(w[i][k]&w[k][j]);
	if(w[s][t]==false||a[s]==a[t]) 
		cout<<"-1";
	else cout<<Dijstra();
	return 0;
}


