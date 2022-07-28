#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<bitset>
#include<vector>
#include<cstdio>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=4e4+5,M=5e5+5,INF=0x3f3f3f3f;

int one[N],idx;
int ver[M],Next[M],edge[M];
inline void AddEdge(int a,int b,int c)
{
	Next[idx]=one[a]; ver[idx]=b; edge[idx]=c; one[a]=idx++;
	Next[idx]=one[b]; ver[idx]=a; edge[idx]=0; one[b]=idx++;
}

int nL,nH,m,S,T;

int d[N],cur[N];
queue<int> q;

bool bfs()
{
	memset(d,-1,sizeof d);
	memcpy(cur,one,sizeof cur);
	while(q.size()) q.pop();
	
	int i,x,y;
	q.push(S); d[S]=1;
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
			edge[i]-=k; edge[i^1]+=k;
			flow+=k;
		}
	}
	return flow;
}

int dfn[N],low[N],times;
int col[N],all;

void tarjan(int x)
{
	static stack<int> S;
	dfn[x]=low[x]=++times;
	S.push(x);
	
	for(int i=one[x],y;~i;i=Next[i]) {
		if(!edge[i]) continue; // 是在残量网络上寻找，并非原图。 
		y=ver[i];
		if(!dfn[y]) {
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(!col[y]) low[x]=min(low[x],dfn[y]);
	}
	if(low[x]==dfn[x]) {
		all++;
		while(S.size() && S.top()!=x) {
			col[S.top()]=all;
			S.pop();
		}
		col[x]=all; S.pop();
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y;
	
	scanf("%d%d%d",&nL,&nH,&m);
	
	S=nL+nH+1,T=S+1;
	memset(one,-1,sizeof one);
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(x,nL+y,1);
	}
	for(i=1;i<=nL;i++) AddEdge(S,i,1);
	for(i=1;i<=nH;i++) AddEdge(nL+i,T,1);
	
	while(bfs()) 
		while(dinic(S,INF));
	
	for(i=1;i<=T;i++) 
		if(!dfn[i]) tarjan(i);
	
	vector<int> ans;
	for(i=0;i<idx;i+=2) {
		x=ver[i^1]; y=ver[i]; // 原网络上是 x->y 
		if(x==S || y==T) continue; // 并非原图上的，是构造出的网络上的。 
		if(!edge[i] || col[x]==col[y]) // 则 (x,y) 为可行边。
			continue;
		else ans.push_back((i>>1)+1);
	}
	printf("%llu\n",ans.size());
	for(i=0;i<(int)ans.size();i++) 
		printf("%d ",ans[i]);
	puts("");
	return 0;
}

