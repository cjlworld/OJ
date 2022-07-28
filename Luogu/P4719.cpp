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
#include<complex>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

inline void relax(int& a,const int& b) { a=((a>b) ? a : b); }

const int N=2e5+5,INF=0x3f3f3f3f;

struct Matrix
{
	int n,m;
	int a[3][3];
	Matrix(int n=0,int m=0) : n(n),m(m) 
		{ memset(a,-0x3f,sizeof a); }
};
Matrix unit;
Matrix mul(Matrix x,Matrix y)
{
	Matrix z(x.n,y.m);
//	printf("the size of Matrix x is (%d , %d)\n",x.n,x.m);
//	printf("the size of Matrix z is (%d , %d)\n",z.n,z.m);
	int i,j,k;
	for(i=1;i<=z.n;i++) 
		for(j=1;j<=z.m;j++) 
			for(k=1;k<=y.n;k++) 
				relax(z.a[i][j],x.a[i][k]+y.a[k][j]);
	return z;
}

int one[N],idx;
int ver[N],Next[N];
inline void AddEdge(int a,int b)
{
	Next[idx]=one[a]; ver[idx]=b; one[a]=idx++;
	Next[idx]=one[b]; ver[idx]=a; one[b]=idx++;
}

int dep[N],siz[N],son[N],fat[N];
int dfn[N],top[N],org[N],ed[N],times;

void dfs1(int x,int fa)
{
	dep[x]=dep[fa]+1;
	siz[x]=1;
	fat[x]=fa;
	
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		dfs1(y,x);
		siz[x]+=siz[y];
		if(siz[y]>siz[son[x]])
			son[x]=y;
	}
}

void dfs2(int x)
{
	dfn[x]=++times;
	org[times]=x;
	
	if(son[fat[x]]==x) top[x]=top[fat[x]];
	else top[x]=x;
	
	if(son[x]) dfs2(son[x]),ed[x]=ed[son[x]];
	else ed[x]=x;
	
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(y==fat[x] || y==son[x]) continue;
		dfs2(y);
	}
}

int n,m;
Matrix t[4*N],g[N];
// t[] 对 g[] 建树。  
#define lc (now<<1)
#define rc (now<<1|1)

Matrix query(int now,int x,int y,int l,int r)
{
	if(x<=l && r<=y) return t[now];
	int mid=(l+r)>>1;
	Matrix res=unit;
	if(x<=mid) res=mul(res,query(lc,x,y,l,mid));
	if(y>=mid+1) res=mul(res,query(rc,x,y,mid+1,r));
	return res;
}

void Update(int now,int pos,int l,int r)
{
	if(l==r && l==pos) 
		return t[now]=g[l],void();
	int mid=(l+r)>>1;
	if(pos<=mid) Update(lc,pos,l,mid);
	else Update(rc,pos,mid+1,r);
	t[now]=mul(t[lc],t[rc]);
}

void Build(int now,int l,int r)
{
	t[now]=unit;
	if(l==r) return;
	int mid=(l+r)>>1;
	Build(lc,l,mid);
	Build(rc,mid+1,r);
}

Matrix ask(int x) 
{
	return query(1,dfn[top[x]],dfn[ed[x]],1,n);
}

int a[N];
void TUpdate(int x,int w)
{
	g[dfn[x]].a[2][1]+=w-a[x]; 
	// 注意区别 点上的编号，dfn[] , 以及 t[] 中的编号，是不一样的。  
	a[x]=w;
	
	static Matrix lt,nw;
	while(x) {
		lt=ask(x);
		Update(1,dfn[x],1,n); // 改变 x 在树中的值 为 g[dfn[x]] .
		// g[dfn[x]] 我们在 上一重循环已经修改好了。 
		nw=ask(x);
		
		// 重边：由于我们在 query 时 是根据 Segment (f[son],f[son...])现算, 
			//	所以只要改变在 t[] 的值即可，不用更新 g[].
		// 轻边: 改变 g[] ,需要更新。 
		x=top[x]; x=fat[x];
		
		g[dfn[x]].a[1][1]+=max(nw.a[1][1],nw.a[2][1])-max(lt.a[1][1],lt.a[2][1]);
		g[dfn[x]].a[1][2]=g[dfn[x]].a[1][1];
		g[dfn[x]].a[2][1]+=nw.a[1][1]-lt.a[1][1];
	}
}

int f[N][2];
void dp(int x)
{
	f[x][0]=0; f[x][1]=a[x];	
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(y==fat[x]) continue;
		dp(y);
		f[x][0]+=max(f[y][0],f[y][1]);
		f[x][1]+=f[y][0];
	}
	
	Matrix& val=g[dfn[x]];
	val.n=val.m=2;
	val.a[1][1]=val.a[1][2]=0;
	val.a[2][1]=a[x];
	val.a[2][2]=-INF;
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(y==son[x] || y==fat[x]) continue;
		
		val.a[1][1]+=max(f[y][0],f[y][1]);
		val.a[2][1]+=f[y][0];
	}
	val.a[1][2]=val.a[1][1];
	Update(1,dfn[x],1,n);
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y;
	
	unit.n=unit.m=2;
	unit.a[1][1]=unit.a[2][2]=0;
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)
		scanf("%d",&a[i]);
		
	memset(one,-1,sizeof one);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(x,y);
	}
	
	Build(1,1,n);
	dfs1(1,0); 
	dfs2(1);
	
//	printf("now print the dfn[] : ");
//	for(i=1;i<=n;i++) printf("%d ",dfn[i]);
//	printf("\n");
	dp(1);
	
	Matrix ans;
	while(m--) {
		scanf("%d%d",&x,&y);
		TUpdate(x,y);
		ans=ask(1);
		printf("%d\n",max(ans.a[1][1],ans.a[2][1]));
	}
	return 0;
}

