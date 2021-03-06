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

const int N=5e4+5,M=1e6+5,INF=0x3f3f3f3f;

int one[N],idx;
int ver[M],Next[M],edge[M];
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
		if(!edge[i]) continue;
		y=ver[i];
		if(!dfn[y]) {
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(!col[y]) low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x]) {
		all++;
		while(S.top()!=x) {
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
	int x,y,z;
	
	scanf("%d",&n);
	memset(one,-1,sizeof one);
	for(i=1;i<=n;i++) {
		scanf("%d",&z);
		while(z--) {
			scanf("%d",&y);
			AddEdge(i,n+y,1);
		}
	}
	S=n+n+1,T=S+1;
	for(i=1;i<=n;i++) AddEdge(S,i,1),AddEdge(i+n,T,1);
	
	while(bfs()) 
		while(dinic(S,INF));
	
	for(i=1;i<=T;i++) 
		if(!dfn[i]) tarjan(i);
	
	for(x=1;x<=n;x++) {
		vector<int> ans;
		for(i=one[x];~i;i=Next[i]) {
			y=ver[i];
			if(y==S) continue;
			if(!edge[i] || col[x]==col[y]) 
				ans.push_back(y-n);
		}
		printf("%llu ",ans.size());
		sort(ans.begin(),ans.end());
		for(i=0;i<(int)ans.size();i++) 
			printf("%d ",ans[i]);
		puts("");
	}
	return 0;
}

