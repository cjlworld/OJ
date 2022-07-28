#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=2e4+5,M=3e5+5,INF=0x7fffffff;
int one[N];
int Next[M],ver[M],edge[M],idx=1;
inline void AddEdge(const int &a,const int &b,const int &c)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	edge[idx]=c;
	return;
}
//==========================================
int n,m;
int sn,tn,s[N],t[N];
int S,T;
int d[N],cur[N];
queue<int> q;
bool bfs()
{
	memset(d,-1,sizeof d);
	while(q.size()) q.pop();
	int x,y,i;
	q.push(S); d[S]=1,cur[S]=one[S];
	while(q.size()>0) {
		x=q.front(); q.pop();
		for(i=one[x];i>0;i=Next[i]) {
			y=ver[i];
			if(edge[i]>0&&d[y]==-1) {
				d[y]=d[x]+1;
				cur[y]=one[y];
				q.push(y);
				if(y==T) return true;
			}
		}
	}
	return false;
}
int dinic(int x,int limit)
{
	if(x==T) return limit;
	int flow=0,k,y;
	for(int i=cur[x];i>0&&flow<limit;i=Next[i]) {
		cur[x]=i;
		y=ver[i];
		if(edge[i]>0&&d[y]==d[x]+1) {
			k=dinic(y,min(limit-flow,edge[i]));
			if(k==0) d[y]=-1;
			edge[i]-=k;
			edge[i^1]+=k;
			flow+=k;
		}
	}
	return flow;
}
int maxflow=0;
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z;
	scanf("%d%d%d%d",&n,&m,&sn,&tn);
	S=n+1,T=n+2;
	for(i=1;i<=sn;i++) scanf("%d",&s[i]),AddEdge(S,s[i],INF),AddEdge(s[i],S,0);
	for(i=1;i<=tn;i++) scanf("%d",&t[i]),AddEdge(t[i],T,INF),AddEdge(T,t[i],0);
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(x,y,z);
		AddEdge(y,x,0);
	}
	while(bfs()) 
		while((x=dinic(S,INF))) 
			maxflow+=x;
	cout<<maxflow<<endl;
	return 0;
}
