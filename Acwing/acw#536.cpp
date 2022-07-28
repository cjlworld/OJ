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

inline void relax(LL& a,const LL& b) { a=((a>b) ? a : b); }

const int N=2e5+5;
const LL INF=0x3f3f3f3f3f3f3f3f,lowinf=1e15;

int one[N],idx;
int ver[N],Next[N];
inline void AddEdge(int a,int b)
{
	Next[idx]=one[a]; ver[idx]=b; one[a]=idx++;
	Next[idx]=one[b]; ver[idx]=a; one[b]=idx++;
}

struct Matrix 
{
	int n,m;
	LL a[2][2];
	Matrix(int n=0,int m=0) : n(n),m(m)
	{
		memset(a,-0x3f,sizeof a);
	}
};

Matrix mul(const Matrix& x,const Matrix& y)
{
	Matrix z(x.n,y.m);
	if(z.n!=2 || z.m!=2)
		printf("the size of z is (%d , %d)\n",z.n,z.m);
	int i,j,k;
	for(i=0;i<z.n;i++) 
		for(j=0;j<z.m;j++) 
			for(k=0;k<y.n;k++) 
				relax(z.a[i][j],x.a[i][k]+y.a[k][j]);
	return z;
}

struct Node
{
	int ch[2],fa;
	Matrix val,sum;
}t[N];

void pushup(int x)
{
	t[x].sum=t[x].val;
	if(t[x].ch[0]) t[x].sum=mul(t[t[x].ch[0]].sum,t[x].sum);
	if(t[x].ch[1]) t[x].sum=mul(t[x].sum,t[t[x].ch[1]].sum);
}

inline bool isroot(int x) { return (t[t[x].fa].ch[0]!=x && t[t[x].fa].ch[1]!=x); }

void rotate(int x)
{
	if(isroot(x)) return;
	int y=t[x].fa,z=t[y].fa;
	int k=(t[y].ch[1]==x);
	if(!isroot(y)) t[z].ch[t[z].ch[1]==y]=x;
	t[x].fa=z;
	t[y].ch[k]=t[x].ch[k^1]; t[t[x].ch[k^1]].fa=y;
	t[x].ch[k^1]=y; t[y].fa=x;
	pushup(y); pushup(x);
}

void splay(int x)
{
	int y,z;
	while(!isroot(x)) {
		y=t[x].fa; z=t[y].fa;
		if(!isroot(y)) {
			if((t[z].ch[1]==y)^(t[y].ch[1]==x)) 
				rotate(x);
			else rotate(y);
		}
		rotate(x);
	}
}

void access(int x)
{
	int z=x,y;
	for(y=0;x;y=x,x=t[x].fa) {
		splay(x);
		
		Matrix& val=t[x].val;
		if(t[x].ch[1]) { // change from the real son to weak son , so add the val;
			Matrix& rv=t[t[x].ch[1]].sum;
			val.a[0][0]+=max(rv.a[1][0],rv.a[0][0]);
			val.a[0][1]=val.a[0][0];
			val.a[1][0]+=rv.a[0][0];
		}
		if(y) { // del the val from weak son's;
			Matrix& nw=t[y].sum; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			val.a[0][0]-=max(nw.a[1][0],nw.a[0][0]);
			val.a[0][1]=val.a[0][0];
			val.a[1][0]-=nw.a[0][0];
		}
		
		t[x].ch[1]=y;
		pushup(x);
	}
	splay(z);
}

int n,m;
char type[20];
LL a[N],tot;
LL f[N][2];

void dp(int x,int fa)
{
	t[x].fa=fa;
	f[x][0]=0; f[x][1]=a[x];
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		dp(y,x);
		f[x][0]+=max(f[y][0],f[y][1]);
		f[x][1]+=f[y][0];
	}
	
	Matrix& val=t[x].val;
	val.n=val.m=2;
	val.a[0][1]=val.a[0][0]=f[x][0];
	val.a[1][0]=f[x][1]; val.a[1][1]=-INF;
	
	t[x].sum=t[x].val;
	t[x].ch[0]=t[x].ch[1]=0;
}

void Update(int x,int y)
{
	access(x);
	Matrix& val=t[x].val;
	if(y==0) val.a[1][0]+=lowinf;
	else val.a[1][0]-=lowinf;
	pushup(x);
//	printf("now t[x].sum is %lld , %lld\n",t[x].sum.a[0][0],t[x].sum.a[1][0]);
}

void Recover(int x,int y)
{
	access(x);
	Matrix& val=t[x].val;
	if(y==0) val.a[1][0]-=lowinf;
	else val.a[1][0]+=lowinf;
	pushup(x);
//	printf("now t[x].sum is %lld , %lld\n",t[x].sum.a[0][0],t[x].sum.a[1][0]);
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y;
	int px,py;
	
	scanf("%d%d%s",&n,&m,type);
	for(i=1;i<=n;i++) 
		scanf("%lld",&a[i]),tot+=a[i];
		
	memset(one,-1,sizeof one);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(x,y);
	}
	
	dp(1,0);

	while(m--) {
		scanf("%d%d%d%d",&px,&x,&py,&y);
		Update(px,x);
		Update(py,y);
		
		access(1);
		Matrix& sum=t[1].sum;
		LL ans=tot-max(sum.a[0][0],sum.a[1][0])+((x^1)+(y^1))*lowinf;
		
		if(ans>1e10) puts("-1");
		else printf("%lld\n",ans);
		
		Recover(px,x);
		Recover(py,y);
	}
	return 0;
}


