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

const int N=1e5+5,INF=0x3f3f3f3f;
const int dx[]={0,0,1,-1},dy[]={1,-1,0,0};

int one[N],idx=1;
int ver[N],Next[N],edge[N];
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
    int i,y,k,flow=0;
    for(i=cur[x];i && flow<limit;i=Next[i]) {
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

int a[256][256],sum;

int get(int x,int y) { return (x-1)*m+y-1; }

int main()
{
	int i,j;
	int x,y;
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) {
		for(j=1;j<=m;j++) 
			scanf("%d",&a[i][j]),sum+=a[i][j];
	}
	
	S=n*m+3,T=n*m+4;
	
	for(i=1;i<=n;i++) {
	    for(j=1;j<=m;j++) {
	        if((i+j)%2==0) AddEdge(S,get(i,j),a[i][j]);
	        else {
	            AddEdge(get(i,j),T,a[i][j]);
	            continue;
	        }
	        
	        for(int k=0;k<4;k++) {
	            x=i+dx[k],y=j+dy[k];
	            if(x>=1&&x<=n&&y>=1&&y<=m) 
	                AddEdge(get(i,j),get(x,y),INF);
	        }
	    }
	}
	
	int ans=0;
	while(bfs())
	    while((x=dinic(S,INF)))
	        ans+=x;
	  
	cout<<sum-ans<<endl;
	
	return 0;
}

