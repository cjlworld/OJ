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
#include<complex>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=10000+5,INF=0x3f3f3f3f;

int one[N],idx;
int ver[N],edge[N],Next[N];
inline void AddEdge(int a,int b,int c)
{
	Next[idx]=one[a]; ver[idx]=b; edge[idx]=c; one[a]=idx++;
	Next[idx]=one[b]; ver[idx]=a; edge[idx]=0; one[b]=idx++;
}

int n,S,T;
int d[N],cur[N];
queue<int> q;

bool bfs()
{
	memset(d,-1,sizeof d);
	memcpy(cur,one,sizeof cur);
	while(q.size()) q.pop();
	
	int i,x,y;
	q.push(S); d[S]=0;
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
	int k,flow=0;
	for(int i=cur[x],y;~i && flow<limit;i=Next[i]) {
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

int a[N],f[N];

inline int get(int x,int y) { return x*2+y; }

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x;
	
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	
	for(i=1;i<=n;i++) 
		for(j=0;j<=i-1;j++) 
			if(a[j]<=a[i]) f[i]=max(f[i],f[j]+1);
	
	int ans=0;
	for(i=1;i<=n;i++) ans=max(ans,f[i]);
	printf("%d\n",ans);
	if(ans==1) {
		printf("%d\n%d\n",n,n);
		return 0;
	}
	S=0,T=n+1;
	memset(one,-1,sizeof one); idx=0;
	for(i=1;i<=n;i++) {
		if(f[i]==1) AddEdge(S,get(i,0),1);
		if(f[i]==ans) AddEdge(get(i,1),T,1);
		AddEdge(get(i,0),get(i,1),1);
		for(j=1;j<=i-1;j++) 
			if(a[j]<=a[i] && f[j]==f[i]-1) 
				AddEdge(get(j,1),get(i,0),1);
	}
	
	int maxflow=0;
	while(bfs()) 
		while((x=dinic(S,INF))) 
			maxflow+=x;
	printf("%d\n",maxflow);
	
	S=0,T=n+1;
	memset(one,-1,sizeof one); idx=0;
	for(i=1;i<=n;i++) {
		if(f[i]==1) AddEdge(S,get(i,0),1);
		if(f[i]==ans) AddEdge(get(i,1),T,1);
		AddEdge(get(i,0),get(i,1),1);
		
		for(j=1;j<=i-1;j++) 
			if(a[j]<=a[i] && f[j]==f[i]-1) 
				AddEdge(get(j,1),get(i,0),1);
	}
	AddEdge(get(1,0),get(1,1),INF);
	AddEdge(get(n,0),get(n,1),INF);
	AddEdge(S,get(1,0),INF);
	if(f[n]==ans) AddEdge(get(n,1),T,INF);
	
	maxflow=0;
	while(bfs()) 
		while((x=dinic(S,INF))) 
			maxflow+=x;
	printf("%d\n",maxflow);
	return 0;
}

