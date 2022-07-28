#include<cmath>
#include<cstdio>
#include<iostream>
#include<algorithm>
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
template<class T>
inline T min(const T &x,const T &y)
{
	if(x>y) return y;
	else return x;
}
template<class T>
inline void swap_num(T &x,T &y)
{
	x^=y^=x^=y;
	return;
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
#define swap_num(x,y) FastIO::swap_num(x,y)
#define abs(x) FastIO::abs(x)
#define pow(x,y) FastIO::pow(x,y)
#define quickpow(x,y,z) FastIO::quickpow(x,y,z)
//==================================================
const int N=133333+5;
const int M=1e6+5;
int n,m;
int a[N];
int c[M];
int ago[N];
int ans=0;
struct quiz
{
	int l,r;
	int ans;
	int o;
	int Tim;
}Q[N],R[N];
int Qtot=0,Rtot=0,siz;
inline bool cmp(const quiz &a,const quiz &b)
{
	if(a.l/siz!=b.l/siz) 
		return a.l<b.l;
	if(a.r/siz!=b.r/siz) 
		return a.r<b.r;
	return a.Tim<b.Tim;	
}
inline bool rule(const quiz &a,const quiz &b)
{
	return a.o<b.o;
}
inline void Add(int pos)
{
	if(c[a[pos]]==0) ans++;
	c[a[pos]]++;
	return;
}
inline void Sub(int pos)
{
	if(c[a[pos]]==1) ans--;
	c[a[pos]]--;
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	char opt;
	read(n); read(m);
	for(i=1;i<=n;i++) 
		read(a[i]);
	for(i=1;i<=n;i++) 
		ago[i]=a[i];
	for(i=1;i<=m;i++) {
		for(opt=getchar();opt!='R'&&opt!='Q';opt=getchar());
		if(opt=='R') {
			Rtot++;
			read(R[Rtot].l); read(R[Rtot].r);
			R[Rtot].Tim=ago[R[Rtot].l];
			R[Rtot].o=i;
			ago[R[Rtot].l]=R[Rtot].r;
		}
		else {
			Qtot++;
			read(Q[Qtot].l); read(Q[Qtot].r);
			if(Q[Qtot].l>Q[Qtot].r) 
				swap(Q[Qtot].l,Q[Qtot].r);
			Q[Qtot].Tim=Rtot;
			Q[Qtot].o=i;
		}
	}
	siz=pow(N,0.6666666666);;
	sort(Q+1,Q+Qtot+1,cmp);
	int head=1,tail=0,times=0;
	for(i=1;i<=Qtot;i++) {
		while(times<Q[i].Tim) {
			times++;
			if(R[times].l>=head&&R[times].l<=tail) {
				Sub(R[times].l);
				a[R[times].l]=R[times].r;
				Add(R[times].l);
			}
			else a[R[times].l]=R[times].r;
		}
		while(times>Q[i].Tim) {
			if(R[times].l>=head&&R[times].l<=tail) {
				Sub(R[times].l);
				a[R[times].l]=R[times].Tim;
				Add(R[times].l);
			}
			else a[R[times].l]=R[times].Tim;
			times--;
		}
		while(head>Q[i].l) Add(--head);
		while(tail<Q[i].r) Add(++tail);
		while(head<Q[i].l) Sub(head++);
		while(tail>Q[i].r) Sub(tail--);
		Q[i].ans=ans;
	}
	sort(Q+1,Q+Qtot+1,rule);
	for(i=1;i<=Qtot;i++) 
		print(Q[i].ans),putchar('\n');
	return 0;
}

