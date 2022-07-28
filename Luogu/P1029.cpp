#include<bits/stdc++.h>
#define LL long long 
using namespace std;
const int N=1e5+5;
LL A,B,C;
LL gcd(LL a,LL b)
{
	if(b==0) 
		return a;
	return gcd(b,a%b);
}
LL lcm(LL a,LL b)
{
	return (a*b/gcd(a,b));
}
int cnt=0;
int main()
{
	scanf("%lld%lld",&A,&B);
	C=A*B;
	LL i,j;
	for(i=A;i<=B;i+=A) 
	{
		if(C%i==0)
			j=C/i;
		else continue;
		if(gcd(i,j)==A) {
			cnt++;
		}
	}
	cout<<cnt;
}
