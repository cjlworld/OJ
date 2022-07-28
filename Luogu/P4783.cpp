#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<complex>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=1e3+5;
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

LL inv(LL x,LL MOD)
{
	return power(x,MOD-2,MOD);
}
LL mabs(LL x) { return ((x>0) ? x : -x); }

int n,m;
LL a[N][N];

int gauss()
{
	int r,c;
	for(c=0,r=0;c<n && r<n;c++) {
		int t=r;
		for(int i=r;i<n;i++) 
			if(mabs(a[i][c])>mabs(a[t][c])) t=i;
		for(int i=0;i<m;i++) 
			swap(a[r][i],a[t][i]);
		LL rate=a[r][c];
		if(rate==0) continue;
		for(int i=c;i<m;i++) a[r][i]=(a[r][i]*inv(rate,MOD))%MOD;
		for(int i=r+1;i<n;i++) {
			rate=a[i][c];
			for(int j=c;j<m;j++)
				a[i][j]=(a[i][j]-rate*a[r][j]%MOD)%MOD;
		}
		r++;
	}
	
	if(r<n) return 1;

	for(int i=n-1;i>=0;i--) 
		for(int j=i-1;j>=0;j--) {
			LL rate=a[j][i];
			for(int k=i;k<m;k++) 
				a[j][k]=(a[j][k]-rate*a[i][k]%MOD)%MOD;
		}
	return 0;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	
	scanf("%d",&n);
	m=2*n;
	for(i=0;i<n;i++) {
		for(j=0;j<n;j++) 
			scanf("%lld",&a[i][j]);
		for(j=n;j<m;j++) 
			a[i][j]=(j==i+n);
	}
	
	int ans=gauss();
	if(ans==1) puts("No Solution");
	else {
		for(i=0;i<n;i++,printf("\n")) 
			for(j=n;j<m;j++) 
				printf("%lld ",(a[i][j]+MOD)%MOD);
	}
	return 0;
}

