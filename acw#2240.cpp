#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
/*
 S ---> F ---> COW1 ---> COW2 ---> D ---> T
 Fi = i;
 COWi1 = F+i;
 COWi2 = F+n+i;
 Di = F+n+n+i;
 S = F+n+n+D+1;
 T = F+n+n+D+2;
*/
using namespace std;
const int N=1e3+5,M=1e5+5,INF=1e9+5;
int one[N],idx=1;
int ver[M],Next[M],edge[M];
inline void AddEdge(int a,int b,int c)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	edge[idx]=c;
	return;	
} 
//===========================================
int n,F,D,S,T;
queue<int> q;
int d[N],cur[N];
bool bfs()
{
	memset(d,-1,sizeof d);
	while(q.size()) q.pop();
	int i,x,y;
	q.push(S); d[S]=1,cur[S]=one[S];
	while(q.size()) {
		x=q.front(); q.pop();
		for(i=one[x];i>0;i=Next[i]) {
			y=ver[i];
			if(edge[i]>0&&d[y]==-1) {
				d[y]=d[x]+1;
				cur[y]=one[y];
				if(y==T) return true;
				q.push(y);
			}
		}
	}
	return false;
}
int dinic(int x,int limit)
{
	if(x==T) return limit;
	int i,y,flow=0,k;
	for(i=cur[x];i>0&&flow<limit;i=Next[i]) {
		cur[x]=i;
		y=ver[i];
		if(edge[i]>0&&d[y]==d[x]+1) {
			k=dinic(y,min(edge[i],limit-flow));
			if(k==0) d[y]=-1;
			edge[i]-=k;
			edge[i^1]+=k;
			flow+=k;
		}
	}
	return flow;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d%d%d",&n,&F,&D);
	S=F+n+n+D+1; T=F+n+n+D+2;
	for(i=1;i<=n;i++) {
		scanf("%d%d",&x,&y);
		for(j=1;j<=x;j++) {
			scanf("%d",&z);
			AddEdge(z,F+i,1);
			AddEdge(F+i,z,0);
		}
		for(j=1;j<=y;j++) {
			scanf("%d",&z);
			AddEdge(F+n+i,F+n+n+z,1);
			AddEdge(F+n+n+z,F+n+i,0);
		}
	}
	for(i=1;i<=n;i++) 
		AddEdge(F+i,F+n+i,1),AddEdge(F+n+i,F+i,0);
	for(i=1;i<=F;i++) 
		AddEdge(S,i,1),AddEdge(i,S,0);
	for(i=F+n+n+1;i<=F+n+n+D;i++) 
		AddEdge(i,T,1),AddEdge(T,i,0);
	int maxflow=0;
	while(bfs()) 
		while((x=dinic(S,INF)))
			maxflow+=x;
	cout<<maxflow;
	return 0;
}

