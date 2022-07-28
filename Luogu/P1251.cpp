#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#define int long long
using namespace std;
const int N=4024,M=1e5+5,INF=1e9+5;
int one[N],idx=1;
int ver[M],edge[M],Next[M],w[M];
inline void AddEdge(int a,int b,int c,int d)
{
	Next[++idx]=one[a]; one[a]=idx; ver[idx]=b; edge[idx]=c; w[idx]=d;
	Next[++idx]=one[b]; one[b]=idx; ver[idx]=a; edge[idx]=0; w[idx]=-d;
	return;
}
//=================================================
int n,p,f,s,fast,slow,S,T;
int r[N];
int dis[N],incf[N],pre[N];
bool vis[N];
queue<int> q;
bool spfa()
{
	memset(dis,0x3f,sizeof dis);
	memset(incf,0,sizeof incf);
	int i,x,y;
	q.push(S); dis[S]=0,incf[S]=INF;
	while(q.size()) {
		x=q.front(); q.pop();
		vis[x]=false;
		for(i=one[x];i>0;i=Next[i]) {
			y=ver[i];
			if(edge[i] && dis[y]>dis[x]+w[i]) {
				dis[y]=dis[x]+w[i];
				incf[y]=min(incf[x],edge[i]);
				pre[y]=i;
				if(!vis[y]) vis[y]=true,q.push(y);
			}
		}
	}
	return incf[T]>0;
}
void EK(int &maxflow,int &mincost)
{
	maxflow=mincost=0;
	int i,k;
	while(spfa()) {
		k=incf[T];
		maxflow+=k; mincost+=dis[T]*k;
		for(i=T;i!=S;i=ver[pre[i]^1]) {
			edge[pre[i]]-=k;
			edge[pre[i]^1]+=k;
		}
	}
	return;
}
signed main()
{
//	freopen("1.in","r",stdin);
	int i;
	scanf("%lld",&n);
	for(i=1;i<=n;i++) scanf("%lld",&r[i]);
	scanf("%lld%lld%lld%lld%lld",&p,&fast,&f,&slow,&s);
	S=n+n+1,T=n+n+2;
	for(i=1;i<=n;i++) {
		AddEdge(S,i+n,INF,p);
		AddEdge(S,i,r[i],0);
	    if(i+1<=n) AddEdge(i,i+1,INF,0);
		if(i+fast<=n) AddEdge(i,i+fast+n,INF,f);
		if(i+slow<=n) AddEdge(i,i+slow+n,INF,s);
		AddEdge(i+n,T,r[i],0);
	}
	int flow,cost;
	EK(flow,cost);
	cout<<cost;
	return 0;
}


