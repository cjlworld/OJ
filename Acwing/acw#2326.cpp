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

const int N=2e4+5,M=2e5+5,INF=0x3f3f3f3f;
const int dx[]={0,0,-1,1},dy[]={-1,1,0,0};

int one[N],idx;
int ver[M],Next[M],edge[M];
inline void AddEdge(int a,int b,int c)
{
	Next[idx]=one[a]; ver[idx]=b; edge[idx]=c; one[a]=idx++;
	Next[idx]=one[b]; ver[idx]=a; edge[idx]=0; one[b]=idx++;
}

int n,m,S,T;
int d[N],cur[N];
queue<int> q;

bool bfs()
{
	memset(d,-1,sizeof d);
	memcpy(cur,one,sizeof cur);
	while(q.size()) q.pop();
	
	int i,x,y;
	q.push(S); d[S]=0;
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
			edge[i]-=k,edge[i^1]+=k;
			flow+=k;
		}
	}
	return flow;
}

int get(int x,int y) { return (x-1)*m+y; }
int a[1024][1024];
int ans;

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	int x,y;
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) 
		for(j=1;j<=m;j++) 
			scanf("%d",&a[i][j]),ans+=a[i][j];
	
	S=get(n,m)+1,T=get(n,m)+2;
	memset(one,-1,sizeof one);
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++) {
			if((i+j)&1) AddEdge(S,get(i,j),a[i][j]);
			else {
				AddEdge(get(i,j),T,a[i][j]);
				continue;
			} 
			for(k=0;k<4;k++) {
				x=i+dx[k],y=j+dy[k];
				if(x<=n && x>=1 && y<=m && y>=1) 
					AddEdge(get(i,j),get(x,y),INF);
			}
		}
		
	while(bfs()) 
		while((x=dinic(S,INF))) 
			ans-=x;
	
	printf("%d\n",ans);
	return 0;
}

