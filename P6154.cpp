#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<bitset>
#include<vector>
#include<cstdio>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=1e6+5;
const LL MOD=998244353;

LL power(LL x,LL k,LL MOD)
{
	LL res=1; x%=MOD;
	while(k) {
		if(k&1) res=res*x%MOD;
		x=x*x%MOD; k>>=1;
	}
	return res%MOD;
}
LL inv(LL x) { return power(x,MOD-2,MOD); }

int one[N],idx;
int ver[N],Next[N];
inline void AddEdge(int a,int b)
{
	Next[idx]=one[a]; ver[idx]=b; one[a]=idx++;
}

LL f[N]; // f[i] 表示从 i 出发的路径长度的期望。 
LL g[N]; // g[i] 表示从 i 出发的路径条数。 

LL dpsum(int x)
{
	if(~g[x]) return g[x];
	g[x]=1;
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		g[x]=(g[x]+dpsum(y))%MOD;
	}
	return g[x];
}

LL dp(int x)
{
	if(~f[x]) return f[x];
	f[x]=0;
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		f[x]=(f[x]+(dp(y)+1)*dpsum(y)%MOD*inv(dpsum(x))%MOD)%MOD;
	}
	return f[x];
}

int n,m;

int main()
{
//	freopen("1.in","r",stdin);
	int i,x,y;
	
	scanf("%d%d",&n,&m);
	memset(one,-1,sizeof one);
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(x,y);
	}
	memset(f,-1,sizeof f);
	memset(g,-1,sizeof g);
	
	LL ans=0,sum=0,invsum;
	for(i=1;i<=n;i++) sum=(sum+dpsum(i))%MOD;
	invsum=inv(sum);
	for(i=1;i<=n;i++) 
		ans=(ans+invsum*dpsum(i)%MOD*dp(i)%MOD)%MOD;
	cout<<ans<<endl;
	return 0;
}

