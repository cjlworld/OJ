#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<iostream>

using namespace std;
typedef long long LL;

template<class T>
inline T mabs(T x) { return ((x<0) ? -x : x); }

LL gcd(LL a,LL b)
{
	if(b==0) return a;
	else return gcd(b,a%b);
}

LL muler(LL x,LL y,LL MOD)
{
	LL high=(long double)x/MOD*y;
	LL low=x*y-high*MOD;
	return (low%MOD+MOD)%MOD;
}

LL power(LL x,LL k,LL MOD)
{
	LL res=1; x%=MOD;
	while(k) {
		if(k&1) res=muler(res,x,MOD);
		x=muler(x,x,MOD); k>>=1;
	}
	return res%MOD;
}

bool Witness(LL x,LL k,LL MOD)
{
	LL p=power(x,k,MOD);
	if(p!=1 && p!=MOD-1) return false;
	else if(p==MOD-1 || (k&1)) return true;
	else return Witness(x,k>>1,MOD);
}

bool Miller_Rabin(LL n)
{
	static const int pcnt=8;
	static const int p[]={2,3,5,7,11,13,17,24251};
	
	if(n<=1) return false; 
	for(int i=0;i<pcnt;i++) {
		if(n%p[i]==0) return (p[i]==n);
		else if(!Witness(p[i],n-1,n)) return false;
	}
	for(int i=0;i<pcnt;i++) 
		if(!Witness(rand()%(n-2)+2,n-1,n)) return false;
	return true;
}

LL Pollard_Rho(LL n)
{
	LL c=rand()%(n-1)+1;
	LL tur=rand()%(n-1)+1,rab=(muler(tur,tur,n)+c)%n;
		// 一定要另外随一个 x0 , 开始，不能直接从 0 开始。 
	LL val=1,d;
	for(int i=0;tur!=rab;i++) {
		val=muler(val,mabs(rab-tur),n);
		if(i%127==0 && (d=gcd(val,n))>1) 
			return d;
		// turtle 走一步，rabbit 走两步。 
		tur=(muler(tur,tur,n)+c)%n;
		rab=(muler(rab,rab,n)+c)%n; rab=(muler(rab,rab,n)+c)%n;
	}
	if((d=gcd(val,n))>1) return d;
	else return Pollard_Rho(n); // 下一次调整。 
}

LL ans;
void fac(LL n)
{
	if(n<=ans || n<=1) return;
	if(Miller_Rabin(n)) {
		ans=max(ans,n);
		return;
	}
	LL p=Pollard_Rho(n);
	while(n%p==0) n/=p;
	fac(n); fac(p);
}

int T;
LL n;

int main()
{
	srand(time(0));
	cin>>T;
	while(T--) {
		cin>>n;
		ans=0,fac(n);
		if(ans==n) puts("Prime");
		else printf("%lld\n",ans);
	}
	return 0;
}

