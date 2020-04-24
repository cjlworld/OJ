#include<cmath>
#include<cstdio>
#include<iostream>
#include<algorithm>
#define LL long long
using namespace std;
template<class T>
inline void read(T &x)
{
	x=0;
	bool sign=false;
	char c;
	for(c=getchar();c<'0'||c>'9';c=getchar()) 
		if(c=='-') 
			sign=true;
	for(;c>='0'&&c<='9';c=getchar()) 
		x=(x<<1)+(x<<3)+(c-'0');
	x=(sign) ? ~x+1 : x;
	return;
}
//==========================
const int N=5e4+5;
int n,m;
struct quiz
{
	int l,r;
	LL ans;
	int o;
}q[N];
int siz;
inline bool cmp(const quiz &a,const quiz &b)
{
	if(a.l/siz!=b.l/siz) 
		return a.l<b.l;
	return (a.r<b.r)^(a.l/siz&1);
}
inline bool rule(const quiz &a,const quiz &b)
{
	return a.o<b.o;
}
LL a[N];
LL ans=0ll;
int c[N];
inline void Add(const int &pos)
{
	ans+=c[a[pos]]*1ll;
	c[a[pos]]++;
	return;
}
inline void Sub(const int &pos)
{
	ans-=(c[a[pos]]-1)*1ll;
	c[a[pos]]--;
	return;
}
inline LL gcd(const LL &x,const LL &y)
{
	if(y==0ll) 
		return x;
	return gcd(y,x%y);
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y;
	LL z,tmp;
	read(n); read(m);
	for(i=1;i<=n;i++) 
		read(a[i]);
	for(i=1;i<=m;i++) {
		read(q[i].l); read(q[i].r);
		q[i].o=i;
	}
	siz=sqrt(n);
	sort(q+1,q+m+1,cmp);
	int head=1,tail=0;
	for(i=1;i<=m;i++) {
		while(head>q[i].l) Add(--head);
		while(tail<q[i].r) Add(++tail);
		while(head<q[i].l) Sub(head++);
		while(tail>q[i].r) Sub(tail--);
		q[i].ans=ans;
	}
	sort(q+1,q+m+1,rule);
	for(i=1;i<=m;i++) {
		if(q[i].ans==0ll) {
			printf("0/1\n");
			continue;
		}
		z=(LL)(q[i].r*1ll-q[i].l*1ll+1ll);
		z=z*(z-1);
		q[i].ans=q[i].ans*2ll;
		tmp=gcd(z,q[i].ans);
		z=z/tmp;
		q[i].ans=q[i].ans/tmp;
		printf("%lld/%lld\n",q[i].ans,z);
	}
	return 0;
}

