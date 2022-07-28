#include<cmath>
#include<ctime>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

template<class T>
inline T mabs(T x) { return ((x>0) ? x : -x); } 

LL muler(LL x,LL y,LL MOD)
{
	LL high=(long double)x/MOD*y;
	LL low=(LL)((ULL)x*y-(ULL)high*MOD);
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

LL gcd(LL a,LL b)
{
	if(b==0) return a;
	else return gcd(b,a%b);
}

LL exgcd(LL a,LL b,LL& x,LL& y)
{
	if(b==0) {
		x=1; y=0;
		return a;
	}
	LL z=exgcd(b,a%b,y,x);
	y-=(a/b)*x;
	return z;
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
	static const int p[]={2,3,5,7,11,13,61,24251};
	
	if(n<=1) return false;
	for(int i=0;i<pcnt;i++) {
		if(n%p[i]==0) return (n==p[i]);
		else if(!Witness(p[i],n-1,n)) return false;
	}
	for(int i=0;i<pcnt;i++) 
		if(!Witness(rand()%(n-2)+2,n-1,n)) return false;
	return true;
}

vector<LL> v;
LL Pollard_Rho(LL n)
{
	LL c=rand()%(n-1)+1;
	LL t=rand()%(n-1)+1,r=(muler(t,t,n)+c)%n;
	LL val=1,d;
	for(int i=0;t!=r;i++) {
		val=muler(val,mabs(r-t),n);
		if(i%127==0 && (d=gcd(val,n))>1) 
			return d;
		t=(muler(t,t,n)+c)%n;
		r=(muler(r,r,n)+c)%n; r=(muler(r,r,n)+c)%n;
	}	
	if((d=gcd(val,n))>1) return d;
	else return Pollard_Rho(n);
}

void fac(LL n,vector<LL>& v)
{
	if(n<=1) return;
	if(Miller_Rabin(n)) {
		v.push_back(n);
		return;
	}
	LL p=Pollard_Rho(n);
	fac(n/p,v); fac(p,v);
}

LL e,N,c,d,n,r;

int main()
{
//	freopen("1.in","r",stdin);
	srand(time(0));
	LL y;
	
	cin>>e>>N>>c;
	fac(N,v);
	r=(v[0]-1)*(v[1]-1);
	exgcd(e,r,d,y);
	d=(d%r+r)%r;
	n=power(c,d,N);
	cout<<d<<" "<<n<<endl;
	return 0;
}

