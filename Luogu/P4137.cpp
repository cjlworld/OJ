#include<map>
#include<set>
#include<cmath>
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
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
template<class T>
inline void max(const T &x,const T &y)
{
	if(x>y) return x;
	else return y;
}
template<class T>
inline void min(const T &x,const T &y)
{
	if(x>y) return y;
	else return x;
}
template<class T>
inline void swap(T &x,T &y)
{
	T temp=x; x=y; y=temp;
	return;
}
template<class T>
inline T abs(const T &x)
{
	if(x>0) return x;
	else return (-x);
}
LL pow(LL x,int k)
{
	LL res=1;
	while(k) {
		if(k&1) res=res*x;
		x=x*x; k>>=1;
	}
	return res;
}
LL quickpow(LL x,LL k,LL mod)
{
	LL res=1;
	while(k) {
		if(k&1) res=res*x%mod;
		x=x*x%mod; k>>=1;
	}
	return res%mod;
}
}
#define rint register int 
#define read(x) FastIO::read(x) 
#define print(x) FastIO::print(x)
#define min(x,y) FastIO::min(x,y) 
#define max(x,y) FastIO::max(x,y)
#define swap(x,y) FastIO::swap(x,y)
#define abs(x) FastIO::abs(x)
#define pow(x,y) FastIO::pow(x,y)
#define quickpow(x,y,z) FastIO::quickpow(x,y,z)
//======================================================
const int N=2e5+5;
const int SQ=1000;
const int SIZ=448;
int n,m;
int a[N],F[N];
int cnt[N];
int siz;
struct data
{
	int l,r;
	int ans;
	int o;
}q[N];
int num[SQ];
inline bool cmp(const data &a,const data &b)
{
	if((int)(a.l/siz)!=(int)(b.l/siz)) 
		return a.l<b.l;
	else return a.r<b.r;
}
inline bool rule(const data &a,const data &b)
{
	return a.o<b.o;
}
inline void Add(int pos)
{
	if(cnt[a[pos]]==0) 
		num[a[pos]/SIZ+1]++;
	cnt[a[pos]]++;
	return;
}
inline void Sub(int pos)
{
	if(cnt[a[pos]]==1) 
		num[a[pos]/SIZ+1]--;
	cnt[a[pos]]--;
	return;
}
inline int Query()
{
	for(rint i=1;i<=SIZ;i++) {
		if(num[i]==SIZ) continue;
		for(rint j=SIZ*(i-1);j<=SIZ*i-1;j++) 
			if(!cnt[j]) 
				return j;
	}
	return n;
}
int main()
{
	rint i,j;
	int tot=0;
	read(n); read(m);
	siz=sqrt(n);
	for(i=1;i<=n;i++) {
		read(a[i]);
		if(a[i]>n) a[i]=n+1; 
	}
	for(i=1;i<=m;i++) {
		read(q[i].l); read(q[i].r);
		q[i].o=i;
	}
	sort(q+1,q+m+1,cmp);
	rint ql=1,qr=0;
	for(i=1;i<=m;i++) {
		while(qr<q[i].r) Add(++qr);
		while(ql>q[i].l) Add(--ql);
		while(qr>q[i].r) Sub(qr--);
		while(ql<q[i].l) Sub(ql++); 
		q[i].ans=Query();
	}
	sort(q+1,q+m+1,rule);
	for(i=1;i<=m;i++) 
		print(q[i].ans),putchar('\n');
	return 0;
}

