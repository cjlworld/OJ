#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
const int N=1e6+5;
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
int n,m;
LL c[N];
inline int lowbit(int x)
{
	return x&(-x);
}
inline void update(int x,LL y)
{
	for(;x<=n;x+=lowbit(x))
		c[x]+=y;
	return;
}
inline LL sum(int x)
{
	LL res=0;
	for(;x>=1;x-=lowbit(x)) 
		res+=c[x];
	return res;
}
int dfn_in[N],dfn_out[N],times=0;
void dfs(int now,const int &fa)
{
	dfn_in[now]=++times;
	for(int i=one[now];i>0;i=Next[i]) 
		if(ver[i]!=fa) 
			dfs(ver[i],now);
	dfn_out[now]=times;
	return;  
}
LL a[N];
int rt;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int opt;
	int x,y;
	LL z;
	scanf("%d%d%d",&n,&m,&rt);
	for(i=1;i<=n;i++) 
		scanf("%lld",&a[i]);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(x,y);
		AddEdge(y,x);
	}
	dfs(rt,0);
	for(i=1;i<=n;i++) 
		update(dfn_in[i],a[i]);
	while(m--) {
		scanf("%d%d",&opt,&x);
		if(opt==1) {
			scanf("%lld",&z);
			update(dfn_in[x],z);
		}
		else 
			printf("%lld\n",sum(dfn_out[x])-sum(dfn_in[x]-1));
	}
	return 0;
}

