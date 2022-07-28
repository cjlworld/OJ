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
LL phi[N],f[N];
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

	for(i=1;i<=n;i++) 
		for(j=i;j<=n;j+=i)
			f[j]+=phi[j/i]*i;
	
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
