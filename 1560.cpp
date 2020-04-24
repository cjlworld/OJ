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
//============================================
const int N=3e4+5;
const int INF=(-1u)>>1;
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
//==================================================
int son[N]; //weigh son
int dep[N]; //deep
int fa[N]; //father
int sum[N];
int a[N];
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
			son[u]=v;
			tmp=sum[v];
		}
		sum[u]+=sum[v];
	}
	return;
}
int dfn[N],times=0; //times
int top[N]; //top of link
int org[N];
void dfs2(int u)
{
	int i,v;
	dfn[u]=++times;
	org[times]=u;
	if(u==son[fa[u]]) top[u]=top[fa[u]];
	else top[u]=u;
	if(son[u]==0) 
		return;
	dfs2(son[u]);
	for(i=one[u];i>0;i=Next[i]) {
		v=ver[i];
		if(v==fa[u]||v==son[u]) continue;
		dfs2(v);
	}
	return;
}
//==============================================
struct node
{
	int l,r;
	int val;
	int sum;
	#define l(x) t[x].l
	#define r(x) t[x].r
	#define val(x) t[x].val
	#define sum(x) t[x].sum
}t[4*N];
#define lc (now<<1)
#define rc (now<<1|1)
inline void pushup(const int &now)
{
	val(now)=max(val(lc),val(rc));
	sum(now)=sum(lc)+sum(rc);
	return;
}
void Build(int now,int l,int r)
{
	l(now)=l;
	r(now)=r;
	if(l==r) {
		sum(now)=val(now)=a[org[l]];
		return;
	}
	int mid=(l+r)>>1;
	Build(lc,l,mid);
	Build(rc,mid+1,r);
	pushup(now);
	return;
}
void edit(int now,const int &x,const int &key)
{
	if(x<l(now)||x>r(now)) 
		return;
	if(l(now)==r(now)&&l(now)==x) {
		val(now)=key;
		sum(now)=key;
		return;
	}
	edit(lc,x,key);
	edit(rc,x,key);
	pushup(now);
	return;
}
node query(int now,const int &x,const int &y)
{
	if(y<l(now)||x>r(now)) 
		return node{0,0,-INF,0};
	if(x<=l(now)&&r(now)<=y) 
		return t[now];
	node p1,p2,res;
	p1=query(lc,x,y);
	p2=query(rc,x,y);
	res.val=max(p1.val,p2.val);
	res.sum=p1.sum+p2.sum;
	return res;
}
//=================================================
int Qmax(int x,int y)
{
	int res=-INF;
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]]) 
			swap(x,y);
		res=max(res,query(1,dfn[top[x]],dfn[x]).val);
		x=top[x]; x=fa[x];
	}
	if(dep[x]<dep[y]) 
		swap(x,y);
	res=max(res,query(1,dfn[y],dfn[x]).val);
	return res;
}
int Qsum(int x,int y)
{
	int res=0;
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]]) 
			swap(x,y);
		res+=query(1,dfn[top[x]],dfn[x]).sum;
		x=top[x]; x=fa[x];
	}
	if(dep[x]<dep[y]) 
		swap(x,y);
	res+=query(1,dfn[y],dfn[x]).sum;
	return res;
}
//================================================
int n,m,q;
char opt[10];
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;	
	read(n);
	for(i=1;i<=n-1;i++) {
		read(x); read(y);
		AddEdge(x,y);
		AddEdge(y,x);
	}
	for(i=1;i<=n;i++) 
		read(a[i]);
	dfs1(1,0);
	dfs2(1);
	Build(1,1,n);
	read(m);
	for(i=1;i<=m;i++) {
		scanf("%s",opt+1);
		if(opt[1]=='C') {
			read(x); read(y);
			edit(1,dfn[x],y);
		}
		else if(opt[2]=='M') {
			read(x); read(y);
			printf("%d\n",Qmax(x,y));
		}
		else {
			read(x); read(y);
			printf("%d\n",Qsum(x,y));
		}
	}	
	return 0;
}

