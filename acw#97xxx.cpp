#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
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
const LL MOD=9901; // 9901 ÊÇÖÊÊý 

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
	for(i=1;i<=tot;i++) {
		if(p[i]%MOD==1) ans=ans*(c[i]*b+1)%MOD;
		else ans=ans*(fpow(p[i],(c[i]*b)+1,MOD)-1)%MOD*fpow(p[i]-1,MOD-2,MOD)%MOD;
	}

	cout<<(ans+MOD)%MOD;
	return 0;
}

