#include<vector>
#include<cstdio>
#include<iostream>
#include<algorithm>
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
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
struct Lazytree
{
	vector<int> v;
	inline void insert(int val) { v.insert(lower_bound(v.begin(),v.end(),val),val); }
	inline void erase(int val) { v.erase(lower_bound(v.begin(),v.end(),val)); }
	inline LL count(int l,int r) 
	{ 
		return (LL)(upper_bound(v.begin(),v.end(),r)-lower_bound(v.begin(),v.end(),l));
	}
	Lazytree() { v.clear(); }
};
const int N=2e4+5;
const int INF=(-1u)>>1;
struct Node
{
	int l,r;
	Lazytree S;
}t[4*N];
#define lc (now<<1)
#define rc (now<<1|1)
int a[N];
void Build(int now,int l,int r)
{
	t[now].l=l;
	t[now].r=r;
	if(l==r) return;
	int mid=(l+r)>>1;
	Build(lc,l,mid);
	Build(rc,mid+1,r);
	return;
}
void del(int now,int pos,int val)
{
	if(pos<t[now].l||pos>t[now].r) 
		return;
	t[now].S.erase(val);
	if(pos==t[now].l&&t[now].l==t[now].r)
		return;
	del(lc,pos,val);
	del(rc,pos,val);
	return;
}
void add(int now,int pos,int val)
{
	if(pos<t[now].l||pos>t[now].r) 
		return;
	t[now].S.insert(val);
	if(pos==t[now].l&&t[now].l==t[now].r)
		return;
	add(lc,pos,val);
	add(rc,pos,val);
	return;
}
LL count(int now,int x,int y,int vl,int vr)
{
	if(y<t[now].l||x>t[now].r) 
		return 0;
	if(x<=t[now].l&&t[now].r<=y) 
		return t[now].S.count(vl,vr);
	return count(lc,x,y,vl,vr)+count(rc,x,y,vl,vr);
}

int n,m;
int main()
{
//	freopen("1.in","r",stdin);
	register int i;
	int x,y;
	read(n); 
	for(i=1;i<=n;i++) 
		read(a[i]);
	Build(1,1,n);
	for(i=1;i<=n;i++) 
		add(1,i,a[i]);
	LL ans=0;
	for(i=1;i<=n-1;i++) 
		ans+=count(1,i+1,n,1,a[i]-1);
	print(ans); putc('\n');	
	read(m);
	while(m--) {
		read(x); read(y);
		if(x>y) swap(x,y);
		ans+=count(1,x+1,y-1,a[x]+1,INF);
		ans-=count(1,x+1,y-1,0,a[x]-1);
		ans+=count(1,x+1,y-1,0,a[y]-1);
		ans-=count(1,x+1,y-1,a[y]+1,INF);
		if(a[x]>a[y]) ans--;
		else if(a[x]<a[y]) ans++;
		
		del(1,x,a[x]);
		del(1,y,a[y]);
		add(1,y,a[x]);
		add(1,x,a[y]);
		swap(a[x],a[y]);
		
		print(ans); putc('\n');	
	}
	return 0;
}


