#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;
typedef unsigned long long LL;
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
#define enter FastIO::putc('\n')

const int N=50000+5;
const LL MOD=1e9+7,Limit=MOD*MOD*10;

void Fot(LL a[],LL b[],LL c[],rint n,rLL MOD)
{
	static LL C[N];
	for(rint i=0;i<=n;i++) {
		C[i]=0;
		for(rint j=0;j<=i;j++) 
			(C[i]+=a[j]*b[i-j])>=Limit && (C[i]%=MOD);
		C[i]%=MOD;
	}
	memcpy(c,C,sizeof(LL)*(n+2));
}

int n,k;
LL a[N],g[N];

int main()
{
	rint i;
	read(n); read(k);
	for(i=1;i<=n;i++) read(a[i]);
	for(i=0;i<=n;i++) g[i]=1;
	
	while(k) {
		if(k&1) Fot(a,g,a,n,MOD);
		Fot(g,g,g,n,MOD); k>>=1;
	}
	
	for(i=1;i<=n;i++) print(a[i]),enter;
	return 0;
}

