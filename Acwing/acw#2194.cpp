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

const int N=1e4+5,INF=0x3f3f3f3f;

int one[N],idx=1;
int ver[N],Next[N],edge[N],w[N];
inline void AddEdge(int a,int b,int c,int d)
{
	Next[++idx]=one[a],one[a]=idx,ver[idx]=b,edge[idx]=c,w[idx]=d;
	Next[++idx]=one[b],one[b]=idx,ver[idx]=a,edge[idx]=0,w[idx]=-d;
}

int n,m,S,T;
int dis[N],cur[N];
bool vis[N];
queue<int> q;

bool spfa()
{
	memset(dis,0x3f,sizeof dis);
	memcpy(cur,one,sizeof cur);
	
	int i,x,y;
	
	q.push(S),dis[S]=0;
	while(q.size()) {
		x=q.front(); q.pop();
		vis[x]=false;
		for(i=one[x];i;i=Next[i]) {
			y=ver[i]; 
			if(edge[i] && dis[y]>dis[x]+w[i]) {
				dis[y]=dis[x]+w[i];
				if(!vis[y]) 
					q.push(y),vis[y]=true;
			}
		}
	}
	return (dis[T]<INF);
}

LL ans;

int dinic(int x,int limit)
{
	if(x==T) return limit;
	vis[x]=true;
	int i,k,flow=0,y;
	for(i=cur[x];i && flow<limit;i=Next[i]) {
		y=ver[i];
		cur[x]=i;
		
		if(edge[i] && !vis[y] && dis[y]==dis[x]+w[i]) {
			k=dinic(y,min(edge[i],limit-flow));
			if(!k) dis[y]=INF;
			edge[i]-=k,edge[i^1]+=k;
			flow+=k;
			ans+=w[i]*k;
		}
	}
	vis[x]=false;
	return flow;
}

int a[N],sum;

int main()
{
//	freopen("1.in","r",stdin);
	int i,x;
	
	scanf("%d",&n);
	for(i=1;i<=n;i++) {
		scanf("%d",&a[i]);
		sum+=a[i];
	}
	sum=sum/n;
	
	AddEdge(1,n,INF,1),AddEdge(n,1,INF,1);
	AddEdge(1,2,INF,1),AddEdge(n,n-1,INF,1);
	
	for(i=2;i<=n-1;i++) {
		AddEdge(i,i-1,INF,1);
		AddEdge(i,i+1,INF,1);
	}
	
	S=n+1,T=n+2;
	for(i=1;i<=n;i++) {
		if(a[i]>sum) AddEdge(S,i,a[i]-sum,0);
		else if(a[i]<sum) AddEdge(i,T,sum-a[i],0);
	}
	
	int maxflow=0;
	while(spfa()) 
		while((x=dinic(S,INF)))
			maxflow+=x;
	printf("%lld\n",ans);
	return 0;
}

