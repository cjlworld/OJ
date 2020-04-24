#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
const int N=1e5+5;
int one[N];
int ver[2*N],Next[2*N];
LL edge[2*N];
int tot=0;
inline void AddEdge(int a,int b,LL c)
{
	tot++;
	Next[tot]=one[a];
	one[a]=tot;
	ver[tot]=b;
	edge[tot]=c;
	return; 
}
int n;
LL a[N],sum[N];
LL f[N]; //f[u]=u's sons and grandsons... to u;
void Dp(int u,int fa)
{
	for(int i=one[u];i>0;i=Next[i]) 
		if(ver[i]!=fa) 
			Dp(ver[i],u);
	int v;
	sum[u]=a[u];
	for(int i=one[u];i>0;i=Next[i]) {
		if(ver[i]==fa) continue;
		v=ver[i];
		f[u]+=f[v]+sum[v]*edge[i];
		sum[u]+=sum[v];
	}
	return;
}
LL g[N]; //g[u]=the people above u to u;
// g[u]=g[fa]+(f[fa]-f[u]-sum[u]*edge(u,fa))+(sum[1]-sum[u])*edge(u,fa)
void Gp(int u,int fa,LL cost)
{
	g[u]=g[fa]+(f[fa]-f[u]-sum[u]*cost)+(sum[1]-sum[u])*cost;
	for(int i=one[u];i>0;i=Next[i]) 
		if(ver[i]!=fa)
			Gp(ver[i],u,edge[i]);
	return;
}
int main()
{
	int i,j;
	int x,y;
	LL z;
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%lld",&a[i]);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d%lld",&x,&y,&z);
		AddEdge(x,y,z);
		AddEdge(y,x,z);
	}
	Dp(1,0);
	f[0]=f[1];
	Gp(1,0,0ll);
	LL ans=100000000000000ll;
	for(i=1;i<=n;i++) 
		ans=min(ans,g[i]+f[i]);
	cout<<ans;
	return 0;
}


