#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
typedef long long LL;
using namespace std;
const int N=10010,M=2e5+5,INF=0x3f3f3f;
int one[N],ver[M],Next[M],edge[M],idx=1;
inline void AddEdge(const int &a,const int &b,const int &c)
{
    Next[++idx]=one[a];
    one[a]=idx;
    ver[idx]=b;
    edge[idx]=c;
    return;
}
//=========================================
int n,m,S,T;
int d[N],cur[N];
queue<int> q;
bool bfs()
{
    memset(d,-1,sizeof d);
    while(q.size()) q.pop();
    q.push(S); d[S]=1,cur[S]=one[S];
    register int i,x,y;
    while(q.size()>0) {
        x=q.front(); q.pop();
        for(i=one[x];i>0;i=Next[i]) {
            y=ver[i];
            if(edge[i]>0&&d[y]==-1) {
                d[y]=d[x]+1;
                cur[y]=one[y];
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
    int flow=0,y,k;
    for(int i=cur[x];i>0&&flow<limit;i=Next[i]) { // 注意不要用引用，用引用会慢很多。 
        cur[x]=i;
        y=ver[i];
        if(d[y]==d[x]+1&&edge[i]>0) {
            k=dinic(y,min(edge[i],limit-flow));
            if(k==0) d[y]=-1;
            edge[i]-=k;
            edge[i^1]+=k;
            flow+=k;
        }
    }
    return flow;
}
LL maxflow=0;
int main()
{
//  freopen("1.in","r",stdin);
    int i;
    int x,y,z;
    scanf("%d%d%d%d",&n,&m,&S,&T);
    for(i=1;i<=m;i++) {
        scanf("%d%d%d",&x,&y,&z);
        AddEdge(x,y,z);
        AddEdge(y,x,0);
    }
    while(bfs()) 
        while((x=dinic(S,INF))) 
            maxflow+=x;
    cout<<maxflow;
    return 0;
}
