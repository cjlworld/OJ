#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
const int N=2e5+5;
const int MOD=10007;
int one[N];
int ver[2*N],Next[2*N];
int tot=0;
inline void AddEdge(int a,int b)
{
	tot++;
	Next[tot]=one[a];
	one[a]=tot;
	ver[tot]=b;
	return;
}
int n;
LL a[N];
LL f[N],sum[N];
LL Max=-1,ans=0;
void Dp(int u,int fa)
{
	int i,j,k,v;
	for(i=one[u];i>0;i=Next[i]) 
		if(ver[i]!=fa) 
			Dp(ver[i],u);
	for(i=one[u];i>0;i=Next[i]) {
		v=ver[i];
		if(v==fa) continue;
		Max=max(Max,f[u]*a[v]);
		Max=max(Max,a[u]*f[v]);
		f[u]=max(f[u],a[v]);
		ans=(ans+sum[u]*a[v]%MOD+a[u]*sum[v]%MOD)%MOD;
		sum[u]+=a[v];
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d",&n);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(x,y);
		AddEdge(y,x);
	}
	for(i=1;i<=n;i++) 
		scanf("%lld",&a[i]);
	Dp(1,0);
	ans=ans*2%MOD;
	cout<<Max<<" "<<ans<<endl;
	return 0;
}

