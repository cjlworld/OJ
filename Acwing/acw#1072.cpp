#include<bits/stdc++.h>

using namespace std;
const int N=1e5+5,INF=1e9+5,M=3e5+5;
int one[N],idx=1;
int ver[M],edge[M],Next[M];
inline void AddEdge(int a,int b,int c)
{
    Next[++idx]=one[a];
    one[a]=idx;
    ver[idx]=b;
    edge[idx]=c;
    return;
}
//==================================
int f[N];
int ans;
int n;
void Dp(int x,int fa)
{
    int i,y;
    int cmax=0;
    for(i=one[x];i>0;i=Next[i]) {
        y=ver[i]; 
        if(y==fa) continue;
        Dp(y,x);
        f[x]=max(f[x],f[y]+edge[i]);
        ans=max(ans,f[y]+cmax+edge[i]);
        cmax=max(cmax,f[y]+edge[i]);
    }
    return;
}
int main()
{
    int i,j;
    int x,y,z;
    cin>>n;
    for(i=1;i<=n-1;i++) {
        scanf("%d%d%d",&x,&y,&z);
        AddEdge(x,y,z);
        AddEdge(y,x,z);
    } 
    Dp(1,0);
    // for(i=1;i<=n;i++) 
    //     printf("%d ",f[i]);
    // printf("\n");
    cout<<ans<<endl;
    return 0;
}
