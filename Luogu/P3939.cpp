#include<vector>
#include<cstdio>
#include<iostream>
#include<algorithm>
typedef long long LL;
typedef unsigned long long ULL;
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
#define gc() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,_SIZE,stdin),(iS==iT?EOF:*iS++)):*iS++)
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
using namespace std;
const int N=3e5+5;
struct Lazytree
{
	vector<int> v;
	inline int count(int l,int r) { return (int)(upper_bound(v.begin(),v.end(),r)-lower_bound(v.begin(),v.end(),l)); }
}t[N];
int a[N];
int n,m;
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z,opt;
	read(n); read(m);
	for(i=1;i<=n;i++) {
		read(a[i]);
		t[a[i]].v.push_back(i);
	}
	for(i=1;i<=m;i++) {
		read(opt); read(x);
		if(opt==1) {
			read(y); read(z);
			print(t[z].count(x,y));	putc('\n');
		}
		else {
			if(a[x+1]==a[x]) continue;
			t[a[x]].v[lower_bound(t[a[x]].v.begin(),t[a[x]].v.end(),x)-t[a[x]].v.begin()]++;
			t[a[x+1]].v[lower_bound(t[a[x+1]].v.begin(),t[a[x+1]].v.end(),x+1)-t[a[x+1]].v.begin()]--;
			swap(a[x+1],a[x]);
		}
	}
	return 0;
}

