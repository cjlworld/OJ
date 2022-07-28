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
//=================================
const int N=2e5+5;
const int SQ=2000;
LL MOD;
LL a[N];
int n,m;
struct block
{
    int siz,k;
    int L[SQ],R[SQ],F[N];
    LL atag[SQ],mtag[SQ];
    LL sum[SQ];
    inline void Build()
    {
        memset(L,0,sizeof L);
        memset(R,0,sizeof R);
        memset(F,0,sizeof F);
        memset(atag,0,sizeof atag);
        memset(sum,0,sizeof sum);
        fill(mtag,mtag+SQ-5,1ll);
        rint i,j;
        if(n>25) siz=sqrt(n)/4;
		else siz=sqrt(n);       
        k=n/siz+(n%siz>0);
        for(i=1;i<=k;i++) {
            L[i]=R[i-1]+1;
            R[i]=i*siz;
        }
        R[k]=n;
        for(i=1;i<=k;i++) 
            for(j=L[i];j<=R[i];j++) 
                F[j]=i,sum[i]=(sum[i]+a[j])%MOD;
        return;
    }
    inline void push_down(int now)
    {
        rint i,j;
        sum[now]=((sum[now]*mtag[now])%MOD+(R[now]-L[now]+1)*atag[now]%MOD)%MOD;
        for(i=L[now];i<=R[now];i++)
            a[i]=(a[i]*mtag[now]%MOD+atag[now])%MOD;
        mtag[now]=1ll;
        atag[now]=0ll;
        return;
    }
    inline void modify(int x,int y,LL z) //first ? second ?
    {
        rint i,j;
        if(F[x]==F[y]) {
            push_down(F[x]);
            sum[F[x]]=(sum[F[x]]+(y-x+1)*z%MOD)%MOD;
            for(i=x;i<=y;i++) 
                a[i]=(a[i]+z)%MOD;
            return;
        }
        push_down(F[x]);
        sum[F[x]]=(sum[F[x]]+(R[F[x]]-x+1)*z%MOD)%MOD;
        for(i=x;i<=R[F[x]];i++)
            a[i]=(a[i]+z)%MOD;
        for(i=F[x]+1;i<=F[y]-1;i++) 
            atag[i]=(atag[i]+z)%MOD;
        push_down(F[y]);
        sum[F[y]]=(sum[F[y]]+(y-L[F[y]]+1)*z%MOD)%MOD;
        for(i=L[F[y]];i<=y;i++)
            a[i]=(a[i]+z)%MOD;
        return;
    }
    inline void multiply(int x,int y,LL z)
    {
        rint i,j;
        if(F[x]==F[y]) {
            push_down(F[x]);
            for(i=x;i<=y;i++) {
            	sum[F[x]]=(sum[F[x]]+a[i]*(z-1)%MOD)%MOD;
            	a[i]=(a[i]*z)%MOD;
			}
            return;
        }
        push_down(F[x]);
        for(i=x;i<=R[F[x]];i++) {
        	sum[F[x]]=(sum[F[x]]+a[i]*(z-1)%MOD)%MOD;
        	a[i]=(a[i]*z)%MOD;    	
		}     
        for(i=F[x]+1;i<=F[y]-1;i++) {
            mtag[i]=(mtag[i]*z)%MOD;
            if(atag[i]!=0ll)
      	      atag[i]=(atag[i]*z)%MOD;
        }
        push_down(F[y]);
        for(i=L[F[y]];i<=y;i++) {
        	sum[F[y]]=(sum[F[y]]+a[i]*(z-1)%MOD)%MOD;
        	a[i]=(a[i]*z)%MOD;
		}           
        return;
    }
    inline LL want(int x)
    {
        return (a[x]*mtag[F[x]]%MOD+atag[F[x]])%MOD;
    }
    inline LL query(int x,int y)
    {
    	rint i,j;
    	LL res=0;
    	if(F[x]==F[y]) {
    		for(i=x;i<=y;i++) 
    			res=(res+a[i]*mtag[F[x]]%MOD+atag[F[x]])%MOD;
			return res; 
		}
		for(i=x;i<=R[F[x]];i++) 
			res=(res+a[i]*mtag[F[x]]%MOD+atag[F[x]])%MOD;
		for(i=F[x]+1;i<=F[y]-1;i++) 
			res=(res+sum[i]*mtag[i]%MOD+(R[i]-L[i]+1)*atag[i]%MOD)%MOD;
		for(i=L[F[y]];i<=y;i++) 
			res=(res+a[i]*mtag[F[y]]%MOD+atag[F[y]])%MOD;
		return res%MOD;
	}
}B;
int main()
{
    rint i,j;
    int opt,x,y;
    LL z;
    LL ans;
    read(n); read(MOD);
    for(i=1;i<=n;i++) {
        read(a[i]);
        a[i]=a[i]%MOD;
    }
    B.Build();
    read(m);
    for(i=1;i<=m;i++) {
        read(opt); read(x); read(y);
        if(opt==1) {
        	read(z);
        	z=z%MOD;
        	B.multiply(x,y,z);
		}
		else if(opt==2) {
			read(z);
			z=z%MOD;
			B.modify(x,y,z);
		}
        else if(opt==3) {
        	ans=B.query(x,y);
        	if(ans<0) ans+=MOD;
        	print(ans),putchar('\n');
		}
    }
    return 0;
}

