#include<map>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;

const LL N=5e6+5,MOD=1e9+7;

inline LL sqr(LL n) { return n*n%MOD; }
inline LL idsum(LL n) { return n*(n+1)/2%MOD; }

LL p[N],tot;
bool tag[N];
LL miu[N];
void prime(LL n)
{
	LL i,j;
	miu[1]=1;
	for(i=2;i<=n;i++) {
		if(!tag[i]) p[++tot]=i,miu[i]=-1;
		for(j=1;j<=tot && i*p[j]<=n;j++) {
			tag[i*p[j]]=true;
			if(i%p[j]==0) break;
			miu[i*p[j]]=-miu[i];
		}
	}
	for(i=1;i<=n;i++) miu[i]=((i*miu[i]%MOD+miu[i-1])%MOD+MOD)%MOD;
}

LL Sieve(LL n)
{
	static map<LL,LL> sums;
	
	if(n<N) return miu[n];
	if(sums.count(n)) return sums[n];
	
	LL res=1;
	for(LL i=2,j,t;i<=n;i=j+1) {
		t=n/i; j=n/t;
		res=(res-(idsum(j)-idsum(i-1))%MOD*Sieve(t)%MOD+MOD)%MOD;
	}
	res=(res+MOD)%MOD;
	return sums[n]=res;
}

LL f(LL n)
{
	LL res=0;
	for(LL i=1,j,t;i<=n;i=j+1) {
		t=n/i; j=n/t;
		res=(res+(idsum(j)-idsum(i-1))%MOD*t%MOD)%MOD;
	}
	return res;
}

LL n;

int main()
{
//	freopen("1.in","r",stdin);
	prime(N-1);
	cin>>n;
	LL ans=0;
	for(LL i=1,j,t;i<=n;i=j+1) {
		t=n/i; j=n/t;
		ans=(ans+(Sieve(j)-Sieve(i-1))%MOD*sqr(f(t))%MOD+MOD)%MOD;
	}
	ans=(ans+MOD)%MOD;
	cout<<ans<<endl;
	return 0;
}

