#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<bitset>
#include<vector>
#include<cstdio>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;

const LL MOD=1000000007;
const int N=1e7+5;

int p[N],tot;
bool tag[N];
int phi[N];

void prime(int n)
{
	int i,j;
	phi[1]=1;
	for(i=2;i<=n;i++) {
		if(!tag[i]) phi[p[++tot]=i]=i-1;
		for(j=1;j<=tot && i*p[j]<=n;j++) {
			tag[i*p[j]]=true;
			if(i%p[j]==0) {
				phi[i*p[j]]=phi[i]*p[j];
				break;
			}
			else phi[i*p[j]]=phi[i]*(p[j]-1);
		}
	}
}

LL varphi(int n)
{
	static map<int,LL> phis;
	
	if(n<N) return phi[n];
	if(phis.count(n)) return phis[n];
	
	int res=n,x=n;
	for(int i=1;i<=tot && p[i]*p[i]<=x;i++) {
		if(x%p[i]==0) {
			res=res/p[i]*(p[i]-1);
			while(x%p[i]==0) x/=p[i];
		}
	}
	if(x>1) res=res/x*(x-1);
	return phis[n]=res;
}

LL f(int n)
{
	LL res=1;
	for(int i=1;i*i<=n;i++) {
		if(n%i==0) {
			res+=i*varphi(i);
			if(i*i!=n) res+=n/i*varphi(n/i);
			(res>=1e17) && (res%=MOD);
		}
	}
	res%=MOD;
	if(res%2 && n%2) return (res*n+MOD)/2%MOD;
	else return (res*n)/2%MOD;
}

int T,n;

int main()
{
//	freopen("1.in","r",stdin);
	prime(N-1);
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		printf("%lld\n",f(n));
	}
	return 0;
}

