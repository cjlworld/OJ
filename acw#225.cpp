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

const int N=32;

int MOD,n,k;

struct Matrix
{
	int n,m;
	int a[N][N];
	Matrix() { memset(a,0,sizeof a),n=m=0; }
};

Matrix mul(Matrix x,Matrix y)
{
	Matrix z;
	z.n=x.n,z.m=y.m;
	// x.m==y.n;
	int i,j,k;
	for(i=1;i<=z.n;i++) 
		for(j=1;j<=z.m;j++) 
			for(k=1;k<=y.n;k++) 
				z.a[i][j]=(z.a[i][j]+x.a[i][k]*y.a[k][j]%MOD)%MOD;
	return z;
}

Matrix add(Matrix x,Matrix y)
{
	int i,j;
	for(i=1;i<=x.n;i++) 
		for(j=1;j<=x.m;j++) 
			x.a[i][j]=(x.a[i][j]+y.a[i][j])%MOD;
	return x;	
}

Matrix fpow(Matrix x,int k)
{
	Matrix res;
	res.n=res.m=x.n;
	for(int i=1;i<=res.n;i++) res.a[i][i]=1;
	
	while(k) {
		if(k&1) res=mul(res,x);
		x=mul(x,x); k>>=1;
	}
	return res;
}

Matrix fsum(Matrix x,int k)
{
	if(k==1) return x;
	Matrix res,t;
	res.n=res.m=x.n;
	if(k&1) res=add(res,fpow(x,k)),k--;
	t=fsum(x,k>>1);
	res=add(res,t);
	t=mul(t,fpow(x,k>>1));
	res=add(res,t);
	return res;
}

void output(Matrix x)
{
	int i,j;
	for(i=1;i<=x.n;i++,printf("\n"))
		for(j=1;j<=x.m;j++) 
			printf("%d ",x.a[i][j]);
}

int main()
{
//	freopen("1.in","r",stdin);
	cin>>n>>k>>MOD;
	Matrix A;
	A.n=A.m=n;
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=n;j++) 
			scanf("%d",&A.a[i][j]);
	output(fsum(A,k));
	return 0;
}

