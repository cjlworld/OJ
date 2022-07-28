#include<cstdio>
#include<iostream>
#include<algorithm>
#define LL long long
using namespace std;
char _c;
bool _sign;
template<class T>
inline void read(T &x)
{
	x=0;
	_sign=false;
	for(_c=getchar();_c<'0'||_c>'9';_c=getchar()) 
		if(_c=='-') 
			_sign=false;
	for(;_c>='0'&&_c<='9';_c=getchar()) 
		x=(x<<1)+(x<<3)+(_c&15);
	if(_sign) x=~x+1;
	return;
}
inline void Swap(int &x,int &y)
{
	x^=y^=x^=y;
	return;
}
//===============================
const int N=3e5+10;
const int INF=(-1u)>>1>>1;
int one[N];
int Next[2*N],ver[2*N];
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
//===========================
int sum[N];
int son[N];
int fa[N];
int dep[N];
LL w[N];
void dfs1(int u,const int &father)
{
	int i,v;
	dep[u]=dep[father]+1;
	fa[u]=father;
	sum[u]=1;
	int tmp=-INF;
	for(i=one[u];i>0;i=Next[i]) {
		v=ver[i];
		if(v==father) continue;
		w[v]=w[u]+edge[i];
		dfs1(v,u);		
		sum[u]+=sum[v];
		if(sum[v]>tmp) {
			tmp=sum[v];
			son[u]=v;
		} 
	}
	return;
}
int top[N];
int dfn[N],dfnt[N],times=0;
int org[N];
void dfs2(int u)
{
	int i,v;
	times++;
	dfn[u]=times;
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
inline int lca(int x,int y)
{
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]]) 
			Swap(x,y);
		x=top[x]; x=fa[x];
	}
	if(dep[x]<dep[y]) 
		return x;
	else return y;
}
//======================================
int n,m;
struct dsu
{
	int par[N];
	LL Max[N];
	int x_,y_,i;
	inline void reset(const int &ed)
	{
		for(i=0;i<=ed;i++)
			par[i]=i;
		return;
	}
	int Find(const int &x)
	{
		if(x!=par[x]) return par[x]=Find(par[x]);
		return x;
	}
	inline void range(const int &st,const int &ed,const LL &key)
	{
		if(st>ed||st>n||ed>n) return;
		y_=Find(ed+1);
		for(i=Find(st);i<=ed;i=Find(i+1)) 
			Max[i]=key,par[i]=y_;
		return;
	}
	inline void Join(const int &x,const int &y)
	{
		x_=Find(x);
		y_=Find(y);
		if(x_==y_) 
			return;
		par[x_]=y_;
		return;
	}
};
dsu ex,ds; //exist,disappear
//=====================================
inline void deal(int x,int y,const int &val)
{
	int ago[2]={x,y};
	int tmp=lca(x,y);
	if(tmp!=x) ds.range(dfn[x]+1,dfnt[x],val);
	if(tmp!=y) ds.range(dfn[y]+1,dfnt[y],val);
	while(top[x]!=top[y]) {
		if(dep[top[x]]>dep[top[y]]) {
			ex.range(dfn[top[x]],dfn[x],val);
			ds.range(dfn[x]+1,dfn[ago[0]]-1,val);
			ds.range(dfnt[ago[0]]+1,dfnt[top[x]],val);
			ago[0]=top[x];
			x=top[x]; x=fa[x];
		}
		else {
			ex.range(dfn[top[y]],dfn[y],val);
			ds.range(dfn[y]+1,dfn[ago[1]]-1,val);
			ds.range(dfnt[ago[1]]+1,dfnt[top[y]],val);
			ago[1]=top[y];
			y=top[y]; y=fa[y];
		}
	}
	if(dep[x]>dep[y]) 
		Swap(x,y),Swap(ago[0],ago[1]);
	ex.range(dfn[x]+1,dfn[y],val);
	ds.range(dfnt[x]+1,dfnt[1],val);
	ds.range(2,dfn[x],val);
	if(x==y) {
		if(ago[0]!=x&&ago[1]!=y) {
			if(dfn[ago[0]]>dfn[ago[1]]) 
				Swap(ago[0],ago[1]);
			ds.range(dfn[y]+1,dfn[ago[0]]-1,val);
			ds.range(dfnt[ago[0]]+1,dfn[ago[1]]-1,val);
			ds.range(dfnt[ago[1]]+1,dfnt[y],val);
			return;
		}
	}
	if(ago[1]!=y) {
		ds.range(dfn[y]+1,dfn[ago[1]]-1,val);
		ds.range(dfnt[ago[1]]+1,dfnt[y],val);
	}
	if(ago[0]!=x) {
		ds.range(((x==y) ? dfn[y] : dfnt[y])+1,dfn[ago[0]]-1,val);
		ds.range(dfnt[ago[0]]+1,dfnt[x],val);
	}
	else ds.range(dfnt[y]+1,dfnt[x],val);
	return;
}
//=====================================
struct data
{
	int x,y;
	LL weight;
}a[N];
inline bool cmp(const data &a,const data &b)
{
	return a.weight>b.weight;
}
LL ans=1e16;
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,tmp;
	LL z;
	read(n); read(m);
	for(i=1;i<=n-1;i++) {
		read(x); read(y); read(z);
		AddEdge(x,y,z);
		AddEdge(y,x,z);
	}
	dfs1(1,0);
	dfs2(1);
	for(i=1;i<=m;i++) {
		read(a[i].x); read(a[i].y);
		tmp=lca(a[i].x,a[i].y);
		a[i].weight=w[a[i].x]+w[a[i].y]-2ll*w[tmp];
	}
	sort(a+1,a+m+1,cmp);
	ex.reset(n+5);
	ds.reset(n+5);
	dfnt[0]=dfn[0]=INF;
	for(i=1;i<=m;i++) {
		if(a[i].x==a[i].y)
			continue;
		deal(a[i].x,a[i].y,a[i].weight);
	}
		
	//ex.Max ds.Max
	for(i=2;i<=n;i++)
		ans=min(ans,max(ds.Max[dfn[i]],ex.Max[dfn[i]]-(w[i]-w[fa[i]])));
	printf("%lld\n",ans);
	return 0;
}

