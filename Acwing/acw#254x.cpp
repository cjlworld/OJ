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

template<class T>
inline void relax(T& a,const T& b) { a=((a>b) ? a : b); }
template<class T>
inline void tense(T& a,const T& b) { a=((a<b) ? a : b); }

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
	char *oS=obuf,*oT=obuf+_SIZE-1;
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
const double alpha=0.75;

struct Node
{
	int lc,rc;
	int x,y;
	int judge;
	int L,R,D,U;
	int siz;
}t[N];
int idx,root;

inline bool cmpx(const int& a,const int& b) { return t[a].x<t[b].x; }
inline bool cmpy(const int& a,const int& b) { return t[a].y<t[b].y; }

void Maintain(int x)
{
	t[x].L=t[x].R=t[x].x;
	t[x].U=t[x].D=t[x].y;
	
	if(t[x].lc) {
		tense(t[x].L,t[t[x].lc].L);
		relax(t[x].R,t[t[x].lc].R);
		tense(t[x].D,t[t[x].lc].D);
		relax(t[x].U,t[t[x].lc].U);
	}
	if(t[x].rc) {
		tense(t[x].L,t[t[x].rc].L);
		relax(t[x].R,t[t[x].rc].R);
		tense(t[x].D,t[t[x].rc].D);
		relax(t[x].U,t[t[x].rc].U);
	}
	
	t[x].siz=t[t[x].lc].siz+t[t[x].rc].siz+1;
}

int sq[N],tt;

void ldr(int now)
{
	if(!now) return;
	ldr(t[now].lc);
	sq[++tt]=now;
	ldr(t[now].rc);
}

inline double sqr(const double& x) { return x*x; }

int rebuild(int l,int r,int flag)
{
	if(l>r) return 0;
	int mid=(l+r)>>1,cur;
	double avx=0,avy=0,sx=0,sy=0;
	for(int i=l;i<=r;i++) 
		avx+=t[sq[i]].x,avy+=t[sq[i]].y;
	avx/=(r-l+1),avy/=(r-l+1);
	for(int i=l;i<=r;i++) {
		sx+=sqr(t[sq[i]].x-avx);
		sy+=sqr(t[sq[i]].y-avy);
	}

	if(sx>sy) 
		nth_element(sq+l,sq+mid,sq+r+1,cmpx),t[cur=sq[mid]].judge=1;
	else nth_element(sq+l,sq+mid,sq+r+1,cmpy),t[cur=sq[mid]].judge=0;
	
	t[cur].lc=rebuild(l,mid-1,flag^1);
	t[cur].rc=rebuild(mid+1,r,flag^1);
	Maintain(cur);
	return cur;
}

void check(int& now)
{
	if(alpha*t[now].siz<t[t[now].lc].siz || alpha*t[now].siz<t[t[now].rc].siz) 
		tt=0,ldr(now),now=rebuild(1,tt,t[now].judge);
}

void insert(int& now,int id)
{
	if(!now) {
		now=id;
		return;
	}
	t[id].judge^=1;
	if(t[now].judge) {
		if(t[id].x<=t[now].x) insert(t[now].lc,id);
		else insert(t[now].rc,id);
	}
	else {
		if(t[id].y<=t[now].y) insert(t[now].lc,id);
		else insert(t[now].rc,id);
	}
	Maintain(now); check(now);
}

int NewNode(int x,int y)
{
	idx++;
	t[idx].x=x,t[idx].y=y;
	t[idx].lc=t[idx].rc=0;
	t[idx].judge=(rand()&1);
	Maintain(idx);
	return idx;
}

int mindist(int now,int x,int y)
{
	int res=0;
	res+=max(0,t[now].L-x);
	res+=max(0,x-t[now].R);
	res+=max(0,t[now].D-y);
	res+=max(0,y-t[now].U);
	return res;
}

void query(int now,int x,int y,int& res)
{
	tense(res,abs(t[now].x-x)+abs(t[now].y-y));
	int dl=INF,dr=INF;
	if(t[now].lc) dl=mindist(t[now].lc,x,y);
	if(t[now].rc) dr=mindist(t[now].rc,x,y);
	
	if(dl<dr) {
		if(dl<res) query(t[now].lc,x,y,res);
		if(dr<res) query(t[now].rc,x,y,res);
	} 
	else {
		if(dr<res) query(t[now].rc,x,y,res);
		if(dl<res) query(t[now].lc,x,y,res);
	}
}

int n,m;

int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	srand((unsigned) time(0));
	int i;
	int opt,x,y;
	
	read(n); read(m);
	for(i=1;i<=n;i++) {
		read(x); read(y);
		NewNode(x,y); sq[++tt]=i;
	}
	root=rebuild(1,tt,0);
	while(m--) {
		read(opt); read(x); read(y);
		if(opt==1) 
			insert(root,NewNode(x,y));
		else {
			int ans=INF;
			query(root,x,y,ans);
			print(ans),enter;
		}
		if(m%10000==0) cerr<<m<<" "<<clock()<<endl;
	}
	return 0;
}
