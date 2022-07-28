#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
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

const int N=200+5,M=4e5+5,INF=0x3f3f3f3f;

int one[N],idx=1;
int ver[M],Next[M],edge[M];
inline void AddEdge(int a,int b,int c)
{
	Next[++idx]=one[a],one[a]=idx,ver[idx]=b,edge[idx]=c;	
	Next[++idx]=one[b],one[b]=idx,ver[idx]=a,edge[idx]=0;
}

int n,m,S,T;

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
		for(i=one[x];i;i=Next[i]) {
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
	int y,i,k,flow=0;
	for(i=cur[x];i && flow<limit;i=Next[i]) {
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
 
int a[N]; // a[i] 表示节点i多流出去的量。 
int low[M],up[M];
int sum=0;

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y;
	
	scanf("%d%d",&n,&m);
	
	for(i=1;i<=m;i++) {
		scanf("%d%d%d%d",&x,&y,&low[i],&up[i]);
		a[y]+=low[i];
		a[x]-=low[i];
		AddEdge(x,y,up[i]-low[i]); // 在附加图上最多流这么多。 
	}
	
	S=n+1,T=n+2;
	for(i=1;i<=n;i++) {
		if(a[i]>0)  // 多流出去了,要补回来。 
			AddEdge(S,i,a[i]),sum+=a[i];
		else if(a[i]<0) AddEdge(i,T,-a[i]);
	}
	
	int maxflow=0;
	while(bfs()) 
		while((x=dinic(S,INF))) 
			maxflow+=x;
	
	if(maxflow<sum) printf("NO\n");
	else {
		printf("YES\n");
		for(i=1;i<=m;i++) 
			printf("%d\n",low[i]+edge[i*2^1]);
	}
	return 0;
}

