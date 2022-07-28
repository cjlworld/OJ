#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
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

const int N=1e5+5,M=2e6+5;
int one[N],hs[N],idx;
int ver[M],Next[M];
void AddEdge(int h[],int a,int b)
{
	Next[++idx]=h[a];
	h[a]=idx;
	ver[idx]=b;
}

// 强联通分量的判断条件 low[x]==dfn[x],注意横向边。
int dfn[N],low[N],times;
int id[N],all;
stack<int> S;

void tarjan(int x)
{
	dfn[x]=low[x]=++times;
	S.push(x);
	int i,y;
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(!dfn[y]) {
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(!id[y]) 
			low[x]=min(low[x],dfn[y]);
	}
	
	if(low[x]==dfn[x]) {
		all++;
		while(S.top()!=x) 
			id[S.top()]=all,S.pop();
		id[x]=all,S.pop();
	}
}

int n,m;
LL MOD;

int sum[N],f[N]; 
// f[x] 表示 从入度为0的节点走到 x，所产生的半联通子图中节点的数量最多是多少。 
LL g[N];
// g[x] 表示取到 f[x] 的方案数。
set<ULL> Mem;

int main()
{
//	freopen("1.in","r",stdin);
	int i,x,y;
	
	scanf("%d%d%lld",&n,&m,&MOD);
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(one,x,y);
	}
	
	for(i=1;i<=n;i++) 
		if(!dfn[i]) tarjan(i);
	
	for(x=1;x<=n;x++) {
		sum[id[x]]++;
		for(i=one[x];i;i=Next[i]) {
			y=ver[i];
			if(id[x]!=id[y]&&!Mem.count(id[x]*1ull*N+id[y])) {
				AddEdge(hs,id[x],id[y]);
//				printf("%d %d\n",id[x],id[y]);
				Mem.insert(id[x]*1ull*N+id[y]);
			}
				
		}
	}
//	for(i=1;i<=all;i++) 
//		printf("%d : %d\n",i,sum[i]);
	
	int ans=0;
	LL cnt=0;
	
	for(x=all;x>=1;x--) {
		if(!f[x]) f[x]=sum[x];
		for(i=hs[x];i;i=Next[i]) {
			y=ver[i];
			f[y]=max(f[y],f[x]+sum[y]);
		}
	}
	
	for(x=all;x>=1;x--) {
		if(!g[x]) g[x]=1;
		for(i=hs[x];i;i=Next[i]) {
			y=ver[i];
			if(f[y]==f[x]+sum[y]) 
				g[y]=(g[y]+g[x])%MOD;
		}
	}
	
	for(i=1;i<=all;i++) ans=max(ans,f[i]);
	for(i=1;i<=all;i++) 
		if(f[i]==ans) 
			cnt=(cnt+g[i])%MOD;
//	for(i=1;i<=all;i++) 
//		printf("f[%d] = %d , g[%d] = %lld\n",i,f[i],i,g[i]);
	printf("%d\n%lld\n",ans,cnt);
	return 0;
}

