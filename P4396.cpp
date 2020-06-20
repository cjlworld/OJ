#include<cmath>
#include<cstdio>
#include<iostream>
#include<algorithm>
#define LL long long
#define rint register int
using namespace std;
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
inline char getc()
{
	return gc();
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
using FastIO::getc;
//=================================================
const int N=1e5+5;
int n,m;
struct Bits
{
	int c[N];
	int res;
	inline int lowbit(const int &x) { return x&(-x); }
	inline void update(int x,int y) 
	{
		for(;x<=n;x+=lowbit(x)) 
			c[x]+=y;
		return;
	}
	inline int sum(int x)
	{
		res=0;
		for(;x>=1;x-=lowbit(x)) 
			res+=c[x];
		return res;
	}
}C1,C2;
int a[N];
int t[N];
struct quiz
{
	int l,r;
	int a,b;
	int ans1,ans2;
	int o;
}q[N];
int siz;
inline bool cmp(const quiz &a,const quiz &b)
{
	if(a.l/siz!=b.l/siz) 
		return a.l<b.l;
	else return a.r<b.r;
}
inline bool rule(const quiz &a,const quiz &b)
{
	return a.o<b.o;
}
inline void Add(int pos)
{
	if(t[a[pos]]==0)
		C2.update(a[pos],1);
	C1.update(a[pos],1);
	++t[a[pos]];
	return;
}
inline void Sub(int pos)
{
	if(t[a[pos]]==1) 
		C2.update(a[pos],-1);
	C1.update(a[pos],-1);
	--t[a[pos]];
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	rint i;
	read(n); read(m);
	for(i=1;i<=n;i++) 
		read(a[i]);
	for(i=1;i<=m;i++) {
		read(q[i].l); read(q[i].r);
		read(q[i].a); read(q[i].b);
		q[i].o=i;
	}
	siz=sqrt(n);
	sort(q+1,q+m+1,cmp);
	rint head=1,tail=0;
	for(i=1;i<=m;i++) {
		while(head>q[i].l) Add(--head);
		while(tail<q[i].r) Add(++tail);
		while(head<q[i].l) Sub(head++);
		while(tail>q[i].r) Sub(tail--);
		q[i].ans1=C1.sum(q[i].b)-C1.sum(q[i].a-1);
		q[i].ans2=C2.sum(q[i].b)-C2.sum(q[i].a-1);
	}
	sort(q+1,q+m+1,rule);
	for(i=1;i<=m;i++) {
		print(q[i].ans1); putc(' ');
		print(q[i].ans2); putc('\n');
	}
	return 0;
}

