#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

LL quickpow(LL x,LL k,LL MOD)
{
	LL res=1; x%=MOD;
	while(k) {
		if(k&1) res=res*x%MOD;
		x=x*x%MOD; k>>=1;
	}
	return res;
}

LL C(LL a,LL b,LL MOD)
{
	if(b>a) return 0;
	LL res=1;
	for(LL i=1,j=a;i<=b;i++,j--) {
		res=res*j%MOD;
		res=res*quickpow(i,MOD-2,MOD)%MOD;
	}
	return res%MOD;
}

LL lucas(LL a,LL b,LL MOD)
{
	if(a<MOD && b<MOD) return C(a,b,MOD);
	return C(a%MOD,b%MOD,MOD)*lucas(a/MOD,b/MOD,MOD)%MOD;
}
LL a,b,p;
int main()
{
//	freopen("1.in","r",stdin);
	int T;
	cin>>T;
	while(T--) {
		cin>>a>>b>>p;
		cout<<lucas(a,b,p)<<endl;
	}
	return 0;
}
//	prime((int)1e6)
//const int N=1e6+5;
//int p[N],tot=0;
//bool tag[N];
//void prime(int n)
//{
//	LL i,j;
//	for(i=2;i<=n;i++) {
//		if(tag[i]) continue;
//		p[++tot]=i;
//		for(j=i*i;j<=n;j+=i) 
//			tag[j]=true;
//	}
//	return;
//}
//
//LL MOD;
//LL a,b;
//LL tim[N];
//void divide(LL n,LL k) // divide the primes from n!
//{
//	LL i,j;
//	for(i=1;i<=tot;i++) 
//		for(j=p[i];j<=n;j*=p[i]) 
//			tim[i]+=n/j*k;
//	return;
//}
