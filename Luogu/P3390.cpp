#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL MOD=1e9+7;
const LL N=100+5;
const LL K=1e12+5;
LL n,k;
struct matrix
{
	LL n,m,g[N][N];
	void set(int x) {
		n=m=x;
		for(int i=1;i<=n;i++) 
			for(int j=1;j<=m;j++) 
				g[i][j]=(i==j);
		return;
	}
};
matrix x;
matrix operator*(matrix x,matrix y)
{
	matrix z;
	z.n=x.n; z.m=y.m;
	memset(z.g,0,sizeof(z.g));
	for(int i=1;i<=z.n;i++) {
		for(int j=1;j<=z.m;j++) {
			long long ans=0;
			for(int k=1;k<=x.m;k++) 
				ans+=(LL)x.g[i][k]*y.g[k][j],ans=ans%MOD;
			z.g[i][j]=ans%MOD;
		}
	}
	return z;
}
matrix operator^(matrix x,LL k)
{
	matrix res;
	res.set(n);
	while(k) {
		if(k&1) res=operator*(res,x);
		x=operator*(x,x); k>>=1;
	}
	return res;
}
void matrix_put(matrix a)
{
	int i,j;
	for(i=1;i<=a.n;i++) {
		for(j=1;j<=a.m;j++) 
			printf("%lld ",a.g[i][j]);
		printf("\n");
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%lld%lld",&n,&k);
	x.m=x.n=n;
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=n;j++) 
			scanf("%lld",&x.g[i][j]);
	x=operator^(x,k);
	matrix_put(x);
	return 0;
}
