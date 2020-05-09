#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
#define rint register int 
namespace FastIO
{
const int _SIZE = (1 << 21) + 1;
char ibuf[_SIZE],obuf[_SIZE];
char *iS,*iT;
char c;
char qu[55];
char *oS=obuf,*oT=oS+_SIZE-1;
bool _sign=false;
int qr;
// getchar
#define gc() (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, _SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++)
// print the remaining part
inline void flush() 
{
    fwrite(obuf,1,oS-obuf,stdout);
    oS=obuf;
    return;
}
// putchar
inline void putc(const char &x) 
{
    *oS++=x;
    if(oS==oT)
        flush();
    return;
}
// input a signed integer
template <class T>
inline void read(T &x) 
{
	x=0;
	_sign=false;
    for (c=gc();c<'0'||c>'9';c=gc())
        if (c=='-')
            _sign=true;
    for (;c>='0'&&c<='9';c=gc()) 
		x=(x<<1)+(x<<3)+(c&15);
    x=(_sign) ? (~x+1) : x;
    return;
}
// print a signed integer
template <class T>
inline void print(T x) {
    if (!x) {
    	putc('0');
    	return;
	}
    if (x<0)
        putc('-'),x=~x+1;
    while(x) qu[++qr]=x%10+'0',x/=10;
    while(qr) putc(qu[qr--]);
    return;
}
// no need to call flush at the end manually!
struct Flusher_ 
{
    ~Flusher_() { flush(); }
}io_flusher_;
}  // namespace io
using FastIO::read;
using FastIO::print;
using FastIO::putc;
//===========================
using namespace std;
const int N=2500+5;
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
//==========================================
#define min(a,b) (( (a) < (b) ) ? (a) : (b))
#define max(a,b) (( (a) > (b) ) ? (a) : (b)) 
int k,n;
int a[N],b[N]; //候选人i的招募费用，战斗值
double f[N][N];
int sum[N];
void Dp(const int &u)
{
	rint i,j,e,v;
	for(i=one[u];i>0;i=Next[i]) 
		Dp(ver[i]);
	for(i=one[u];i>0;i=Next[i]) {
		v=ver[i];
		for(j=min(k,sum[u]+1);j>=2;j--) {
			for(e=1;e<=min(j-1,sum[v]+1);e++) {
				f[u][j]=max(f[u][j],f[u][j-e]+f[v][e]);
			}
		}
	}
	return;
}
inline bool check(const double &t)
{
	memset(f,0xc2,sizeof f);
	for(rint i=1;i<=n;i++) {
		f[i][1]=(b[i]/1.0)-(a[i]/1.0)*t;
		f[i][0]=0.0;
	}
	f[0][1]=f[0][0]=0.0;
	Dp(0);
	return (f[0][k]<0);
}
void predfs(const int &u)
{
	rint i;
	sum[u]=1;
	for(i=one[u];i>0;i=Next[i]) 
		predfs(ver[i]);
	for(i=one[u];i>0;i=Next[i]) 
		sum[u]+=sum[ver[i]];
	return;
}
int main()
{
//	freopen("data.txt","r",stdin);
	read(k); read(n);
	k++;
	rint i;
	rint x;
	for(i=1;i<=n;i++) {
		read(a[i]);
		read(b[i]);
		read(x);
		AddEdge(x,i);
	}
	predfs(0);
	double L=0,R=1e5+5,mid;
	while(L+0.00001<R) {
		mid=(L+R)/2;
		if(check(mid)) R=mid;
		else L=mid;
	}
	printf("%.3lf",R);
	return 0;
}
