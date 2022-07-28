#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=256,M=8e4+5,INF=1e9+5;
int one[N];
int ver[M],Next[M],edge[M],w[M],idx=1;
inline void AddEdge(int a,int b,int c,int d)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	edge[idx]=c;
	w[idx]=d;
}
//==============================================
int n,m,t;
int LIT;
int d[N],cur[N];
int S,T;
queue<int> q; 
bool bfs()
{
	memset(d,-1,sizeof d);
	while(q.size()>0) q.pop();
	q.push(S); d[S]=1,cur[S]=one[S];
	int i,x,y;
	while(q.size()>0) {
		x=q.front(); q.pop();
		for(i=one[x];i>0;i=Next[i]) {
			y=ver[i];
			if(edge[i]>0&&d[y]==-1&&w[i]<=LIT) {
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
	int flow=0,y,i,k;
	for(i=cur[x];i>0&&flow<limit;i=Next[i]) {
		cur[x]=i;
		y=ver[i];
		if(edge[i]>0&&d[y]==d[x]+1&&w[i]<=LIT) {
			k=dinic(y,min(limit-flow,edge[i]));
			if(k==0) d[y]=-1;
			flow+=k;
			edge[i]-=k;
			edge[i^1]-=k;
		}
	}
	return flow;
}
bool check(int limit)
{
	LIT=limit;
	int maxflow=0,x;
	fill(edge,edge+idx+1,1);
	while(bfs()) 
		while((x=dinic(S,INF))) 
			maxflow+=x;
	return (maxflow>=t);
}
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z;
	int L=0,R=-INF,mid;
	scanf("%d%d%d",&n,&m,&t);
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(x,y,1,z);
		AddEdge(y,x,1,z);
		R=max(R,z+5);
	}
	S=1,T=n;
	while(L+1<R) {
		mid=(L+R)>>1;
		if(check(mid)) R=mid;
		else L=mid;
	}
	cout<<R;
	return 0;
}

