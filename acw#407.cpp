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

const int N=2000,M=5e4+5,INF=1e9+5;

int one[N],idx=1;
int ver[M],Next[M],edge[M];
inline void AddEdge(int a,int b,int c)
{
	Next[++idx]=one[a],one[a]=idx,ver[idx]=b,edge[idx]=c;
	Next[++idx]=one[b],one[b]=idx,ver[idx]=a,edge[idx]=0;
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
	q.push(S),d[S]=1;
	while(q.size()) {
		x=q.front(); q.pop();
		for(i=one[x];i;i=Next[i]) {
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
	int i,k,y,flow=0;
	for(i=cur[x];i && flow<limit;i=Next[i]) {
		cur[x]=i;
		y=ver[i];
		if(edge[i] && d[y]==d[x]+1) {
			k=dinic(y,min(edge[i],limit-flow));
			if(!k) d[y]=-1;
			edge[i]-=k,edge[i^1]+=k;
			flow+=k;
		}
	}
	return flow;
}

int b[N][22],a[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,len,l,r;
	int x;
	
	scanf("%d%d",&n,&m);
	S=n+m+1,T=n+m+2;
	for(i=1;i<=n;i++) 
		for(j=1;j<=m;j++) 
			scanf("%d",&b[i][j]);
	
	for(i=1;i<=m;i++) 
		scanf("%d",&a[i]);
	
	for(len=1;len<=m;len++) {
		for(l=1;l+len-1<=m;l++) {
			r=l+len-1;
			
			memset(one,0,sizeof one);
			idx=1;
			
			for(i=1;i<=n;i++) AddEdge(S,i,1);
			for(i=1;i<=n;i++) 
				for(j=l;j<=r;j++)
					AddEdge(i,n+b[i][j],1);
			for(j=1;j<=m;j++)
				AddEdge(n+j,T,a[j]);

			int maxflow=0;
			while(bfs()) 
				while((x=dinic(S,INF)))
					maxflow+=x;
			if(maxflow==n) {
				printf("%d\n",len);
				return 0;
			}
			
	//		cerr<<l<<" "<<r<<endl;
		}
	}
	return 0;
}

