#include<bits/stdc++.h>
#define rint register int
#define INF 2147483646l
#define LL long long
using namespace std;
const LL MOD=1e9+7;
LL n;
const int N=10;
LL ago[6][6]=
{
	{0},
	{0,1,1},
	{0,1,0}
};

struct matrix
{
	int n,m;
	LL g[N][N];
	void set(int x) 
	{
		n=m=x;
		for(int i=1;i<=x;i++) 
			for(int j=1;j<=x;j++) 
				g[i][j]=(i==j);
		return;
	}
};
matrix ss;
matrix operator*(matrix x,matrix y)
{
	matrix z;
	memset(z.g,0,sizeof(z.g));
	z.n=x.n; z.m=y.m;
	for(int i=1;i<=z.n;i++) {
		for(int j=1;j<=z.m;j++) {
			LL ans=0;
			for(int k=1;k<=x.m;k++) 
				ans+=(x.g[i][k]*y.g[k][j])%MOD;
			z.g[i][j]=ans%MOD;
		}
	}
	return z;
}
matrix operator^(matrix x,LL k)
{
	matrix res;
	memset(res.g,0,sizeof(res.g));
	res.set(2);
	while(k)
	{
		if(k&1) res=res*x;
		x=x*x; k>>=1;
	}
	return res;
}
matrix c;
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%lld",&n);
	for(int i=1;i<=2;i++) 
		for(int j=1;j<=2;j++)
			ss.g[i][j]=ago[i][j];
	ss.n=ss.m=2;
	c.n=2; c.m=1;
	c.g[1][1]=1;
	c.g[2][1]=1;
	if(n==1||n==2) {
		puts("1"); return 0;
	}
	if(n==3) {
		puts("2"); return 0;
	}
	c=(ss^(n-2))*c;
	printf("%lld\n",c.g[1][1]%MOD);
	return 0;
}

