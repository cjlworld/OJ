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
const int N=1000,M=1e5+5,INF=1e9+5;
int one[N],idx=1;
int ver[M],Next[M],edge[M],w[M];
inline void AddEdge(int a,int b,int c,int d)
{
	Next[++idx]=one[a]; one[a]=idx; ver[idx]=b; edge[idx]=c; w[idx]=d;
	Next[++idx]=one[b]; one[b]=idx; ver[idx]=a; edge[idx]=0; w[idx]=-d;
	return;
}
//========================================
int n,m,A,B,S,T;
int get(int x,int y)
{
	return x*(m+1)+y;
}
int incf[N],pre[N],dis[N];
bool vis[N];
queue<int> q;
bool spfa()
{
	memset(incf,0,sizeof incf);
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
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
				if(!vis[y]) 
					vis[y]=true,q.push(y);
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
	int x,y,z;
	scanf("%d%d",&A,&B);
	scanf("%d%d",&n,&m);
	S=(n+1)*(m+1)+1,T=S+1;
	for(i=0;i<=n;i++) 
		for(j=0;j<=m-1;j++) {
			scanf("%d",&x);
			AddEdge(get(i,j),get(i,j+1),1,-x);
			AddEdge(get(i,j),get(i,j+1),INF,0);
		}
	for(i=0;i<=m;i++)
		for(j=0;j<=n-1;j++) {
			scanf("%d",&x);
			AddEdge(get(j,i),get(j+1,i),1,-x);
			AddEdge(get(j,i),get(j+1,i),INF,0);
		}
	for(i=1;i<=A;i++) {
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(S,get(y,z),x,0);
	}
	for(i=1;i<=B;i++) {
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(get(y,z),T,x,0);
	}
	int flow,cost;
	EK(flow,cost);
	cout<<-cost;
	return 0;
}

