#include<set>
#include<vector>
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
inline void print(T x,char ch='\n') {
    if (!x) {
    	putc('0');
    	return;
	}
    if (x<0)
        putc('-'),x=~x+1;
    while(x) qu[++qr]=x%10+'0',x/=10;
    while(qr) putc(qu[qr--]);
    putc(ch);
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
	unsigned int sum;
}t[300*N];
int pool=0;
#define lowbit(x) ((x)&(-(x)))
int n,m;
int root[N];
void Insert(int &now,const int &key,const int &l,const int &r)
{
	if(!now) now=++pool;
	t[now].sum++;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(key<=mid) Insert(t[now].lc,key,l,mid);
	else Insert(t[now].rc,key,mid+1,r);
	return;
}
void erase(int now,const int &key,const int &l,const int &r)
{
	t[now].sum--;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(key<=mid) erase(t[now].lc,key,l,mid);
	else erase(t[now].rc,key,mid+1,r);
	return;
}
set<int> tmp;
int tmpa[N];
int tmps[N];
int querykth(unsigned rank,const int &l,const int &r)
{
	if(l==r) return l;
	rint i;
	unsigned int temp=0;
	for(i=1;i<=tmpa[0];i++) temp+=t[t[tmpa[i]].lc].sum;
	for(i=1;i<=tmps[0];i++) temp-=t[t[tmps[i]].lc].sum;
	int mid=(l+r)>>1;
	if(rank<=temp) {
		for(i=1;i<=tmpa[0];i++) tmpa[i]=t[tmpa[i]].lc;
		for(i=1;i<=tmps[0];i++) tmps[i]=t[tmps[i]].lc;
		return querykth(rank,l,mid);
	}
	else {
		for(i=1;i<=tmpa[0];i++) tmpa[i]=t[tmpa[i]].rc;
		for(i=1;i<=tmps[0];i++) tmps[i]=t[tmps[i]].rc;
		return querykth(rank-temp,mid+1,r);
	}
}
vector<int> v;
inline int findkth(int l,int r,int rank)
{
	rint i;
	tmp.clear();
	tmpa[0]=tmps[0]=0;
	for(i=r;i>=1;i-=lowbit(i)) 
		tmp.insert(i);
	for(i=l-1;i>=1;i-=lowbit(i)) {
		if(tmp.count(i)) 
			tmp.erase(i);
		else tmps[++tmps[0]]=root[i];
	}
	for(set<int>::iterator it=tmp.begin();it!=tmp.end();it++)
		tmpa[++tmpa[0]]=root[*it];
	return querykth(rank,1,v.size());
}
inline void Add(int pos,const int &key)
{
	for(;pos<=n;pos+=lowbit(pos)) 
		Insert(root[pos],key,1,v.size());
	return;
}
inline void Sub(int pos,const int &key)
{
	for(;pos<=n;pos+=lowbit(pos)) 
		erase(root[pos],key,1,v.size());
	return;
}
struct quiz
{
	int opt;
	int x,y,z;
}q[N];
int a[N];
int main()
{
//	freopen("1.in","r",stdin);
	rint i;
	register char opt;
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
		Add(i,a[i]);
	for(i=1;i<=m;i++) {
		if(q[i].opt==1) 
			print(v[findkth(q[i].x,q[i].y,q[i].z)-1]);
		else Sub(q[i].x,a[q[i].x]),Add(q[i].x,q[i].y),a[q[i].x]=q[i].y;
	}
	return 0;
}

