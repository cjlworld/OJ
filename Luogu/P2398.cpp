#include<map>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;

const LL N=5e6+5;

LL p[N],tot;
bool tag[N];
LL phi[N];
void prime(int n)
{
	int i,j;
	phi[1]=1;
	for(i=2;i<=n;i++) {
		if(!tag[i]) p[++tot]=i,phi[i]=i-1;
		for(j=1;j<=tot && p[j]*i<=n;j++) {
			tag[i*p[j]]=true;
			if(i%p[j]==0) {
				phi[i*p[j]]=phi[i]*p[j];
				break;
			}
			else phi[i*p[j]]=phi[i]*(p[j]-1);
		}
	}
	for(i=1;i<=n;i++) phi[i]+=phi[i-1];
}

LL Sieve(LL n)
{
	static map<LL,LL> sums;
	
	if(n<N) return phi[n];
	if(sums.count(n)) return sums[n];
	
	LL res=n*(n+1)/2;
	for(LL i=2,j,t;i<=n;i=j+1) {
		t=n/i; j=n/t;
		res-=(j-i+1)*Sieve(t);
	}
	return sums[n]=res;
}

LL n;

int main()
{
//	freopen("1.in","r",stdin);
	prime(N-1);
	cin>>n;
	
	LL i,j,t,ans=0;
	for(i=1;i<=n;i=j+1) {
		t=n/i; j=n/t;
		ans=(ans+(Sieve(j)-Sieve(i-1))*t*t);
	}
	cout<<ans<<endl;
	
	return 0;
}
