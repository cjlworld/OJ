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
int ver[N],edge[N],Next[N];
inline void AddEdge(int a,int b,int c)
{
	if(c<0) puts("here");
	Next[idx]=one[a],ver[idx]=b,edge[idx]=c,one[a]=idx++;
	Next[idx]=one[b],ver[idx]=a,edge[idx]=0,one[b]=idx++;
}

int n,m,s,t,S,T,tot;
int up[N],low[N];
int a[N]; // a[i] 表示节点 i 多流出去的流量。 

int cur[N],d[N];
queue<int> q;

bool bfs()
{
	memset(d,-1,sizeof d);
	memcpy(cur,one,sizeof cur);
	while(q.size()) q.pop();
	
	int i,x,y;
	q.push(S),d[S]=0;
	while(q.size()) {
		x=q.front(); q.pop();
		for(i=one[x];~i;i=Next[i]) {
			y=ver[i];
			if(edge[i] && d[y]==-1) {
				d[y]=d[x]+1;
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
	int i,k,y,flow=0;
	for(i=cur[x];~i && flow<limit;i=Next[i]) {
		y=ver[cur[x]=i];
		if(edge[i] && d[y]==d[x]+1) {
			k=dinic(y,min(edge[i],limit-flow));
			if(!k) d[y]=-1;
			edge[i]-=k,edge[i^1]+=k;
			flow+=k;
		}
	}
	return flow;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y;
	
	scanf("%d%d%d%d",&n,&m,&s,&t);
	memset(one,-1,sizeof one);
	for(i=1;i<=m;i++) {
//		cin>>x>>y>>low[i]>>up[i];
		scanf("%d%d%d%d",&x,&y,&low[i],&up[i]);
//		printf("%d %d %d %d\n",x,y,low[i],up[i]);
		AddEdge(x,y,up[i]-low[i]);
		a[x]-=low[i],a[y]+=low[i];
	}
	S=n+1,T=n+2;
	for(i=1;i<=n;i++) {
		if(a[i]>0) AddEdge(S,i,a[i]),tot+=a[i];
		else if(a[i]<0) AddEdge(i,T,-a[i]);
	}
	AddEdge(t,s,INF);
	
	int maxflow=0;
	while(bfs()) 
		while((x=dinic(S,INF)))
			maxflow+=x;
	
	if(maxflow<tot) printf("No Solution\n");
	else {
		int f0=edge[idx-1];
		edge[idx-1]=edge[idx-2]=0;
		S=s,T=t;
		
		maxflow=0;
		while(bfs()) 
			while((x=dinic(S,INF)))
				maxflow+=x;
		
		printf("%d\n",f0+maxflow);
	} 
	return 0;
}

