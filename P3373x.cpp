#include<set>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
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
template<class T>
void print(T x)
{
	if(x<0) x=~x+1,putchar('-');
	if(x>9) print(x/10);
	putchar(x%10+48);
	return;
}
}
#define rint register int 
#define read(x) FastIO::read(x) 
#define print(x) FastIO::print(x)
//=================================
const int N=1e5+5;
const int SQ=1000;
LL MOD;
LL a[N];
int n,m;
struct node
{
	int l,r;
	LL mul,add;
	LL sum;
	#define l(x) t[x].l
	#define r(x) t[x].r
	#define mul(x) t[x].mul
	#define add(x) t[x].add
	#define sum(x) t[x].sum
};
#define lc (now<<1)
#define rc (now<<1|1)
node t[4*N];
inline void push_up(const int &now)
{
	sum(now)=sum(lc)+sum(rc);
	sum(now)=sum(now)%MOD;
	return;
}
void Build(int now,int l,int r)
{
	l(now)=l;
	r(now)=r;
	mul(now)=1ll;
	add(now)=0ll;
	if(l==r) {
		sum(now)=a[l];
		return;
	}
	int mid=(l+r)>>1;
	Build(lc,l,mid);
	Build(rc,mid+1,r);
	push_up(now);
	return;
}
inline void push_down(int now)
{
	if(l(now)==r(now))
		return;
	if(add(now)==0ll&&mul(now)==1ll) 
		return;
	sum(lc)=(sum(lc)*mul(now)%MOD+add(now)*(r(lc)-l(lc)+1)%MOD)%MOD;
	sum(rc)=(sum(rc)*mul(now)%MOD+add(now)*(r(rc)-l(rc)+1)%MOD)%MOD;
	add(lc)=(add(lc)*mul(now)%MOD+add(now))%MOD;
	add(rc)=(add(rc)*mul(now)%MOD+add(now))%MOD;
	mul(lc)=mul(lc)*mul(now)%MOD;
	mul(rc)=mul(rc)*mul(now)%MOD;
	mul(now)=1ll;
	add(now)=0ll;
	return;
}
void multiply(int now,const int &x,const int &y,const LL &z)
{
	if(r(now)<x||l(now)>y)
		return;
	if(l(now)>=x&&r(now)<=y) {
		sum(now)=sum(now)*z%MOD;
		add(now)=(add(now)*z)%MOD;
		mul(now)=mul(now)*z%MOD;
		return;
	}
	push_down(now);
	multiply(lc,x,y,z);
	multiply(rc,x,y,z);
	push_up(now);
	return;
}
void modify(int now,const int &x,const int &y,const int &z)
{
	if(r(now)<x||l(now)>y)
		return;
	if(l(now)>=x&&r(now)<=y) {
		sum(now)=(sum(now)+(r(now)-l(now)+1)*z%MOD)%MOD;
		add(now)=(add(now)+z)%MOD;
		return;
	}
	push_down(now);
	modify(lc,x,y,z);
	modify(rc,x,y,z);
	push_up(now);
	return;
}
LL query(int now,const int &x,const int &y)
{
	if(r(now)<x||l(now)>y)
		return 0ll;
	if(l(now)>=x&&r(now)<=y) 
		return sum(now);
	push_down(now);
	LL res=0;
	res=(res+query(lc,x,y))%MOD;
	res=(res+query(rc,x,y))%MOD;
	return res%MOD;
}
int main()
{
//	freopen("1.in","r",stdin);
    rint i,j;
    int opt,x,y;
    LL z;
    read(n); read(m); read(MOD);
    for(i=1;i<=n;i++) {
        read(a[i]);
        a[i]=a[i]%MOD;
    }
    Build(1,1,n);    
    for(i=1;i<=m;i++) {
        read(opt); read(x); read(y);
        if(opt==1) {
        	read(z);
        	multiply(1,x,y,z);
		}
		else if(opt==2) {
			read(z);
			modify(1,x,y,z);
		}
        else if(opt==3) print(query(1,x,y)),putchar('\n');
    }
    return 0;
}
