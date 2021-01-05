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
typedef pair<int,int> PII;

inline void relax(int &a,const int &b) { a=((a>b) ? a :b); }

namespace FastIO
{
	const int _SIZE = (1 << 21) + 1;
	
	inline char NextChar()
	{
		static char ibuf[_SIZE];
		static char *iS,*iT;
		
		if(iS==iT) 
			iS=ibuf,iT=iS+fread(ibuf,1,_SIZE,stdin);
		return (iS == iT ? EOF : *iS++);
	}
	
	template <class T>
	inline void read(T &x) 
	{
		static char c;
		static bool sign;
		
		x=0;
		sign=false;
	    for (c=NextChar();c<'0'||c>'9';c=NextChar())
	        if (c=='-') sign=true;
	    for (;c>='0'&&c<='9';c=NextChar()) 
			x=(x<<1)+(x<<3)+(c&15);
		if(sign) x=-x;
	}
	
	char obuf[_SIZE];
	char *oS=obuf,*oT=oS+_SIZE-1;
	inline void flush() 
	{
	    fwrite(obuf,1,oS-obuf,stdout);
	    oS=obuf;
	}
	inline void putc(const char &x) 
	{
	    *oS++=x;
	    if(oS==oT) flush();
	}
	
	template <class T>
	inline void print(T x) {
		static char qu[50];
		static int qr;
		
	    if (!x) {
	    	putc('0');
	    	return;
		}
	    if (x<0) putc('-'),x=-x;
	    for(qr=1;x;qr++,x/=10) qu[qr]=x%10+'0';
	    for(qr--;qr>=1;qr--) putc(qu[qr]);
	}

	struct Flusher_ 
	{
 	   ~Flusher_() { flush(); }
	}io_flusher_;
}
using FastIO::read;
using FastIO::print;
#define enter FastIO::putc('\n')

const int N=1e6+5,INF=0x3f3f3f3f;

int one[N],idx;
int ver[N<<1],Next[N<<1];
inline void AddEdge(int a,int b)
{
	Next[idx]=one[a]; ver[idx]=b; one[a]=idx++;
	Next[idx]=one[b]; ver[idx]=a; one[b]=idx++;
}

struct Matrix 
{
	int n,m;
	int a[3][3];
	Matrix(int n=0,int m=0) : n(n),m(m) 
	{
		memset(a,-0x3f,sizeof a);
	}
};

Matrix mul(const Matrix& x,const Matrix& y)
{
	Matrix z(x.n,y.m);
//	printf("the size of Matrix z is (%d , %d)\n",z.n,z.m);
	int i,j,k;
	for(i=1;i<=z.n;i++) 
		for(j=1;j<=z.m;j++) 
			for(k=1;k<=y.n;k++) 
				relax(z.a[i][j],x.a[i][k]+y.a[k][j]);
	return z;
}

struct Node
{
	int ch[2],fa;
	int siz;
	Matrix val,sum;
}t[N];

void pushup(int x)
{
	t[x].sum=t[x].val;
	if(t[x].ch[0]) t[x].sum=mul(t[t[x].ch[0]].sum,t[x].sum);
	if(t[x].ch[1]) t[x].sum=mul(t[x].sum,t[t[x].ch[1]].sum);
	
	t[x].siz=t[t[x].ch[0]].siz+t[t[x].ch[1]].siz+1;
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
//	printf("now splay node %d\n",x);
	while(!isroot(x)) {
//		printf("In the splay : the father is %d\n",t[x].fa);
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
		if(t[x].ch[1]) {
			Matrix& rv=t[t[x].ch[1]].sum;
			
			val.a[1][1]+=max(rv.a[1][1],rv.a[2][1]);
			val.a[1][2]=val.a[1][1];
			val.a[2][1]+=rv.a[1][1];
		}
		
		if(y) {
			Matrix& nw=t[y].sum;
			val.a[1][1]-=max(nw.a[1][1],nw.a[2][1]);
			val.a[1][2]=val.a[1][1];
			val.a[2][1]-=nw.a[1][1];
		}
		
		t[x].ch[1]=y;
		pushup(x);
	}
	splay(z);
}

int f[N][2],a[N],dep[N],maxdep;
void dp(int x,int fa)
{
	t[x].fa=fa;
	f[x][1]=a[x];
	f[x][0]=0;
	dep[x]=dep[fa]+1;
	relax(maxdep,dep[x]);
	
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		dp(y,x);
		f[x][0]+=max(f[y][0],f[y][1]);
		f[x][1]+=f[y][0];
	}
	
	Matrix& val=t[x].val;
	val.n=val.m=2;
	val.a[1][1]=val.a[1][2]=f[x][0];
	val.a[2][1]=f[x][1];
	val.a[2][2]=-INF;
	
	t[x].sum=val;
	t[x].siz=1;
	t[x].ch[0]=t[x].ch[1]=0;
}


int n,m;
int lastans;

namespace Force
{
	void Let_us_push_it_up(int x,PII o,PII w)
	{
		if(x==0) return;
		PII no(f[x][0],f[x][1]);
		f[x][0]+=max(w.first,w.second)-max(o.first,o.second);
		f[x][1]+=w.first-o.first;
		Let_us_push_it_up(t[x].fa,no,PII(f[x][0],f[x][1]));
	}
	
	void sol()
	{
		int x,y;
		while(m--) {
			read(x); read(y);
			x^=lastans;
			Let_us_push_it_up(t[x].fa,PII(f[x][0],f[x][1]),PII(f[x][0],f[x][1]-a[x]+y));
			f[x][1]+=y-a[x];
			a[x]=y;
			print(lastans=max(f[1][0],f[1][1])),enter;
		}
	}
}

namespace LCT
{
	void sol()
	{
		int x,y;
		while(m--) {
			read(x); read(y);
			x^=lastans;
			access(x);
			Matrix& val=t[x].val;
			val.a[2][1]+=y-a[x];
			a[x]=y;
			pushup(x); // ¸üÐÂsum;
			Matrix& sum=t[x].sum;
			print(lastans=max(sum.a[1][1],sum.a[2][1])),enter;
		}
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	srand((unsigned) time(0));
	int i;
	int x,y;
	
	read(n); read(m);
	for(i=1;i<=n;i++) read(a[i]);
	
	memset(one,-1,sizeof one);
	for(i=1;i<=n-1;i++) {
		read(x); read(y);
		AddEdge(x,y);
	}
	
	dp(1,0);	

	if(maxdep>1e3) LCT::sol(); 
	else Force::sol();
	return 0;
}
