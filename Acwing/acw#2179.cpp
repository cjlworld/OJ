#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=1000,M=1e5+5,INF=1e9+5;
int one[N];
int ver[M],Next[M],edge[M],idx=1;
inline void AddEdge(int a,int b,int c)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	edge[idx]=c;
	return;
}
//==========================================
int m,n;
int S,T;
int maxflow=0;
queue<int> q;
int d[N],cur[N];
bool bfs()
{
	while(q.size()) q.pop();
	memset(d,-1,sizeof d);
	int i;
	int x,y;
	q.push(S); d[S]=1,cur[S]=one[S];
	while(q.size()) {
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
	int flow=0,k,i,y;
	for(i=cur[x];i>0&&flow<limit;i=Next[i]) {
		y=ver[i];
		if(edge[i]>0&&d[y]==d[x]+1) {
			k=dinic(y,min(edge[i],limit-flow));
			if(k==0) d[y]=-1;
			edge[i]-=k,edge[i^1]+=k,flow+=k;
		}
	}
	return flow;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y;
	int sum=0;
	scanf("%d%d",&m,&n);
	S=m+n+1,T=m+n+2;
	for(i=1;i<=m;i++) {
		scanf("%d",&x);
		AddEdge(S,i,x);
		AddEdge(i,S,0);
		sum+=x;
	}
	for(i=1;i<=n;i++) {
		scanf("%d",&x);
		AddEdge(i+m,T,x);
		AddEdge(T,i+m,0);
	}
	for(i=1;i<=m;i++) 
		for(j=m+1;j<=m+n;j++)
			AddEdge(i,j,1),AddEdge(j,i,0);
	while(bfs()) 
 		while((x=dinic(S,INF))) 
			maxflow+=x;
	if(maxflow!=sum) {
		cout<<"0";
		return 0;
	}
	printf("1\n");
	for(x=1;x<=m;x++) {
		for(i=one[x];i>0;i=Next[i]) {
			y=ver[i];
			if(edge[i^1]>0) {
				for(j=1;j<=edge[i^1];j++) 
					printf("%d ",y-m);
			}
		}
		printf("\n");
	}
	return 0;
}

