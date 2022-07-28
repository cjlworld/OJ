#include<map>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;

const LL N=1e7+5;

LL MOD,n;

LL p[N],tot;
bool tag[N];
LL phi[N],sphi[N];
void prime(LL n)
{
	LL i,j;
	phi[1]=1;
	for(i=2;i<=n;i++) {
		if(!tag[i]) p[++tot]=i,phi[i]=i-1;
		for(j=1;j<=tot && i*p[j]<=n;j++) {
			tag[i*p[j]]=true;
			if(i%p[j]==0) {
				phi[i*p[j]]=phi[i]*p[j];
				break;
			}
			else phi[i*p[j]]=phi[i]*(p[j]-1);
		}
	}
	for(i=1;i<=n;i++) 
		sphi[i]=(sphi[i-1]+phi[i]*i%MOD*i%MOD)%MOD;
}

LL idsum(LL n) 
{ 
	LL x=n,y=n+1;
	if(x%2==0) x/=2;
	else y/=2;
	return (x%MOD)*(y%MOD)%MOD;
}

LL sqrsum(LL n)
{
	LL x=n,y=n+1,z=2*n+1;
	if(x%3==0) x/=3;
	else if(y%3==0) y/=3;
	else if(z%3==0) z/=3;
	
	if(x%2==0) x/=2;
	else if(y%2==0) y/=2;
	else if(z%2==0) z/=2;
	
	return (x%MOD)*(y%MOD)%MOD*(z%MOD)%MOD;
}

LL Sieve(LL n)
{
	static map<LL,LL> sums;
	if(n<N) return sphi[n];
	if(sums.count(n)) return sums[n];
	
	LL res=idsum(n)%MOD*idsum(n)%MOD;
	for(LL i=2,j,t;i<=n;i=j+1) {
		t=n/i; j=n/t;
		res=(res-(sqrsum(j)-sqrsum(i-1))*Sieve(t)%MOD)%MOD;
	}
	res=(res+MOD)%MOD;
	return sums[n]=res;
}

int main()
{
//	freopen("1.in","r",stdin);
	cin>>MOD>>n;
	prime(N-1);
	LL i,j,t,ans=0;
	for(i=1;i<=n;i=j+1) {
		t=n/i; j=n/t;
		ans=(ans+(Sieve(j)-Sieve(i-1))*idsum(t)%MOD*idsum(t)%MOD)%MOD;
	}
	ans=(ans+MOD)%MOD;
	cout<<ans<<endl;
	return 0;
}

