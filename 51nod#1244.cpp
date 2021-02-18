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
	for(i=1;i<=n;i++) miu[i]+=miu[i-1];
}

LL Sieve(LL n)
{
	static map<LL,LL> sums;
	
	if(n<N) return miu[n];
	if(sums.count(n)) return sums[n];
	
	LL res=1;
	for(LL i=2,j,t;i<=n;i=j+1) {
		t=n/i; j=n/t;
		res-=(j-i+1)*Sieve(t);
	}
	return sums[n]=res;
}

int main()
{
//	freopen("1.in","r",stdin);
	prime(N-1);
	LL a,b;
	cin>>a>>b;
	cout<<Sieve(b)-Sieve(a-1);
	return 0;
}

