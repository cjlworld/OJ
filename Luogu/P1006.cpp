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
const int N=1e5+5,M=1e5+5,INF=1e9+5;
int one[N],idx=1;
int ver[M],Next[M],edge[M],w[M];
inline void AddEdge(int a,int b,int c,int d)
{
	Next[++idx]=one[a]; one[a]=idx; ver[idx]=b; edge[idx]=c; w[idx]=d;
	Next[++idx]=one[b]; one[b]=idx; ver[idx]=a; edge[idx]=0; w[idx]=-d;
}
//========================================
int n,m,S,T;
int a[69][69];
int get(int x,int y,int times)
{
	return x*m+y+(times-1)*n*m;
}
int incf[N],pre[N],dis[N];
bool vis[N];
queue<int> q;
bool spfa()
{
	memset(incf,0,sizeof incf);
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
    memset(pre,0,sizeof pre);
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
				incf[y]=min(incf[x],edge[i]);
				pre[y]=i;
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
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) 
		for(j=1;j<=m;j++) 
			scanf("%d",&a[i][j]);
	for(i=1;i<=n;i++) {
		for(j=1;j<=m;j++) {
			AddEdge(get(i,j,1),get(i,j,2),1,-a[i][j]);
			if(i+1<=n) AddEdge(get(i,j,2),get(i+1,j,1),INF,0);
			if(j+1<=m) AddEdge(get(i,j,2),get(i,j+1,1),INF,0);
		}
	}
	edge[2]=2; edge[idx-1]=2;
	S=get(1,1,1); T=get(n,m,2);
	int flow,cost;
	EK(flow,cost);
	cout<<-cost;
	return 0;
}

