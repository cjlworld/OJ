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

const int N=3e6+5;
int one[N],hs[N],idx;
int Next[N],ver[N],edge[N];
void AddEdge(int h[],int a,int b,int c)
{
	Next[++idx]=h[a];
	h[a]=idx;
	ver[idx]=b;
	edge[idx]=c;
}

int dfn[N],low[N],times;
int id[N],all;
stack<int> S;

void tarjan(int x)
{
	dfn[x]=low[x]=++times;
	S.push(x);
	int i,y;
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(!dfn[y]) {
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(!id[y]) low[x]=min(low[x],dfn[y]);
	}
	if(low[x]==dfn[x]) {
		all++;
		while(S.top()!=x)
			id[S.top()]=all,S.pop();
		id[x]=all,S.pop();
	}
}

int n,m;
int dis[N];
bool vis[N];
void Dijstra(int x)
{
	priority_queue<PII,vector<PII>,greater<PII> > q;
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	
	int i,y,z;
	q.push(PII(0,x)),dis[x]=0;
	while(q.size()) {
		x=q.top().second; q.pop();
		if(vis[x]) continue;
		vis[x]=true;
		for(i=hs[x];i;i=Next[i]) {
			y=ver[i],z=edge[i];
			if(dis[y]>dis[x]+z) {
				dis[y]=dis[x]+z;
				q.push(PII(dis[y],y));
			}
		}
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(one,x,y,z);
	}
	for(i=1;i<=n;i++) 
		if(!dfn[i]) tarjan(i);
	
	for(x=1;x<=n;x++)
		for(i=one[x];i;i=Next[i]) {
			y=ver[i],z=edge[i];
			if(id[x]!=id[y]) 
				AddEdge(hs,id[x],id[y],z);
		}
	Dijstra(id[1]);
	printf("%d\n",dis[id[n]]);
	return 0;
}

