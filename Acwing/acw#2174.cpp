#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
const int N=5000+5,M=1e5+5,INF=1e9;
int one[N],idx=1;
int ver[M],Next[M],edge[M],w[M];
inline void AddEdge(int a,int b,int c,int d)
{
    Next[++idx]=one[a];
    one[a]=idx;
    ver[idx]=b;
    edge[idx]=c;
    w[idx]=d;
    return;
}
//=====================================
int n,m,S,T;
queue<int> q;
int dis[N],incf[N],pre[N];
bool vis[N];
bool spfa()
{
    while(q.size()) q.pop();
    memset(dis,0x3f,sizeof dis);
    memset(vis,0,sizeof vis);
    memset(incf,0,sizeof incf);
    memset(pre,0,sizeof pre);
    int i;
    int x,y;
    q.push(S),dis[S]=0,vis[S]=true,incf[S]=INF;
    while(q.size()) {
        x=q.front(); q.pop();
        vis[x]=false;
        for(i=one[x];i>0;i=Next[i]) {
            y=ver[i]; 
            if(edge[i]>0 && dis[y]>dis[x]+w[i]) {
                dis[y]=dis[x]+w[i];
                pre[y]=i;
                incf[y]=min(incf[x],edge[i]);
                if(!vis[y]) {
                    vis[y]=true;
                    q.push(y);
                }
            }
        }
    }
    return incf[T]>0;
}
void EK(int &maxflow,int &mincost)
{
    int i,x;
    maxflow=mincost=0;
    while(spfa()) {
        x=incf[T];
        maxflow+=x; mincost+=x*dis[T];
        for(i=T;i!=S;i=ver[pre[i]^1]) {
            edge[pre[i]]-=x;
            edge[pre[i]^1]+=x;
        }
    }
    return;
}
int main()
{
//	freopen("1.in","r",stdin);
    int i,x,y,z,c;
    scanf("%d%d%d%d",&n,&m,&S,&T);
    for(i=1;i<=m;i++) {
        scanf("%d%d%d%d",&x,&y,&z,&c);
        AddEdge(x,y,z,c);
        AddEdge(y,x,0,-c);
    }
    int flow,cost;
    EK(flow,cost);
    cout<<flow<<" "<<cost;
    return 0;
}

