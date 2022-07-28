#include<bits/stdc++.h>
#define LL long long
using namespace std;
const LL MOD=1e9+7;
const int N=4;
LL t,n;
LL ago[N][N]=
	{
		{0},
		{0,1,0,1},
		{0,1,0,0},
		{0,0,1,0}
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
}x,ss;
matrix operator*(matrix x,matrix y)
{
	matrix z;
	memset(z.g,0,sizeof(z.g));
	z.n=x.n; z.m=y.m;
	for(int i=1;i<=z.n;i++) {
		for(int j=1;j<=z.m;j++) {
			LL ans=0;
			for(int k=1;k<=x.m;k++) 
				ans+=(LL)x.g[i][k]*y.g[k][j]%MOD;
			z.g[i][j]=ans%MOD;
		}
	}
	return z;
}
matrix operator^(matrix x,LL k)
{
	matrix res;
	res.set(3);
	while(k) {
		if(k&1) res=res*x;
		x=x*x; k>>=1;
	}
	return res;
}
void matrix_put(matrix a)
{
	for(int i=1;i<=a.n;i++) {
		for(int j=1;j<=a.m;j++) {
			printf("%lld ",a.g[i][j]%MOD);
		}
		puts("\n");
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%lld",&t);
	ss.g[1][1]=ss.g[2][1]=ss.g[3][1]=1;
	ss.n=3; ss.m=1;
	while(t--) {
		memset(x.g,0,sizeof(x.g));
		for(int i=1;i<=3;i++)
			for(int j=1;j<=3;j++)
				x.g[i][j]=ago[i][j];
		x.m=x.n=3;
		scanf("%d",&n);
		x=x^(n-1);
		x=ss*x;
		printf("%d\n",x.g[1][1]);
	}
	return 0;
}

