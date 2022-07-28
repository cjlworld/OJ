#include<cstdio>
#include<iostream>

using namespace std;
typedef long long LL;

const LL N=5e6+5;

LL p[N],tot;
int low[N];
LL f[N];
void prime(int n)
{
	LL i,j,k;
	for(i=2;i<=n;i++) {
		if(!low[i]) p[++tot]=low[i]=i;
		for(j=1;j<=tot && i*p[j]<=n;j++) {
			low[i*p[j]]=p[j];
			if(low[i]==p[j]) continue;
		}
	}
	
	f[1]=1;
	for(i=1;i<=tot;i++) 
		for(j=p[i];j<=n;j*=p[i]) 
			f[j]=(f[j/p[i]]-j/p[i])*p[i]+j/p[i]*(p[i]-1)+j;
		
	for(i=2;i<=n;i++) 
		for(j=1;j<=tot && i*p[j]<=n && p[j]<low[i];j++) 
			for(k=p[j];i*k<=n;k*=p[j]) 
				f[i*k]=f[i]*f[k];
				
	for(i=1;i<=n;i++) f[i]=f[i]+f[i-1]-i;
}

int T,n;

int main()
{
	prime(N-1);
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		printf("%lld\n",f[n]);
	}
	return 0;
}
