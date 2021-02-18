#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;

const int N=5e6+5;
const LL MOD=1e9+7;

LL power(LL x,LL k,LL MOD)
{
	LL res=1; x%=MOD;
	while(k) {
		if(k&1) res=res*x%MOD;
		x=x*x%MOD; k>>=1;
	}
	return res%MOD;
}

LL times;

LL p[N],tot;
int low[N];
LL f[N];

void prime(LL n)
{
	LL i,j,k;
	for(i=2;i<=n;i++) {
		if(!low[i]) p[++tot]=low[i]=i;
		for(j=1;j<=tot && i*p[j]<=n && p[j]<=low[i];j++) 
			low[i*p[j]]=p[j];
	}
	
	f[1]=1;
	for(i=1;i<=tot;i++) {
		k=power(p[i],times,MOD);
		f[p[i]]=k-1;
		for(j=p[i]*p[i];j<=n;j*=p[i]) 
			f[j]=f[j/p[i]]*k%MOD;
	}
	
	for(i=2;i<=n;i++)
		for(j=1;j<=tot && i*p[j]<=n && p[j]<low[i];j++) 
			for(k=p[j];i*k<=n;k*=p[j]) 
				f[i*k]=f[i]*f[k]%MOD;
				
	for(i=1;i<=n;i++) f[i]=(f[i]+f[i-1])%MOD;
}

int T,n,m;

int main()
{
	cin>>T>>times;
	prime(N-1);
	
	while(T--) {
		cin>>n>>m;
		LL i,j,tn,tm,ans=0;
		for(i=1;i<=n && i<=m;i=j+1) {
			tn=n/i; tm=m/i;
			j=min(n/tn,m/tm);
			
			ans=(ans+(f[j]-f[i-1])*tn%MOD*tm%MOD+MOD)%MOD;
		}
		cout<<ans<<endl;
	}
	return 0;
}

