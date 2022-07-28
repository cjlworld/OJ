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
typedef pair<int,int> PII;

const int N=1e5+5;
const LL INF=1e16;

int one[N],idx;
int ver[N],Next[N];
LL edge[N];
inline void AddEdge(int a,int b,LL c)
{
	Next[idx]=one[a],ver[idx]=b,edge[idx]=c,one[a]=idx++;
	Next[idx]=one[b],ver[idx]=a,edge[idx]=0,one[b]=idx++;
}

int n,m,tot,S,T;
LL maxk;

LL a[N];
PII edges[N];

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

int dinic(int x,LL limit)
{
	if(x==T) return limit;
	int i,k,y;
	LL flow=0;
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
	int i,j;
	LL x;
	
	scanf("%d%d",&n,&m);

	for(i=1;i<=m;i++) 
		scanf("%d%d",&edges[i].first,&edges[i].second);
	
	memset(a,-1,sizeof a);
	scanf("%d",&tot);
	for(i=1;i<=tot;i++) {
		scanf("%lld",&x);
		scanf("%lld",&a[x]);
		while((1ll<<maxk)<a[x]) maxk++;
	}
	
	LL ans=0;
	for(i=maxk;i>=0;i--) {
		memset(one,-1,sizeof one),idx=0;
		for(j=1;j<=m;j++) {
			AddEdge(edges[j].first,edges[j].second,1);
			AddEdge(edges[j].second,edges[j].first,1);
		}
			
		
		S=n+1,T=n+2;
		
		for(j=1;j<=n;j++)
			if(~a[j]) {
				if((a[j]>>i)&1) AddEdge(j,T,INF); // 已经确定了，不可能被割掉。 
				else AddEdge(S,j,INF);
			}
			
		while(bfs()) 
			while((x=dinic(S,INF)))
				ans+=(1ll<<i)*x;
	}
	
	printf("%lld\n",ans);
	return 0;
}

