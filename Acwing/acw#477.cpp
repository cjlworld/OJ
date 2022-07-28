#include<queue>
#include<cstdio>
#include<iostream>

using namespace std;

const int N=10000+5;
int one[N],idx=1;
int ver[N],Next[N],edge[N];
inline void AddEdge(int a,int b,int c)
{
    Next[++idx]=one[a];
    one[a]=idx;
    ver[idx]=b;
    edge[idx]=c;
    return;
}

int n,m;
int c[N],u[N];
int dep[N];
int f[N];
queue<int> q;
void topsort()
{
    int i,x,y;
    for(i=1;i<=n;i++) 
        if(dep[i]==0) 
            q.push(i),f[i]=c[i];
    while(q.size()) {
        x=q.front(); q.pop();
        for(i=one[x];i>0;i=Next[i]) {
            y=ver[i];
            f[y]+=edge[i]*f[x];
            dep[y]--;
            if(dep[y]==0) {
                f[y]-=u[y];
                if(f[y]>0) q.push(y);
            }
        }
    }
    return;
}

int main()
{
//	freopen("1.in","r",stdin);
    int i;
    int x,y,z;
    scanf("%d%d",&n,&m);
    for(i=1;i<=n;i++) 
        scanf("%d%d",&c[i],&u[i]);
    for(i=1;i<=m;i++) {
        scanf("%d%d%d",&x,&y,&z);
        AddEdge(x,y,z);
        dep[y]++;
    }
    topsort();
    bool flag=false;
    for(i=1;i<=n;i++) {
        if(one[i]==0) {
            if(f[i]>0) printf("%d %d\n",i,f[i]),flag=true;
        }
  //      printf("%d\n",f[i]);
    }
    if(!flag) printf("NULL");
    return 0;
}
