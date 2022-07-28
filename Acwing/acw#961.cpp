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
const int N=500,M=1e5+5,INF=1e9+5;
int one[N],idx=1;
int ver[M],Next[M],edge[M];
inline void AddEdge(int a,int b,int c)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	edge[idx]=c;
	return;
}
//==================================================
int n,m,S,T;
int a[N],b[N];
int d[N],cur[N];
queue<int> q;
bool bfs()
{
	memset(d,-1,sizeof d);
	while(q.size()) q.pop();
	int i,x,y;
	q.push(S); d[S]=1,cur[S]=one[S];
	while(q.size()) {
		x=q.front(); q.pop();
		for(i=one[x];i>0;i=Next[i]) {
			y=ver[i];
			if(edge[i] && d[y]==-1) {
				d[y]=d[x]+1;
				cur[y]=one[y];
				if(y==T) return true;
				q.push(y);
			}
		}
	}
	return false;
}
int dinic(int x,int limit)
{
	if(x==T) return limit;
	int i,y,k,flow=0;
	for(i=cur[x];i>0&&flow<limit;i=Next[i]) {
		cur[x]=i;
		y=ver[i];
		if(edge[i] && d[y]==d[x]+1) {
			k=dinic(y,min(edge[i],limit-flow));
			if(k==0) d[y]=-1;
			edge[i]-=k;
			edge[i^1]+=k;
			flow+=k;
		}
	}
	return flow;
}
bool st[N];
void dfs(int x)
{
	st[x]=true;
	for(int i=one[x];i>0;i=Next[i]) {
		if(edge[i]>0&& !st[ver[i]]) 
			dfs(ver[i]);
	}
	return;
}
vector<int> ans1,ans2;
int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	int i,x,y;
	scanf("%d%d",&n,&m);
	S=n+n+1,T=n+n+2;
	for(i=1;i<=n;i++) scanf("%d",&a[i]);
	for(i=1;i<=n;i++) scanf("%d",&b[i]);
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(x,y+n,INF);
		AddEdge(y+n,x,0);
	}
	for(i=1;i<=n;i++) {
		AddEdge(S,i,b[i]);
		AddEdge(i,S,0);
		AddEdge(i+n,T,a[i]);
		AddEdge(T,i+n,0);
	}
	int maxflow=0;
	while(bfs()) 
		while((x=dinic(S,INF))) 
			maxflow+=x;
	cout<<maxflow<<endl;
	dfs(S);
	for(i=2;i<=idx;i+=2) {
		if(st[ver[i^1]]&&(!st[ver[i]])) {
			if(ver[i]==T) 
				ans1.push_back(ver[i^1]);
			else ans2.push_back(ver[i]); 
		}
	}
	cout<<ans1.size()+ans2.size()<<endl;
//	for(i=2;i<=idx;i++) 
//		if(edge[i]!=0) 
//			printf("%d %d\n",ver[i^1],ver[i]);
//		printf("%d ---> %d : %d\n",ver[i^1],ver[i],edge[i]);
	for(i=0;i<(int)ans1.size();i++) 
		printf("%d +\n",ans1[i]-n);
	for(i=0;i<(int)ans2.size();i++) 
		printf("%d -\n",ans2[i]);
	return 0;
}

