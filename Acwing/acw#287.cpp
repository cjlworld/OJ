#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=4e5+5;
const LL INF=2e12+5;

int one[N],idx;
int ver[N],Next[N];
LL edge[N];
void AddEdge(int a,int b,LL c)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b,edge[idx]=c;
}
int deg[N];

LL f[N],t[N],g[N];
LL ans;

void Dp1(int x,int fa)
{
	int i,y,chi=0;
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		chi++;
		Dp1(y,x);
		t[y]=min(edge[i],f[y]);
		f[x]+=t[y];
	}
	if(chi==0) f[x]=INF;
//	printf("f[%d] = %lld\n",x,f[x]);
}

void Dp2(int x,int fa,LL cap)
{
	int i,y;
	
	if(fa) g[x]=min(f[fa]-t[x]+g[fa],cap);
	else if(deg[x]==1) g[x]=INF;
	
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		Dp2(y,x,edge[i]);
	}
	ans=max(ans,g[x]*(g[x]!=INF)+f[x]*(f[x]!=INF));
//	printf("g[%d] = %lld\n",x,g[x]);
}

int T,n;

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y;
	LL z;
	scanf("%d",&T);
	while(T--) {
		memset(f,0,sizeof f);
		memset(g,0,sizeof g);
		memset(t,0,sizeof t);
		memset(one,0,sizeof one);
		memset(deg,0,sizeof deg);
		ans=idx=0;
		
		scanf("%d",&n);
		for(i=1;i<=n-1;i++) {
			scanf("%d%d%lld",&x,&y,&z);
			AddEdge(x,y,z),AddEdge(y,x,z);
			deg[x]++,deg[y]++;
		}
		Dp1(1,0),Dp2(1,0,0);
		printf("%lld\n",ans);
	}
	
	return 0;
}

