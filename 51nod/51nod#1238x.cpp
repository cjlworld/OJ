#include<map>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;

const LL N=1e7+5,MOD=1e9+7;

LL power(LL x,LL k,LL MOD)
{
	LL res=1; x%=MOD;
	while(k) {
		if(k&1) res=res*x%MOD;
		x=x*x%MOD; k>>=1;
	}
	return res%MOD;
}

const LL inv2=power(2,MOD-2,MOD),inv6=power(6,MOD-2,MOD);

inline LL idsum(LL n) { return (n%MOD)*((n+1)%MOD)%MOD*inv2%MOD; } 
inline LL sqrsum(LL n) { return (n%MOD)*((n+1)%MOD)%MOD*((2*n+1)%MOD)%MOD*inv6%MOD; }
inline LL sqr(LL n) { return (n%MOD)*(n%MOD)%MOD; }

LL p[N],tot;
bool tag[N];
LL miu[N],f[N];
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
	
	for(i=1;i<=n;i++) {
		if(!miu[i]) continue;
		for(j=i;j<=n;j+=i) // 注意这里还会更新 f[i] 
			f[j]=(f[j]+i*miu[i])%MOD;
	}
	for(i=1;i<=n;i++) f[i]=(f[i]*i)%MOD; // 因为有那句 !miu[i] , 要放在外面，否则被误杀。 
	for(i=1;i<=n;i++) f[i]=(f[i]+f[i-1]+MOD)%MOD;
	
	for(i=1;i<=n;i++) miu[i]=((i*miu[i]%MOD*i%MOD+miu[i-1])%MOD+MOD)%MOD;
}

LL Sieve(LL n)
{
	static map<LL,LL> sums;
	
	if(n<N) return miu[n];
	if(sums.count(n)) return sums[n];
	
	LL res=1;
	for(LL i=2,j,t;i<=n;i=j+1) {
		t=n/i; j=n/t;
		res=(res-(sqrsum(j)-sqrsum(i-1))%MOD*Sieve(t)%MOD+MOD)%MOD;
	}
	res=(res+MOD)%MOD;
	return sums[n]=res;
}

LL F(LL n)
{
	static map<LL,LL> sums;
	
	if(n<N) return f[n];
	if(sums.count(n)) return sums[n];
	
	LL res=0;
	for(LL i=1,j,t;i<=n;i=j+1) {
		t=n/i; j=n/t;
		res=(res+(Sieve(j)-Sieve(i-1))%MOD*(idsum(t)%MOD)%MOD)%MOD;
	}
	res=(res+MOD)%MOD;
	return sums[n]=res;
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
		ans=(ans+(F(j)-F(i-1))%MOD*sqr(idsum(t))%MOD+MOD)%MOD;
	}
	ans=(ans+MOD)%MOD;
	cout<<ans<<endl;
	return 0;
}

