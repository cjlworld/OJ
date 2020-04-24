#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL b,p,k;
LL power(LL n,LL m,LL k)
{
	LL res=1;
	while(m) {
		if(m&1) res=(res*n)%k;
		n=n*n%k; m>>=1;
	}
	return res%k;
}
int main()
{
	scanf("%lld%lld%lld",&b,&p,&k);
	printf("%lld^%lld mod %lld=%lld\n",b,p,k,power(b,p,k));
	return 0;
}

