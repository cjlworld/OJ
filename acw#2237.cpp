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

const int N=2e5+5,M=1e6+5,INF=0x3f3f3f3f;

int one[N],idx;
int Next[M],edge[M],ver[M];
inline void AddEdge(int a,int b,int c)
{
	Next[idx]=one[a],ver[idx]=b,edge[idx]=c,one[a]=idx++;
	Next[idx]=one[b],ver[idx]=a,edge[idx]=0,one[b]=idx++;
}

int m,n,S,T; //猪舍数量以及顾客数量

int get(int x,int y) { return x+(y*m); } // 第x个猪舍，经过y次顾客。 

int cnt;

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
    int i,y,k,flow=0;
    for(i=cur[x];~i && flow<limit;i=Next[i]) { // 注意不要用引用，用引用会慢很多。 
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

int main()
{
	int i,j;
	int x,z;
	
	scanf("%d%d",&m,&n);
	S=get(m,n)+1,T=get(m,n)+2;
	
	memset(one,-1,sizeof one);
	for(i=1;i<=m;i++) {
		scanf("%d",&x);
		AddEdge(S,get(i,0),x); // 初始猪。 
	}
	
	cnt=T;
	for(i=0;i<n;i++) {
		for(j=1;j<=m && i>=1;j++) 
			AddEdge(get(j,i-1),get(j,i),INF); // 上一个猪舍。 
			
		scanf("%d",&z);
		cnt++;
		while(z--) {
			scanf("%d",&x);
			AddEdge(get(x,i),cnt,INF);
			AddEdge(cnt,get(x,i),INF);
		}
		scanf("%d",&z);
		AddEdge(cnt,T,z);
	}
	
	int maxflow=0;
	while(bfs()) 
		while((x=dinic(S,INF)))
			maxflow+=x;
	
	printf("%d\n",maxflow);
	return 0;
}

