#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;

const LL N=2e4+5,P=998244353,G=3;

int T,n;
LL f[N],fact[N];

int main()
{
//	freopen("1.in","r",stdin);
	LL i,j;
	fact[0]=1;
	for(i=1;i<N;i++) fact[i]=(fact[i-1]*i)%P;
	f[1]=0;
	for(i=2;i<N;i++) {
		for(j=1;j<=i-1;j++) 
			f[i]=(f[i]+fact[j]*(fact[i-j]-f[i-j]))%P;
//		cerr<<i<<endl;
	}
	scanf("%d",&T);
	while(T--) {
		scanf("%d",&n);
		printf("%lld\n",(fact[n]-f[n]+P)%P);
	}
	return 0;
}

