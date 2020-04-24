#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
#define int LL 
inline void read(LL &x)
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
inline void print(LL x)
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
inline LL max(const LL &x,const LL &y)
{
	if(x>y) return x;
	else return y;
}
inline void swap(LL &x,LL &y)
{
	x^=y^=x^=y;
	return;
}
const LL INF=1e17;
const int N=1000000+5;
struct node
{
	int lc,rc;
	LL val;
	int size;
	bool reverse;
	LL tag;
	LL sum,qm,ql,qr;
	int pri;
	#define lc(x) t[x].lc
	#define rc(x) t[x].rc
	#define v(x) t[x].val
	#define s(x) t[x].size
	#define rv(x) t[x].reverse
	#define tag(x) t[x].tag
	#define sum(x) t[x].sum
	#define qm(x) t[x].qm
	#define ql(x) t[x].ql
	#define qr(x) t[x].qr
	#define pri(x) t[x].pri
};
node t[N];
int root=0,cnt=0;
int Qdel[N],len=0;
LL a[N];
inline void update(const int &x)
{
	s(x)=s(lc(x))+s(rc(x))+1;
	sum(x)=sum(lc(x))+sum(rc(x))+v(x);
	qm(x)=max(qr(lc(x))+v(x),ql(rc(x))+v(x));
	if(lc(x)) qm(x)=max(qm(x),qm(lc(x)));
	if(rc(x)) qm(x)=max(qm(x),qm(rc(x)));
	qm(x)=max(qm(x),qr(lc(x))+v(x)+ql(rc(x)));
	qm(x)=max(qm(x),v(x));
	ql(x)=max(ql(lc(x)),sum(lc(x))+v(x));
	ql(x)=max(ql(x),sum(lc(x))+v(x)+ql(rc(x)));
	qr(x)=max(qr(rc(x)),sum(rc(x))+v(x));
	qr(x)=max(qr(x),qr(lc(x))+sum(rc(x))+v(x));
	return;
}
inline void Addtag(const int &now,const LL &key)
{
	if(!now) return;
	rv(now)=false;
	v(now)=key;
	tag(now)=key;
	sum(now)=key*s(now);
	if(tag(now)>=0) qr(now)=ql(now)=qm(now)=sum(now);
	else qr(now)=ql(now)=qm(now)=key;		
	return;
}
inline void Addreverse(const int &now)
{
	if(!now||tag(now)!=INF) return;
	rv(now)^=1;
	swap(ql(now),qr(now));
	swap(lc(now),rc(now));
	return;
}
inline void push_down(const int &now)
{
	if(!now) return;
	if((!lc(now))&&(!rc(now))) {
		rv(now)=false;
		tag(now)=INF;
		return;
	}
	if(tag(now)!=INF) rv(now)=false; 
	if(rv(now)) {
		if(lc(now)) Addreverse(lc(now));
		if(rc(now)) Addreverse(rc(now));
		rv(now)=false;
	}
	if(tag(now)!=INF) {
		if(lc(now)) Addtag(lc(now),tag(now));
		if(rc(now)) Addtag(rc(now),tag(now));
		tag(now)=INF;
	}
	return;
}
inline int newnode(const LL &key)
{
	int now;
	if(len>=1) now=Qdel[len--];
	else now=++cnt;
	lc(now)=rc(now)=0;
	s(now)=1;
	rv(now)=false;
	tag(now)=0;
	pri(now)=rand();
	qm(now)=qr(now)=ql(now)=sum(now)=v(now)=key;
	return now;
}
void split(int now,int rank,int &x,int &y) //<= >
{
	if(!now) { 
		x=y=0;
		return;
	}
	push_down(now);
	if(s(lc(now))+1<=rank) {
		x=now;
		split(rc(now),rank-s(lc(now))-1,rc(now),y);
	}
	else {
		y=now;
		split(lc(now),rank,x,lc(y));
	}
	update(now);
	return;
}
int merge(int x,int y) //x<=y
{
	if(x==0||y==0) 
		return x+y;
	if(pri(x)>pri(y)) {
		push_down(x);
		rc(x)=merge(rc(x),y);
		update(x);
		return x;
	}
	else {
		push_down(y);
		lc(y)=merge(x,lc(y));
		update(y);
		return y;
	}
}
int Build(int l,int r)
{
	if(l==r)	
		return newnode(a[l]);
	int x,mid=(l+r)>>1;
	x=merge(Build(l,mid),Build(mid+1,r));
	return x;
}
void recycle(int now)
{
	if(!now) 
		return;
	Qdel[++len]=now;
	recycle(rc(now));
	recycle(lc(now));
	return;
}
char opt[10];
int n,m;
#define rint register int 
signed main()
{
//	freopen("1.in","r",stdin);
	srand(20040524);
	rint i;
	LL x,y,z,pos,tot,val;
	read(n); read(m);
	for(i=1;i<=n;i++) 
		read(a[i]);
	root=Build(1,n);
	qm(0)=-INF;
	while(m--) {
		scanf("%s",opt+1);
		x=y=z=0;
		if(opt[1]=='I') {
			read(pos); read(tot);
			for(i=1;i<=tot;i++)
				read(a[i]);
			split(root,pos,x,z);
			root=merge(merge(x,Build(1,tot)),z);
		}
		else if(opt[1]=='D') {
			read(pos); read(tot);
			split(root,pos-1,x,z);
			split(z,tot,y,z);
			recycle(y);
			root=merge(x,z);
		}
		else if(opt[1]=='M'&&opt[3]=='K') {
			read(pos); read(tot); read(val);
			split(root,pos-1,x,z);
			split(z,tot,y,z);
			Addtag(y,val);
			z=merge(y,z);
			root=merge(x,z);
		}
		else if(opt[1]=='R') {
			read(pos); read(tot);
			split(root,pos-1,x,z);
			split(z,tot,y,z);
			Addreverse(y);
			z=merge(y,z);
			root=merge(x,z);
		}
		else if(opt[1]=='G'&&strlen(opt+1)==7) {
			read(pos); read(tot);
			split(root,pos-1,x,z);
			split(z,tot,y,z);
			print(sum(y)); putchar('\n');
			z=merge(y,z);
			root=merge(x,z);
		}
		else if(opt[1]=='G') {
			read(pos);
			split(root,pos-1,x,z);
			split(z,1,y,z);
			print(v(y)); putchar('\n');
			z=merge(y,z);
			root=merge(x,z);
		}
		else {
			read(pos); read(tot);
			split(root,pos-1,x,z);
			split(z,tot,y,z);
			print(qm(y)),putchar('\n');
			z=merge(y,z);
			root=merge(x,z);
		}
	}
	return 0;
}
