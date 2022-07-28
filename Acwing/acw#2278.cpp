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

const int N=3e4+5,INF=0x3f3f3f3f;

int one[N],idx=1;
int ver[N],Next[N],e[N],edge[N];
inline void AddEdge(int a,int b,int c)
{
	Next[++idx]=one[a],one[a]=idx,ver[idx]=b,e[idx]=c;
	Next[++idx]=one[b],one[b]=idx,ver[idx]=a,e[idx]=0;
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
    for(i=cur[x];i && flow<limit;i=Next[i]) { // 注意不要用引用，用引用会慢很多。 
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

int testcase;
double dist;

struct Ice
{
	int x,y,n,m;
}a[N];

int main()
{
//	freopen("1.in","r",stdin);
	
	int i,j;
	int x;
	
	scanf("%d",&testcase);
	
	while(testcase--) {
		memset(one,0,sizeof one);
		idx=1;
		scanf("%d%lf",&n,&dist);
		m=0;
		
		S=2*n+5;
		
		for(i=0;i<n;i++) 
			scanf("%d%d%d%d",&a[i].x,&a[i].y,&a[i].n,&a[i].m);
		for(i=0;i<n;i++) {
			if(a[i].n) AddEdge(S,i,a[i].n);
			if(a[i].m) AddEdge(i,i+n,a[i].m);
			
			m+=a[i].n;
			
			for(j=0;j<n;j++) 
				if(sqrt((a[i].x-a[j].x)*(a[i].x-a[j].x)+
					(a[i].y-a[j].y)*(a[i].y-a[j].y))<=dist && i!=j)
					AddEdge(i+n,j,INF);
		}
		
		int cnt=0;
		
		for(T=0;T<n;T++) {
			
			for(i=0;i<=idx;i++) edge[i]=e[i];
			int maxflow=0;
			while(bfs()) 
				while((x=dinic(S,INF)))
					maxflow+=x;
			
			if(maxflow==m) printf("%d ",T),cnt++;
		}
		if(cnt==0) printf("-1\n");
		else printf("\n");
	}
	return 0;
}

