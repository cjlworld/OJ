#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=256,M=1e5+5,INF=1e9+5;
int one[N],idx=1;
int e[M];
int ver[M],Next[M],edge[M],w[M];
inline void AddEdge(int a,int b,int c,int d)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	e[idx]=c;
	w[idx]=d;
	return;
}
//==================================================
int n,m,S,T;
int dis[N],incf[N],pre[N];
bool vis[N];
queue<int> q;
bool spfa()
{
	memset(dis,0x3f,sizeof dis);
	memset(incf,0,sizeof incf);
	memset(pre,0,sizeof pre);
	memset(vis,0,sizeof vis);
	while(q.size()) q.pop();
	int i,x,y;
	q.push(S); incf[S]=INF,dis[S]=0,vis[S]=true;
	while(q.size()) {
		x=q.front(); q.pop();
		vis[x]=false;
		for(i=one[x];i>0;i=Next[i]) {
			y=ver[i];
			if(edge[i]>0 && dis[y]>dis[x]+w[i]) {
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
	int i,j,x;
	scanf("%d%d",&m,&n);
	S=n+m+1,T=n+m+2;
	for(i=1;i<=m;i++) {
		scanf("%d",&x);
		AddEdge(S,i,x,0);
		AddEdge(i,S,0,0);
	}
	for(i=1;i<=n;i++) {
		scanf("%d",&x);
		AddEdge(m+i,T,x,0);
		AddEdge(T,m+i,0,0);
	}
	for(i=1;i<=m;i++) 
		for(j=m+1;j<=m+n;j++) {
			scanf("%d",&x);
			AddEdge(i,j,INF,x);
			AddEdge(j,i,0,-x);
		}
	int flow,cost;
	memcpy(edge,e,sizeof edge);
	EK(flow,cost);
	cout<<cost<<endl;
	for(i=2;i<=idx;i++) 
		w[i]=(-1)*w[i];
	memcpy(edge,e,sizeof edge);
	EK(flow,cost);
	cout<<(-cost);
//	for(i=2*n+2*m+2+1;i<=idx;i+=2)
//		cout<<edge[i]<<endl;
	return 0;
}

