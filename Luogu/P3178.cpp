#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
template<class T>
inline void read(T &x)
{
	x=0;
	bool sign=false;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar()) 
		sign=(c=='-') ? true : sign;
	for(;c>='0'&&c<='9';c=getchar())
		x=(x<<1)+(x<<3)+(c-'0');
	x=(sign) ? ~x+1 : x;
	return;
}
template<class T>
inline void Swap(T &x,T &y)
{
	x^=y^=x^=y;
	return;
}
template<class T>
void print(T x)
{
	if(x<0) putchar('-'),x=~x+1;
	if(x>=10) print(x/10);
	putchar(48+x%10);
	return;
}
//===========================================
const int N=1e5+5;
const int INF=(-1u)>>1;
int n,m;
struct Bits
{
	LL c[N];
	LL res;
	inline int lowbit(const int &x)
	{
		return (x&(-x));
	}
	inline void update(int x,LL y)
	{
		for(;x<=n;x+=lowbit(x)) 
			c[x]+=y;
		return;
	}
	inline LL sum(int x)
	{
		res=0ll;
		for(;x>=1;x-=lowbit(x)) 
			res+=c[x];
		return res;
	}
};
Bits C1,C2;
// C1 : (i-1)*c[i]
// C2 : c[i]
inline void modify(int x,int y,const LL &key)
{
	C1.update(x,((LL)(x-1))*key);
	C1.update(y+1,-((LL)(y))*key);
	C2.update(x,key);
	C2.update(y+1,-key);
	return;
}
inline LL prefix(int x)
{
	return (LL)((LL)x)*C2.sum(x)-C1.sum(x);
}
//=============================================
int one[N];
int Next[2*N],ver[2*N];
int tot=0;
inline void AddEdge(int a,int b)
{
	tot++;
	Next[tot]=one[a];
	one[a]=tot;
	ver[tot]=b;
	return;
}
//=============================================
int son[N]; //weightest son of roots
int fa[N]; //father of roots
int dep[N]; //dep of roots
int sum[N]; //size of roots

int dfn[N],dfnt[N],times=0; 
int org[N];
int top[N]; 
void dfs1(int u,const int &father)
{
	int i,j,v;
	dep[u]=dep[father]+1;
	fa[u]=father;
	sum[u]=1;
	int tmp=-INF;
	for(i=one[u];i>0;i=Next[i]) {
		v=ver[i];
		if(v==father) continue;
		dfs1(v,u);
		sum[u]+=sum[v];
		if(sum[v]>tmp) {
			tmp=sum[v];
			son[u]=v;
		}
	}
	return;
}
void dfs2(int u)
{
	int i,j,v;
	dfn[u]=++times;
	org[times]=u;
	if(u==son[fa[u]]) 
		top[u]=top[fa[u]];
	else top[u]=u;
	if(son[u]==0) {
		dfnt[u]=times;
		return;
	}
	dfs2(son[u]);
	for(i=one[u];i>0;i=Next[i]) {
		v=ver[i];
		if(v==son[u]||v==fa[u]) 
			continue;
		dfs2(v);
	}
	dfnt[u]=times;
	return;
}
inline void range(int x,int y,const LL &key)
{
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]]) 
			Swap(x,y);
		modify(dfn[top[x]],dfn[x],key);
		x=top[x]; x=fa[x];
	}
	if(dep[x]<dep[y]) 
		Swap(x,y);
	modify(dfn[y],dfn[x],key);
	return;
}
inline LL query(int x)
{
	LL res=0ll;
	for(;top[x]>1;x=top[x],x=fa[x]) 
		res+=prefix(dfn[x])-prefix(dfn[top[x]]-1);
	res+=prefix(dfn[x])-prefix(0);
	return res;
}
LL a[N];
int main()
{
//	freopen("1.in","r",stdin);
	register int i,j;
	int x,y;
	LL z;
	int opt;
	read(n); read(m);
	for(i=1;i<=n;i++) 
		read(a[i]);
	for(i=1;i<=n-1;i++) {
		read(x); read(y);
		AddEdge(x,y);
		AddEdge(y,x);
	}
	dfs1(1,0);
	dfs2(1);
	for(i=1;i<=n;i++) 
		modify(dfn[i],dfn[i],a[i]);
	for(i=1;i<=m;i++) {
		read(opt); read(x);
		if(opt==1) {
			read(z);
			modify(dfn[x],dfn[x],z);
		}
		else if(opt==2) {
			read(z);
			modify(dfn[x],dfnt[x],z);
		}
		else print(query(x)),putchar('\n');
	}
	return 0;
}

