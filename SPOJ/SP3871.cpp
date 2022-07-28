#include<map>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;

const LL N=1e6+5;

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
	for(i=1;i<=tot;i++) {
		f[p[i]]=p[i]-1+p[i];
		for(j=p[i]*p[i];j<=n;j*=p[i]) 
			f[j]=(f[j/p[i]]-j/p[i])*p[i]+j/p[i]*(p[i]-1)+j;
	}
		
	for(i=2;i<=n;i++) 
		for(j=1;j<=tot && i*p[j]<=n && p[j]<low[i];j++) 
			for(k=p[j];i*k<=n;k*=p[j]) {
				f[i*k]=f[i]*f[k];
//				printf("%lld : %lld * %lld , f[] = %lld\n",i*k,i,k,f[i*k]);
			}
					
//	for(i=1;i<=20;i++) printf("%lld\n",f[i]);
	for(i=1;i<=n;i++) f[i]=f[i]+f[i-1]-i;
}

int n;

int main()
{
//	freopen("1.in","r",stdin);
	prime(N-1);
	
	while(scanf("%d",&n),n) 
		printf("%lld\n",f[n]);
	return 0;
}
