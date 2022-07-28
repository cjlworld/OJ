#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#define LL long long
using namespace std;
namespace FFIO
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
    for (;c>='0'&c<='9';c=gc()) 
		x=(x<<1)+(x<<3)+(c&15);
    x=(_sign) ? (~x+1) : x;
    return;
}
inline char rd()
{
	for(c=gc();c!='Q'&&c!='B';c=gc());
	return c;
}
// print a signed integer
template <class I>
inline void print(I x) {
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
using FFIO::read;
using FFIO::print;
using FFIO::putc;
//================================
const int N=100000+5;
struct node
{
	int lc,rc;
	int val;
	int pri;
	int id;
	int size;
	#define lc(x) t[x].lc
	#define rc(x) t[x].rc
	#define v(x) t[x].val
	#define p(x) t[x].pri
	#define id(x) t[x].id
	#define s(x) t[x].size
}t[N];
int root[N],cnt;
inline void update(const int &now)
{
	s(now)=s(lc(now))+s(rc(now))+1;
	return;
}
void split(int now,const int &key,int &x,int &y) //<= >
{
	if(now==0) {
		x=y=0;
		return;
	}
	if(v(now)<=key) {
		x=now;
		split(rc(now),key,rc(x),y);
	}
	else {
		y=now;
		split(lc(now),key,x,lc(y));
	}
	update(now);
	return;
}
int set_merge(int x,int y)
{
	if(x==0||y==0) 
		return x+y;
	int u,v;	
	if(p(x)*s(x)<p(y)*s(y)) 
		swap(x,y);
	split(y,v(x)-1,u,v);
	lc(x)=set_merge(lc(x),u);
	rc(x)=set_merge(rc(x),v);
	update(x);
	return x;
}
inline int getid(int now,int rank)
{
	if(rank<=0||rank>s(now)) 
		return -1;
	while(now>0&&rank>0) {
		if(s(lc(now))+1==rank) 
			return id(now);
		if(s(lc(now))+1>rank) 
			now=lc(now);
		else rank-=s(lc(now))+1,now=rc(now);
	}
	return -1;
}
inline int newnode(const int &id,const int &key)
{
	cnt++;
	v(cnt)=key;
	id(cnt)=id;
	p(cnt)=rand();
	lc(cnt)=rc(cnt)=0;
	s(cnt)=1;
	return cnt;
}
int par[N];
int Find(const int &x)
{
	if(x!=par[x]) return par[x]=Find(par[x]);
	return x;
}
inline void AddEdge(const int &x,const int &y)
{
	int x_=Find(x);
	int y_=Find(y);
	if(x_==y_) return;
	par[x_]=y_;
	root[y_]=set_merge(root[x_],root[y_]);
	return;
}
int n,m,q;
int main()
{
//	freopen("1.in","r",stdin);
	srand(unsigned(time(0)));
	register int i,j;
	int x,y,z;
	char opt;
	read(n); read(m);
	for(i=1;i<=n+2;i++) 
		par[i]=i;
	for(i=1;i<=n;i++) {
		read(x);
		root[i]=newnode(i,x);
	}
	for(i=1;i<=m;i++) {
		read(x); read(y);
		AddEdge(x,y);
	}
	read(q);
	for(i=1;i<=q;i++) {
		opt=FFIO::rd();
		read(x); read(y);
		if(opt=='Q') 
			print(getid(root[Find(x)],y)),putc('\n');
		else AddEdge(x,y);
	}
	FFIO::flush();
	return 0;
}

