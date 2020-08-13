#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int INF=(-1u)>>1;
const int N=256;
const int M=3e4+5;
int one[N];
int Next[M],ver[M],edge[M];
int tot=1;
inline void AddEdge(const int &a,const int &b,const int &c)
{
    Next[++tot]=one[a];
    one[a]=tot;
    ver[tot]=b;
    edge[tot]=c;
    return;
}
//================================================
int n,m,s,t;
bool vis[N];
int infc[N],pre[N];
queue<int> q;
int maxflow=0;
bool Ek()
{
    memset(vis,0,sizeof vis);
    memset(infc,0,sizeof infc);
    memset(pre,0,sizeof pre);
    while(q.size()) q.pop();
    int i;
    int x,y,z;
    q.push(s); vis[s]=true; infc[s]=INF;
    while(q.size()) {
        x=q.front(); q.pop();
        for(i=one[x];i>0;i=Next[i]) {
            y=ver[i]; z=edge[i];
            if(vis[y]||z<=0) continue;
            infc[y]=min(infc[x],z);
            pre[y]=i;
            vis[y]=true;
            q.push(y);
            if(y==t) return true;
        }
    }
    return false;
}
void Upflow()
{
    maxflow+=infc[t];
    for(int now=t,i;now>0;now=ver[i^1]) {
        i=pre[now];
        edge[i]-=infc[t];
        edge[i^1]+=infc[t];
    }
    return;
}
int main()
{
//  freopen("1.in","r",stdin);
    int i;
    int x,y;
    scanf("%d%d",&n,&m);
    while(scanf("%d%d",&x,&y)==2) {
        if(x==0&&y==0) 
            break;
        AddEdge(x,y+n,1);
        AddEdge(y+n,x,0);
    }
    s=n+m+1,t=n+m+2;
    for(i=1;i<=n;i++) {
        AddEdge(s,i,1);
        AddEdge(i,s,0);
    }
    for(i=n+1;i<=n+m;i++) {
        AddEdge(i,t,1);
        AddEdge(t,i,0);
    }
    while(Ek()) Upflow();
    cout<<maxflow<<endl;
    for(i=2;i<=tot;i+=2) {
        if(edge[i]==1) continue;
        if(ver[i]>n+m||ver[i^1]>n+m) 
            continue;
        x=ver[i]-n; y=ver[i^1];
        printf("%d %d\n",y,x); 
    }
    return 0;
}
