#include<cstdio>
#include<iostream>
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
//==============================================
const int N=256;
const int M=500000+5; 
int n,m;
int a[N],k[N];
bool f[M];
int par[M];
int Find(const int &x)
{
	if(x!=par[x]) return par[x]=Find(par[x]);
	return x;
}
int main()
{
//	freopen("1.in","r",stdin);
	rint i,j,r;
	int x;
	read(n); read(m);
	for(i=1;i<=n;i++) {
		read(k[i]);
		read(a[i]);
	}
	for(i=1;i<=M-1;i++) 
		par[i]=i;
	f[0]=true;
	for(i=1;i<=n;i++) {
		for(j=Find(M-1);j>0;j=Find(j-1)) {
			for(r=1;r<=a[i]&&j-r*k[i]>=0;r++) 
				if(f[j-r*k[i]]) {
					f[j]=true;
					par[j]=Find(j-1);
					break;
				}
		}
	}
	while(m--) {
		read(x);
		if(f[x]) putc('Y'),putc('e'),putc('s');
		else putc('N'),putc('o');
		putc('\n');
	}
	return 0;
}

