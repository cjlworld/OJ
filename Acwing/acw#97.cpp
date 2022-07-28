#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=1e5+5;
const LL MOD=9901; // 9901 是质数 

LL a,b;
LL p[N],c[N],tot=0;

LL fpow(LL x,LL k,LL MOD)
{
	LL res=1; x%=MOD;
	while(k) {
		if(k&1) res=res*x%MOD;
		x=x*x%MOD; k>>=1;
	}
	return res%MOD;
}

LL fsum(LL x,LL k)
{
	// 求解 x^1+x^2+x^3+x^4+...+x^k; 
	if(k==0) return 0;
	LL res=0;
	if(k&1) res+=fpow(x,k,MOD),k--;
	res=(res+fsum(x,k/2)*(fpow(x,k/2,MOD)+1)%MOD)%MOD;
	return res;
}

int main()
{
//	freopen("1.in","r",stdin);	
	LL i;
	scanf("%lld%lld",&a,&b);
	if(a==0) { printf("0\n"); return 0; }
	for(i=2;i*i<=a;i++) {
		if(a%i==0) {
			p[++tot]=i;
			while(a%i==0) a/=i,c[tot]++;
		}
	}
	if(a>1) p[++tot]=a,c[tot]=1;
	
	LL ans=1;
	for(i=1;i<=tot;i++) 
		ans=ans*(1+fsum(p[i],c[i]*b))%MOD;
	cout<<ans;
	return 0;
}

