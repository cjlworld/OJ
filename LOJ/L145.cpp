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
template<class T>
struct Bit
{
	T c[N];
	inline int lowbit(int x)
	{
		return x&(-x);
	}
	inline void update(int x,const T &y)
	{
		for(;x<=n;x+=lowbit(x))
			c[x]+=y;
		return;
	}
	inline T sum(int x)
	{
		T res=0;
		for(;x>=1;x-=lowbit(x)) 
			res+=c[x];
		return res;
	}
};
Bit<LL> C1,C2; 
//c1:: (i-1)*c[i]
//c2:: c[i]
inline void modify(int x,int y,const LL &z)
{
	C1.update(x,z*(x-1));
	C1.update(y+1,-z*y);
	C2.update(x,z);
	C2.update(y+1,-z);
	return;
}
inline LL prefix(LL x)
{
	return x*C2.sum(x)-C1.sum(x);
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
		modify(dfn_in[i],dfn_in[i],a[i]);
	while(m--) {
		scanf("%d%d",&opt,&x);
		if(opt==1) {
			scanf("%lld",&z);
			modify(dfn_in[x],dfn_out[x],z);
		}
		else 
			printf("%lld\n",prefix((LL)dfn_out[x])-prefix((LL)dfn_in[x]-1));
	}
	return 0;
}
