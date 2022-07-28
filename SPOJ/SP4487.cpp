#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<ctime>
#define LL long long
namespace FastIO
{
template<class T>
inline void read(T &x)
{
	x=0;
	char c=getchar();
	bool sign=false;
	while(c<'0'||c>'9') {
		if(c=='-') sign=true;
		c=getchar();
	}
	while(c>='0'&&c<='9') {
		x=(x<<1)+(x<<3)+(c-'0');
		c=getchar();
	}
	if(sign) x=~x+1;
	return;
}
short bcc[22],top=0;
template<class T>
inline void print(T x)
{
	top=0;
	if(!x) {
		putchar('0');
		return;
	}
	if(x<0) putchar('-'),x=~x+1;
	while(x) {
		bcc[++top]=x%10;
		x=x/10;
	}
	while(top>=1) {
		putchar(48+bcc[top]);
		--top;
	}
	return;
}
template<class T>
inline T max(const T &x,const T &y)
{
	if(x>y) return x;
	else return y;
}
}
#define rint register int 
#define read(x) FastIO::read(x) 
#define print(x) FastIO::print(x)
#define max(x,y) FastIO::max(x,y)
//===============================
using namespace std;
//T meanings
//a balanced tree : insert one num; delete one num; edit one num; Q max sequce in a range
const int N=3e5+5;
struct node
{
	int lc,rc;
	int size;
	int val;
	int pri;
	int sum,qm,ql,qr;
	#define lc(x) t[x].lc
	#define rc(x) t[x].rc
	#define v(x) t[x].val
	#define s(x) t[x].size
	#define sum(x) t[x].sum
	#define qm(x) t[x].qm
	#define ql(x) t[x].ql
	#define qr(x) t[x].qr
	#define p(x) t[x].pri
};
node t[N];
int root=0,cnt=0;
inline void update(const int &now)
{
	s(now)=s(lc(now))+s(rc(now))+1;
	sum(now)=sum(lc(now))+sum(rc(now))+v(now);
	qm(now)=max(qr(lc(now))+v(now),ql(rc(now))+v(now));
	if(lc(now)) qm(now)=max(qm(now),qm(lc(now)));
	if(rc(now)) qm(now)=max(qm(now),qm(rc(now)));
	qm(now)=max(qm(now),qr(lc(now))+ql(rc(now))+v(now));
	ql(now)=max(ql(lc(now)),sum(lc(now))+v(now)+ql(rc(now)));
	ql(now)=max(ql(now),sum(lc(now))+v(now));
	qr(now)=max(qr(rc(now)),sum(rc(now))+v(now)+qr(lc(now)));
	qr(now)=max(qr(now),sum(rc(now))+v(now));
	return;
}
void split(int now,int rank,int &x,int &y) //<= >
{
	if(!now) {
		x=y=0;
		return;
	}
	if(s(lc(now))+1<=rank) {
		x=now;
		split(rc(now),rank-s(lc(now))-1,rc(x),y);
	}
	else {
		y=now;
		split(lc(now),rank,x,lc(y));
	}
	update(now);
}
int merge(int x,int y)
{
	if(x==0||y==0) 
		return x+y;
	if(p(x)>p(y)) {
		rc(x)=merge(rc(x),y);
		update(x);
		return x;
	}
	else {
		lc(y)=merge(x,lc(y));
		update(y);
		return y;
	}
}
inline int newnode(const int &key)
{
	++cnt;
	v(cnt)=key;
	s(cnt)=1;
	p(cnt)=rand();
	qm(cnt)=sum(cnt)=ql(cnt)=qr(cnt)=key;
	lc(cnt)=rc(cnt)=0;
	return cnt;
}
inline void insert(const int &pos,const int &key)
{
	int x,y;
	split(root,pos-1,x,y);
	root=merge(merge(x,newnode(key)),y);
	return;
}
inline void erase(const int &pos) 
{
	int x,y,z;
	split(root,pos-1,x,z);
	split(z,1,y,z);
	root=merge(x,z);
	return;
}
inline void edit(const int &pos,const int &key)
{
	int x,y,z;
	split(root,pos-1,x,z);
	split(z,1,y,z);
	v(y)=key;
	sum(y)=qm(y)=ql(y)=qr(y)=key;
	z=merge(y,z);
	root=merge(x,z);
	return;	
}
inline int query(const int &l,const int &r)
{
	int x,y,z;
	split(root,l-1,x,z);
	split(z,r-l+1,y,z);
	int tmp=qm(y);
	z=merge(y,z);
	root=merge(x,z);
	return tmp;
}
int n,m;
int a[N];
int Build(int l,int r)
{
	if(l==r) 
		return newnode(a[l]);
	int x,mid=(l+r)>>1;
	x=merge(Build(l,mid),Build(mid+1,r));
	return x;
}
int main()
{
//	freopen("1.in","r",stdin);
	srand((unsigned)time(0));
	rint i,j;
	int x,y,z;
	char opt;
	read(n);
	for(i=1;i<=n;i++) 
		read(a[i]);
	root=merge(root,Build(1,n));
	read(m);
	while(m--) {
		opt=getchar(); 
		while(opt!='I'&&opt!='D'&&opt!='R'&&opt!='Q') 
			opt=getchar();
		if(opt=='I') {
			read(x); read(y);
			insert(x,y);
		}
		else if(opt=='D') {
			read(x);
			erase(x);
		}
		else if(opt=='R') {
			read(x); read(y);
			edit(x,y);
		}
		else if(opt=='Q') {
			read(x); read(y);
			z=query(x,y);
			print(z),putchar('\n');
		}
	}
	return 0;
}

