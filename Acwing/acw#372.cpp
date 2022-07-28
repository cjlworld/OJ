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

const int N=20000+7,M=1e5+5,INF=1e9+5;
const int dx[]={0,0,0,1,-1},dy[]={0,1,-1,0,0};

int one[N],idx=1;
int Next[M],ver[M],edge[M];
inline void AddEdge(int a,int b,int c)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	edge[idx]=c;
	
//	printf("%d ---> %d  : %d\n",a,b,c);
}

int n,m,S,T;
bool ban[100+5][100+5];

int get(int x,int y)
{
	return (x-1)*n+y;
}

int cur[N],d[N];
queue<int> q;

bool bfs() 
{
	memset(d,-1,sizeof d);
	memcpy(cur,one,sizeof cur);
	while(q.size()) q.pop();
	int i,x,y;
	q.push(S),d[S]=1;
	while(q.size()) {
		x=q.front(); q.pop();
		for(i=one[x];i>0;i=Next[i]) {
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
	int flow=0,k,y,i;
	for(i=cur[x];i>0 && flow<limit;i=Next[i]) {
		cur[x]=i;
		y=ver[i];
		if(edge[i] && d[y]==d[x]+1) {
			k=dinic(y,min(limit-flow,edge[i]));
			if(k==0) d[y]=-1;
			edge[i]-=k, edge[i^1]+=k;
			flow+=k;
		}
	}
	return flow;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	int x,y;
	
	cin>>n>>m;
	for(i=1;i<=m;i++) {
		cin>>x>>y;
		ban[x][y]=true;
	}
	
	S=get(n+1,1),T=get(n+1,2);
//	cout<<S<<" "<<T<<endl;
	
	for(i=1;i<=n;i++) {
		for(j=1;j<=n;j++) {
			if(ban[i][j]) continue;
			if((i+j)%2==0) 
				AddEdge(S,get(i,j),1), AddEdge(get(i,j),S,0);		
			else AddEdge(get(i,j),T,1), AddEdge(T,get(i,j),0);
			
			for(k=1;k<=4;k++) {
				x=i+dx[k], y=j+dy[k];
				if(x>=1&&x<=n&&y>=1&&y<=n&&!ban[x][y]&&(i+j)%2==0) 
					AddEdge(get(i,j),get(x,y),1),AddEdge(get(x,y),get(i,j),0);
			}
		}
	}
	
	int maxflow=0;
	while(bfs())
		while((x=dinic(S,INF))) 
			maxflow+=x;
			
	cout<<maxflow;
	
	return 0;
}

