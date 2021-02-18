#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<iostream>

using namespace std;
typedef long long LL;

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
	else if(p==MOD-1 || (p==1 && (k&1))) return true;
	else return Witness(x,k>>1,MOD);
}

bool Miller_Rabin(LL n)
{
	static const int pcnt=7;
	static const LL p[]={2,3,5,7,11,61,24251};
	
	if(n<=1) return false;
	for(int i=0;i<pcnt;i++) {
		if(n%p[i]==0) return (n==p[i]);
		if(!Witness(p[i],n-1,n)) return false;
	}
	
	for(int i=0;i<pcnt;i++) 
		if(!Witness(rand()%(n-2)+2,n-1,n)) return false;
	return true;
}

int main()
{
//	freopen("1.in","r",stdin);
	srand(time(0));
	LL n;
	while(scanf("%lld",&n)==1) {
		if(Miller_Rabin(n)) puts("Y");
		else puts("N");
	}
	return 0;
}

