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
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=256,M=N*N*2,INF=1e9+5;
int one[N],idx=1;
int ver[M],Next[M],edge[M],w[M],e[M];
inline void AddEdge(int a,int b,int c,int d)
{
	Next[++idx]=one[a]; one[a]=idx; ver[idx]=b; e[idx]=c; w[idx]=d;
	Next[++idx]=one[b]; one[b]=idx; ver[idx]=a; e[idx]=0; w[idx]=-d;
	return;
}
//================================================
int n,S,T;
int incf[N],dis[N],pre[N];
bool vis[N];
queue<int> q;
bool spfa()
{
	memset(incf,0,sizeof incf);
	memset(dis,0x3f,sizeof dis);
	memset(pre,0,sizeof pre);
	memset(vis,0,sizeof vis);
	while(q.size()) q.pop();
	int i,x,y;
	q.push(S); dis[S]=0,incf[S]=INF,vis[S]=true;
	while(q.size()) {
		x=q.front(); q.pop();
		vis[x]=false;
		for(i=one[x];i>0;i=Next[i]) {
			y=ver[i];
			if(edge[i] && dis[y]>dis[x]+w[i]) {
				dis[y]=dis[x]+w[i];
				pre[y]=i;
				incf[y]=min(incf[x],edge[i]);
				if(!vis[y]) {
					vis[y]=true;
					q.push(y);
				}
			}
		}
	}
	return incf[T]>0;
}
void EK(int &maxflow,int &mincost)
{
	maxflow=mincost=0;
	int i,x;
	while(spfa()) {
		x=incf[T];
		maxflow+=x; mincost+=dis[T]*x;
		for(i=T;i!=S;i=ver[pre[i]^1]) {
			edge[pre[i]]-=x;
			edge[pre[i]^1]+=x;
		}
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j,x;
	scanf("%d",&n);
	S=n+n+1,T=n+n+2;
	for(i=1;i<=n;i++) 
		for(j=1;j<=n;j++) {
			scanf("%d",&x);
			AddEdge(i,j+n,1,x);
		}
	for(i=1;i<=n;i++) 
		AddEdge(S,i,1,0),AddEdge(i+n,T,1,0);
	int flow,cost;
	memcpy(edge,e,sizeof edge);
	EK(flow,cost);
	cout<<cost<<endl;
	memcpy(edge,e,sizeof edge);
	for(i=2;i<=idx;i++) 
		w[i]=-w[i];
	EK(flow,cost);
	cout<<-cost;
	return 0;
}

