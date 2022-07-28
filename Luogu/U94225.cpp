#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
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

const int N=1e6+5,INF=1e9+5;
int one[N],idx=1;
int ver[N],Next[N],edge[N],w[N];
void AddEdge(int a,int b,int c,int d)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	edge[idx]=c;
	w[idx]=d;
}

int S,T,n,m;

int ans;
queue<int> q;
int dis[N],cur[N];
bool vis[N];

bool spfa()
{
    memset(dis,0,sizeof dis);
    memset(vis,0,sizeof vis);
    memcpy(cur,one,sizeof cur);
    
    while(q.size()) q.pop();
    int i,x,y;
    q.push(S),dis[S]=0,vis[S]=true;
    while(q.size()) {
        x=q.front(); q.pop();
        vis[x]=false;
        for(i=one[x];i>0;i=Next[i]) {
            y=ver[i]; 
            if(edge[i] && dis[y]<dis[x]+w[i]) {
                dis[y]=dis[x]+w[i];
                if(!vis[y]) 
                    vis[y]=true,q.push(y);
            }
        }
    }
    return (dis[T]>0);
}

int dinic(int x,int limit)
{
	if(x==T) return limit;
	vis[x]=true;
	int i,y,k,flow=0;
	for(i=cur[x];i&&flow<limit;i=Next[i]) {
		cur[x]=i;
		y=ver[i];
		if(edge[i]&&!vis[y]&&dis[y]==dis[x]+w[i]) {
			k=dinic(y,min(edge[i],limit-flow));
			edge[i]-=k,edge[i^1]+=k;
			flow+=k,ans+=k*w[i];
		}
	}
	vis[x]=false;
	return flow;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z;
	
	scanf("%d%d",&n,&m);
	S=m+n+1,T=m+n+2;
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(S,i,1,z),AddEdge(i,S,0,-z);
		AddEdge(i,x+m,1,0),AddEdge(x+m,i,0,0);
		AddEdge(i,y+m,1,0),AddEdge(y+m,i,0,0);
	}
	for(i=n;i>=1;i--)
		AddEdge(i+m,T,1,0),AddEdge(T,i+m,0,0);
	
	int flow=0;
	while(spfa()) 
		while((x=dinic(S,INF)))
			flow+=x; 	
	printf("%d\n",ans);
	return 0;
}

