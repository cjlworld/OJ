#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
template<class T>
inline void read(T &x)
{
	x=0;
	register bool sign=false;
	register char c;
	for(c=getchar();c<'0'||c>'9';c=getchar()) 
		sign=(c=='-') ? true : sign;
	for(;c>='0'&&c<='9';c=getchar()) 
		x=(x<<1)+(x<<3)+(c-'0');
	x=(sign) ? ~x+1 : x;
	return;
}
template<class T>
void print(T x)
{
	if(x<0) putchar('-'),x=~x+1;
	if(x>=10) print(x/10);
	putchar('0'+x%10);
	return;
}
//=================================
const int N=2e5+5;
LL MOD;
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
//=================================
int n,m,root;
struct Bits
{
	LL c[N];
	LL res;
	inline int lowbit(const int &x) 
	{
		return (x&(-x));	
	}
	inline void update(int x,const LL &y) 
	{
		for(;x<=n;x+=lowbit(x)) 
			c[x]=(c[x]+y)%MOD;
		return;
	}
	inline LL sum(int x)
	{
		res=0ll;
		for(;x>=1;x-=lowbit(x)) 
			res=(res+c[x])%MOD;
		return res%MOD;
	}
};
Bits C1,C2;
// c1 (i-1)*c[i]
// c2 c[i]
inline void modify(const LL &x,const LL &y,const LL &key)
{
	C1.update(x,(x-1)*key);
	C1.update(y+1,-y*key);
	C2.update(x,key);
	C2.update(y+1,-key);
	return;
}
inline LL prefix(const LL &x)
{
	return (x*C2.sum(x)%MOD-C1.sum(x))%MOD;
}
//===========================================
const int INF=(-1u)>>1;
int sum[N];
int dep[N];
int fa[N];
int son[N];
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
		if(sum[v]>tmp) {
			tmp=sum[v];
			son[u]=v;
		}
		sum[u]+=sum[v];
	}
	return;
}
LL dfn[N],dfnt[N],times=0;
int org[N];
int top[N];
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
		if(v==fa[u]||v==son[u]) 
			continue;
		dfs2(v);
	}
	dfnt[u]=times;
	return;
}
//=======================================
inline void Swap(int &x,int &y)
{
	x^=y^=x^=y;
	return;
};
inline void range(int x,int y,const int &key)
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
inline LL query(int x,int y)
{
	LL res=0;
 	while(top[x]!=top[y]) {
  	    if(dep[top[x]]<dep[top[y]]) 
			Swap(x,y);
		res=(res+prefix(dfn[x])-prefix(dfn[top[x]]-1))%MOD;;
		x=top[x]; x=fa[x];	
	}
	if(dep[x]<dep[y]) 
		Swap(x,y);
	res=(res+prefix(dfn[x])-prefix(dfn[y]-1))%MOD;
	return res;         
}
//=============================================
int a[N];
int main()
{
//	freopen("1.in","r",stdin);
//	freopen(".out","w",stdout);
	register int i,j;
	int x,y,opt;                           		
	LL z;
	read(n); read(m); read(root); read(MOD);
	for(i=1;i<=n;i++) 
		read(a[i]);
	for(i=1;i<=n-1;i++) {
		read(x); read(y);
		AddEdge(x,y);
		AddEdge(y,x);
	}
	dfs1(root,0);
	dfs2(root);
	for(i=1;i<=n;i++) 
		modify(dfn[i],dfn[i],a[i]);
	for(i=1;i<=n;i++) {
		if(dfn[i]==0||dfnt[i]==0) {
			cout<<"dfn error"<<endl;
			return 0;
		}		
	}
	for(i=1;i<=m;i++) {
		read(opt); read(x);
		if(opt==1) {
			read(y); read(z);
			z=z%MOD;
			range(x,y,z);
		}
		else if(opt==2) {
			read(y);
			z=query(x,y);
			if(z<0) z+=MOD;
			printf("%lld\n",z);
		}
		else if(opt==3) {
			read(z);
			z=z%MOD;
			modify(dfn[x],dfnt[x],z);
		}
		else if(opt==4) {
			z=(prefix(dfnt[x])-prefix(dfn[x]-1))%MOD;
			if(z<0) z+=MOD;
			printf("%lld\n",z);
		}
	}
	return 0;
}

