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
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=16;
const LL MOD=10000007;

int n,m;

struct Matrix
{
	int n,m;
	LL a[N][N];
	Matrix() { memset(a,0,sizeof a),n=m=0; }
};

Matrix mul(Matrix x,Matrix y)
{
	Matrix z;
	z.n=x.n,z.m=y.m;
	int i,j,k;
	for(i=1;i<=z.n;i++) 
		for(j=1;j<=z.m;j++) 
			for(k=1;k<=x.m;k++) 
				z.a[i][j]=(z.a[i][j]+x.a[i][k]*y.a[k][j]%MOD)%MOD;
	return z;
}

Matrix fpow(Matrix x,int k)
{
	Matrix res;
	res.n=res.m=x.n;
	for(int i=1;i<=res.n;i++)
		res.a[i][i]=1;
		
	while(k) {
		if(k&1) res=mul(res,x);
		x=mul(x,x); k>>=1;
	}
	return res;
}

void output(Matrix x)
{
	int i,j;
	for(i=1;i<=x.n;i++,printf("\n")) 
		for(j=1;j<=x.m;j++) 
			printf("%lld ",x.a[i][j]);
	printf("\n");
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	Matrix A,B,C;
	while(~scanf("%d%d",&n,&m)) {
		A=Matrix(),B=Matrix(),C=Matrix();
		
		A.n=n+2,A.m=1;
		A.a[1][1]=23;
		for(i=2;i<=n+1;i++) 
			scanf("%lld",&A.a[i][1]);
		A.a[n+2][1]=1;
		
		B.n=B.m=n+2;
		
		for(i=2;i<=B.n;i++) B.a[i][i]=1;
		B.a[1][1]=10;
		B.a[1][n+2]=3;
		for(i=1;i<=B.n-1;i++) 
			for(j=1;j<=B.m;j++) 
				B.a[i][j]+=B.a[i-1][j];
//		output(A);
//		output(B);
		B=fpow(B,m);
		C=mul(B,A);
//		output(C);
		printf("%lld\n",C.a[n+1][1]%MOD);
	}
	
	return 0;
}

