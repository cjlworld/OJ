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

const int N=25;
const LL MOD=1e9+7;

int n;
LL m,a[N];

LL fpow(LL x,LL k,LL MOD)
{
	LL res=1; x%=MOD;
	while(k) {
		if(k&1) res=res*x%MOD;
		x=x*x%MOD; k>>=1;
	}
	return res%MOD;
}

LL down=1;

LL C(LL a)
{
	if(a<n-1) return 0;
	LL res=down;
	for(LL i=a;i>a-(n-1);i--) res=i%MOD*res%MOD;
	return res;
}


int main()
{
//	freopen("1.in","r",stdin);
	
	int i,j;
	LL x,sign;
	cin>>n>>m;
	for(i=1;i<=n;i++) cin>>a[i];
	for(i=1;i<=n-1;i++) down=down*(LL)i%MOD;
	down=fpow(down,MOD-2,MOD);
	const int S=(1<<n);
	LL ans=0;
	for(i=0;i<S;i++) {
		sign=1, x=m+n-1;
		for(j=0;(i>>j);j++) 
			if((i>>j)&1) 
				sign*=-1,x-=(a[j+1]+1);
		ans=(ans+sign*C(x))%MOD;
	}
	cout<<(ans+MOD)%MOD;
	return 0;
}

