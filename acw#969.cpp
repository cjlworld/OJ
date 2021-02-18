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

const int N=1e5+5,INF=0x3f3f3f3f;

int one[N],idx;
int ver[N],Next[N],edge[N],w[N];
inline void AddEdge(int a,int b,int c,int d)
{
	Next[idx]=one[a]; ver[idx]=b; edge[idx]=c; w[idx]=d; one[a]=idx++;
	Next[idx]=one[b]; ver[idx]=a; edge[idx]=0; w[idx]=-d; one[b]=idx++;
}

int n,m,S,T;
LL ans=0;

int dis[N],cur[N];
bool st[N];
queue<int> q;

bool spfa()
{
	memset(dis,0x3f,sizeof dis);
	memcpy(cur,one,sizeof cur);
	while(q.size()) q.pop();
	
	int i,x,y;
	q.push(S); dis[S]=0;
	while(q.size()) {
		x=q.front(); q.pop();
		st[x]=false;
		for(i=one[x];~i;i=Next[i]) {
			y=ver[i];
			if(edge[i] && dis[y]>dis[x]+w[i]) {
				dis[y]=dis[x]+w[i];
				if(!st[y]) {
					st[y]=true;
					q.push(y);
				}
			}
		}
	}
	return (dis[T]<INF);	
}

int mcmf(int x,int limit)
{
	if(x==T) return limit;
	st[x]=true;
	int k,flow=0;
	for(int i=cur[x],y;~i && flow<limit;i=Next[i]) {
		y=ver[cur[x]=i];
		if(edge[i] && !st[y] && dis[y]==dis[x]+w[i]) {
			k=mcmf(y,min(edge[i],limit-flow));
			if(!k) dis[y]=-INF;
			edge[i]-=k,edge[i^1]+=k;
			flow+=k,ans+=(LL)k*w[i];
		}
	}
	st[x]=false;
	return flow;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z;
	
	scanf("%d%d",&n,&m);
	memset(one,-1,sizeof one);
	S=n+2,T=n+3;
	for(i=1;i<=n;i++) {
		scanf("%d",&x);
		AddEdge(S,i,x,0); AddEdge(i+1,T,x,0);
		AddEdge(i+1,i,INF,0);
	}
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(x,y+1,INF,z);
	}
	
	while(spfa())
		while(mcmf(S,INF));
	printf("%lld\n",ans);
	
	return 0;
}

