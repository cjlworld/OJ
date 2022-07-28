#include<bits/stdc++.h>
#define LL long long 
using namespace std;
const int N=4;
LL MOD;
LL n;
LL ago[N][N]=
{
	{0},
	{0,1,1},
	{0,1,0},
};
struct matrix
{
	int n,m;
	LL g[N][N];
	void set(int x) //建立x*x的单位矩阵 
	{
		n=m=x;
		for(int i=1;i<=x;i++) 
			for(int j=1;j<=x;j++) 
				g[i][j]=(i==j);
		return;
	}
	void clear() //矩阵初始化 
	{
		n=m=0;
		memset(g,0,sizeof(g));
		return;	
	} 
}; 
matrix operator*(matrix x,matrix y) //重载运算符
{
	matrix z;
	z.clear();
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
matrix operator^(matrix x,LL k) //需要矩阵乘法
{
	matrix res;
	res.set(3); 
	while(k) {
		if(k&1) res=res*x;
		x=x*x; k>>=1;
	}
	return res;
}
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%lld%lld",&n,&MOD);
	matrix x;
	matrix ss;
	matrix ans;
	x.clear();
	x.m=x.n=2;
	for(int i=1;i<=2;i++) 
		for(int j=1;j<=2;j++) 
			x.g[i][j]=ago[i][j];
	ss.clear();	
	ss.n=2; ss.m=1;
	ss.g[1][1]=1;
	ss.g[2][1]=1;
	ans.clear();
	ans=(x^(n-2))*ss;
	printf("%lld\n",ans.g[1][1]);
	return 0;
}

