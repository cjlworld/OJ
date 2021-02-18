#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
#define rint int 
#define rLL LL

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
using FastIO::putc;
#define enter FastIO::putc('\n')

const int N=4e5+5;
const LL Ps[]={998244353,469762049,1004535809},G=3,MOD=1e9+7;

inline LL muler(rLL x,rLL y,rLL MOD)
{
	x%=MOD; y%=MOD;
	if(MOD<=Ps[2]) return (x*y%MOD+MOD)%MOD;;
	LL high=(long double)x/MOD*y;
	LL low=x*y-high*MOD;
	return (low%MOD+MOD)%MOD;
}

inline LL power(rLL x,rLL k,rLL MOD)
{
	rLL res=1; x%=MOD;
	while(k) {
		if(k&1) res=res*x%MOD;
		x=x*x%MOD; k>>=1;
	}
	return res%MOD;
}

int rev[N];
void ntt(LL a[],int n,rLL inv,rLL P)
{
	rint i,j,k,m;
	rLL gn,g,u,v,invn;
	
	for(i=0;i<n;i++) 
		if(rev[i]<i) swap(a[rev[i]],a[i]);
	for(k=2,m=1;k<=n;m=k,k<<=1) {
		gn=power(G,(P-1)/k,P);
		if(inv==-1) gn=power(gn,P-2,P);
		for(i=0;i<n;i+=k) 
			for(j=0,g=1;j<m;j++,(g*=gn)>=P && (g%=P)) {
				u=a[i+j],v=a[i+j+m]*g;
				a[i+j]=u+v; a[i+j+m]=u-v;
			}

		for(i=0;i<n;i++) a[i]=(a[i]%P+P);
	}
	if(~inv) return;
	invn=power(n,P-2,P);
	for(i=0;i<n;i++) a[i]=(a[i]*invn)%P;
}

void TMntt(LL a[],LL b[],LL c[],rint n,rLL MOD)
{
	static LL A[N],B[N],E[N],F[N],Ans[3][N];
	static const LL Inv0=power(Ps[1],Ps[0]-2,Ps[0]),Inv1=power(Ps[0],Ps[1]-2,Ps[1]);
	static const LL M=Ps[0]*Ps[1],InvM=power(M,Ps[2]-2,Ps[2]);

	rint bit=0,lim,i,j;
	while((1<<bit)<=n+n) bit++;
	lim=(1<<bit);
	
	for(i=0;i<lim;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
	
	for(i=0;i<n;i++) A[i]=a[i],B[i]=b[i];
	for(i=n;i<lim;i++) A[i]=0,B[i]=0;
	
	for(j=0;j<3;j++) {
		for(i=0;i<lim;i++) E[i]=A[i]%Ps[j],F[i]=B[i]%Ps[j];
		ntt(E,lim,1,Ps[j]); ntt(F,lim,1,Ps[j]);
		for(i=0;i<lim;i++) Ans[j][i]=(E[i]*F[i])%Ps[j];
		ntt(Ans[j],lim,-1,Ps[j]);
	}
	
	rLL x,y;
	for(i=0;i<lim;i++) {
		x=(muler(Ans[0][i]*Ps[1],Inv0,M)+muler(Ans[1][i]*Ps[0],Inv1,M))%M;
		y=muler(Ans[2][i]-x,InvM,Ps[2]);
		c[i]=(muler(y,M,MOD)+x)%MOD;
	}
}

void Polyinv(LL a[],LL b[],rint n)
{
	static LL E[N];
	if(n==1) 
		return b[0]=power(a[0],MOD-2,MOD),void();

	Polyinv(a,b,(n+1)>>1);
	TMntt(a,b,E,n,MOD);
	TMntt(E,b,E,n,MOD);
	for(rint i=0;i<n;i++) b[i]=((2*b[i]-E[i])%MOD+MOD)%MOD;
}

int n;
LL a[N],b[N];
int main()
{
	rint i;
	read(n);
	for(i=0;i<n;i++) read(a[i]);
	Polyinv(a,b,n);
	for(i=0;i<n;i++) print(b[i]),putc(' ');
	enter;
	return 0;
}
