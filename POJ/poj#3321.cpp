#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
const int N=1e5+5;
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
int c[N];
inline int lowbit(int x)
{
	return x&(-x);
}
inline void update(int x,int y)
{
	for(;x<=n;x+=lowbit(x))
		c[x]+=y;
	return;
}
inline int sum(int x)
{
	int res=0;
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
int a[N];
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	char opt;
	int x,y,z;
	scanf("%d",&n);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(x,y);
		AddEdge(y,x);
	}
	dfs(1,0);
	for(i=1;i<=n;i++) {
		update(dfn_in[i],1);
		a[i]=1;
	}
	scanf("%d",&m);
	while(m--) {
		scanf(" %c%d",&opt,&x);
		if(opt=='C') {
			if(a[x]) update(dfn_in[x],-1),a[x]=0;
			else update(dfn_in[x],1),a[x]=1;
		}
		else if(opt=='Q') {
			printf("%d\n",sum(dfn_out[x])-sum(dfn_in[x]-1));
		}
		else {
			m++;
			continue;
		}
	}
	return 0;
}

