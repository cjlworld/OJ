#include<stack>
#include<cstdio>
#include<iostream>
using namespace std;
typedef long long LL;
const int N=5e5+5,M=2*N;
int one[N],idx;
int Next[M],ver[M];
inline void AddEdge(int a,int b)
{
    Next[++idx]=one[a];
    one[a]=idx;
    ver[idx]=b;
}
//=========================================
int n;
int fa[N];
int p[N],top=0;
char S[N],a[N];
LL f[N],ans;
void Dp(int x,int fat)
{
    int k=-1;
    if(a[x]=='(') {
        f[x]=0;
        S[++top]='('; p[top]=x;
    }
    else {
        if(top==0||S[top]==')') {
            f[x]=0;
            S[++top]=')'; p[top]=x;
        }
        else {
            k=p[top];
            f[x]=f[fa[k]]+1;
            top--;
        }
    }
    for(int i=one[x];i>0;i=Next[i]) 
        if(ver[i]!=fat) 
            Dp(ver[i],x);
    if(k==-1) top--;
    else S[++top]=a[k],p[top]=k;
    return;
}
void dfs_sum(int x,int fat)
{
    f[x]+=f[fat];
    for(int i=one[x];i>0;i=Next[i]) {
        if(ver[i]!=fat) 
            dfs_sum(ver[i],x);
    }
    return;
}
int main()
{
    LL i;
    scanf("%d",&n);
    scanf("%s",a+1);
    for(i=2;i<=n;i++) {
        scanf("%d",&fa[i]);
        AddEdge(i,fa[i]);
        AddEdge(fa[i],i);
    }
    Dp(1,0);
    dfs_sum(1,0);
    for(i=1;i<=n;i++)	
    	ans^=i*f[i];
    cout<<ans<<endl;
    return 0;
}

