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

const int N=5e4+5,INF=0x3f3f3f3f;

int one[N],idx;
int Next[N],ver[N],edge[N];
inline void AddEdge(int a,int b,int c)
{
	Next[idx]=one[a],ver[idx]=b,edge[idx]=c,one[a]=idx++;
	Next[idx]=one[b],ver[idx]=a,edge[idx]=0,one[b]=idx++;
}

int n,m,S,T;

int d[N],cur[N];
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
	int i,y,k,flow=0;
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

bool vs[N],vt[N];
void dfs(int x,bool vis[],int t)
{
	vis[x]=true;
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(vis[y] || !edge[i^t]) continue;	
		dfs(y,vis,t);
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z;
	
	scanf("%d%d",&n,&m);
	
	memset(one,-1,sizeof one);
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&x,&y,&z);
		x++,y++;
		AddEdge(x,y,z);
	}
	S=1,T=n;
	
	while(bfs())
		while(dinic(S,INF));
	
	dfs(S,vs,0),dfs(T,vt,1);
	
//	for(i=1;i<=n;i++)
//		if(vs[i]) printf("%d ",i);
//	printf("\n");
//	
//	for(i=1;i<=n;i++)
//		if(vt[i]) printf("%d ",i);
//	printf("\n");
	
	int ans=0;
	for(i=0;i<idx;i+=2) {
		x=ver[i^1],y=ver[i],z=edge[i];
		if(!z && vs[x] && vt[y]) 
			ans++;
	}
	
	printf("%d\n",ans);
	return 0;
}

