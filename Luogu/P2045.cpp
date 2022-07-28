#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=20000,M=1e5+5,INF=1e9+5;
int one[N],idx=1;
int ver[M],Next[M],edge[M],w[M];
inline void AddEdge(int a,int b,int c,int d)
{
	Next[++idx]=one[a]; one[a]=idx; ver[idx]=b; edge[idx]=c; w[idx]=d;
	Next[++idx]=one[b]; one[b]=idx; ver[idx]=a; edge[idx]=0; w[idx]=-d;
	return;
}
//==========================================
int a[56][56];
int n,k,S,T;
int get(int x,int y,int times)
{
	return x*n+y+(times-1)*n*n;
}
int incf[N],dis[N],pre[N];
bool vis[N];
queue<int> q;
bool spfa()
{
	memset(incf,0,sizeof incf);
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	memset(pre,0,sizeof pre);
	while(q.size()) q.pop();
	int i,x,y;
	q.push(S); dis[S]=0,vis[S]=true,incf[S]=INF;
	while(q.size()) {
		x=q.front(); q.pop();
		vis[x]=false;
		for(i=one[x];i>0;i=Next[i]) {
			y=ver[i];
			if(edge[i] && dis[y]>dis[x]+w[i]) {
				dis[y]=dis[x]+w[i];
				incf[y]=min(incf[x],edge[i]);
				pre[y]=i;
				if(!vis[y]) {
					vis[y]=true;
					q.push(y);
				}
			}
		}
	}
	return incf[T]>0;
}
void EK(int &maxflow,int &mincost)
{
	maxflow=mincost=0;
	int i,x;
	while(spfa()) {
		x=incf[T];
		maxflow+=x; mincost+=dis[T]*x;
		for(i=T;i!=S;i=ver[pre[i]^1]) {
			edge[pre[i]]-=x;
			edge[pre[i]^1]+=x;
		}
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	scanf("%d%d",&n,&k);
	for(i=1;i<=n;i++)	
		for(j=1;j<=n;j++) 
			scanf("%d",&a[i][j]);
	for(i=1;i<=n;i++) {
		for(j=1;j<=n;j++) {
			AddEdge(get(i,j,1),get(i,j,2),1,-a[i][j]);
			AddEdge(get(i,j,3),get(i,j,4),INF,0);
			AddEdge(get(i,j,5),get(i,j,1),INF,0);
			AddEdge(get(i,j,5),get(i,j,3),INF,0);
			AddEdge(get(i,j,2),get(i,j,6),INF,0);
			AddEdge(get(i,j,4),get(i,j,6),INF,0);
			
			if(i+1<=n) AddEdge(get(i,j,6),get(i+1,j,5),INF,0);
			if(j+1<=n) AddEdge(get(i,j,6),get(i,j+1,5),INF,0);	
		}
	}
	S=7*n*n+1; T=7*n*n+2;
	AddEdge(S,get(1,1,5),k,0);
	AddEdge(get(n,n,6),T,k,0);
	int flow,cost;
	EK(flow,cost);
	cout<<-cost;
	return 0;
}
