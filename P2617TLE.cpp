#include<vector>
#include<cstdio>
#include<cstdlib>
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
struct Node
{
	int lc,rc;
	int size;
	int val,pri;
}t[20*N];
int pool=0;
#define newnode(x) (pool++,t[pool].lc=t[pool].lc=0,t[pool].size=1,t[pool].val=x,t[pool].pri=rand(),pool) 
#define update(x) t[x].size=t[t[x].lc].size+t[t[x].rc].size+1
void split(int now,const int &key,int &x,int &y) //<= >
{
	if(now==0) 
		return x=y=0,void();
	return (t[now].val<=key) 
		? (x=now,split(t[now].rc,key,t[now].rc,y),update(now),void())
		: (y=now,split(t[now].lc,key,x,t[now].lc),update(now),void());
}
int merge(int x,int y)
{
	if(x==0||y==0)
		return x+y;
	return (t[x].pri>t[y].pri) 
		? (t[x].rc=merge(t[x].rc,y),update(x),x)
		: (t[y].lc=merge(x,t[y].lc),update(y),y); 
}
inline void insert(int &rt,const int &key)
{
	int x,y;
	split(rt,key,x,y);
	rt=merge(merge(x,newnode(key)),y);
	return;
}
inline void erase(int &rt,const int &key)
{
	int x,y,z;
	split(rt,key-1,x,z);
	split(z,key,y,z);
	y=merge(t[y].lc,t[y].rc);
	z=merge(y,z);
	rt=merge(x,z);
	return;
}
inline int findrank(int &rt,const int &key)
{
	int x,y,z;
	split(rt,key-1,x,y);
	z=t[x].size;
	rt=merge(x,y);
	return z;
}
//====================================================
int root[4*N];
int a[N];
void edit(int now,const int &pos,const int &key,const int &l,const int &r)
{
	erase(root[now],a[pos]);
	insert(root[now],key);
	if(l==r) return;
	int mid=(l+r)>>1;
	if(pos<=mid) edit(now<<1,pos,key,l,mid);
	else edit(now<<1|1,pos,key,mid+1,r);
	return;
}
int getrank(int now,const int &key,const int &x,const int &y,const int &l,const int &r)
{
	if(r<x||l>y) return 0;
	if(x<=l&&r<=y) 
		return findrank(root[now],key);
	int mid=(l+r)>>1;
	return getrank(now<<1,key,x,y,l,mid)+getrank(now<<1|1,key,x,y,mid+1,r);
}
int n,m;
struct quiz
{
	int opt;
	int x,y,z;
}q[N];
vector<int> v;
int main()
{
//	freopen("1.in","r",stdin);
	srand(20040524);
	rint i;
	register char opt;
	int L,R,mid;
	read(n); read(m);
	for(i=1;i<=n;i++) {
		read(a[i]);
		v.push_back(a[i]);
	}	
	for(i=1;i<=m;i++) {
		for(opt=getc();opt!='Q'&&opt!='C';opt=getc());
		if(opt=='Q') q[i].opt=1;
		else q[i].opt=2;
		read(q[i].x); read(q[i].y);
		if(q[i].opt==1) read(q[i].z); 
		else v.push_back(q[i].y);
	}
	sort(v.begin(),v.end());
	v.erase(unique(v.begin(),v.end()),v.end());
	for(i=1;i<=n;i++) 
		a[i]=(int)(lower_bound(v.begin(),v.end(),a[i])-v.begin())+1;
	for(i=1;i<=m;i++) 
		if(q[i].opt==2) 
			q[i].y=(int)(lower_bound(v.begin(),v.end(),q[i].y)-v.begin())+1;
	for(i=1;i<=n;i++) 
		edit(1,i,a[i],1,n);
	for(i=1;i<=m;i++) {
		if(q[i].opt==1) {
			L=1,R=(int)v.size()+1;
			while(L+1<R) {
				mid=(L+R)>>1;
				if(getrank(1,mid,q[i].x,q[i].y,1,n)+1<=q[i].z) L=mid;
				else R=mid;
			}
			print(v[L-1]),putc('\n');
		}
		else edit(1,q[i].x,q[i].y,1,n),a[q[i].x]=q[i].y;
	}
	return 0;
}

