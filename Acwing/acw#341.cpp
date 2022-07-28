#include<set>
#include<stack>
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
#define rint register int
using namespace std;
const int N=1e5+5;
const int M=1e6+5;
struct Graph
{
    int one[N];
    int ver[M],Next[M];
    int tot;
    inline void AddEdge(const int &a,const int &b)
    {
        tot++;
        Next[tot]=one[a];
        one[a]=tot;
        ver[tot]=b;
        return;
    }
}GA,GB;
//===============================================
int a[N];
int n,m;
int dfn[N],low[N],times=0;
int col[N],all=0;
stack<int> S;
void tarjian(int now)
{
    dfn[now]=low[now]=++times;
    S.push(now);
    rint i,j,v;
    for(i=GA.one[now];i>0;i=GA.Next[i]) {
        v=GA.ver[i];
        if(!dfn[v]) {
            tarjian(v);
            low[now]=min(low[now],low[v]);
        }
        else if(col[v]==0) 
            low[now]=min(low[now],dfn[v]);
    }
    if(dfn[now]==low[now]) {
        all++;
        v=0;
        while(now!=v&&S.size()) {
            v=S.top(); S.pop();
            col[v]=all;
        }
    }
    return;
}
//=============================================
int b[N],c[N];
int f[N];
set<int> Se[N];
queue<int> q;
bool vis[N];
int dis[N];
#define fmin c
void BFS(int st)
{
    memset(vis,0,sizeof vis);
    while(q.size()) q.pop();
    rint i,j;
    rint x,y,z;
    q.push(st);
    fmin[st]=c[st];
    dis[st]=0;
    vis[st]=true;
    while(q.size()) {
        x=q.front(); q.pop();
        for(i=GB.one[x];i>0;i=GB.Next[i]) {
            y=GB.ver[i];
            fmin[y]=min(fmin[y],fmin[x]);
            dis[y]=max(dis[y],max(dis[x],b[y]-fmin[y]));
            if(vis[y]==false) {
                q.push(y); 
                vis[y]=true;
            }
        }
    }
    return;
}
#undef fmin
int main()
{
//  freopen("1.in","r",stdin);
    rint i,j;
    int x,y,z;
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++) 
        scanf("%d",&a[i]);
    for(i=1;i<=m;i++) {
        scanf("%d%d%d",&x,&y,&z);
        GA.AddEdge(x,y);
        if(z==2) GA.AddEdge(y,x);
    }
    for(i=1;i<=n;i++) 
        if(dfn[i]==0) 
            tarjian(i);
    memset(b,0,sizeof b);
    memset(c,0x3f,sizeof c);
    for(i=1;i<=n;i++) {
        for(j=GA.one[i];j>0;j=GA.Next[j]) 
            if(col[i]!=col[GA.ver[j]]) 
                Se[col[i]].insert(col[GA.ver[j]]);
        b[col[i]]=max(b[col[i]],a[i]);
        c[col[i]]=min(c[col[i]],a[i]);
    }
    for(i=1;i<=all;i++) {
        for(set<int>::iterator it=Se[i].begin();it!=Se[i].end();it++) {
            GB.AddEdge(i,*it);
        }
    }   
    BFS(col[1]);
    printf("%d\n",dis[col[n]]);
    return 0;
}
