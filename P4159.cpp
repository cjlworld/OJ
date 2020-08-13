#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
#define rint register int
using namespace std;
const int N=100;
const int MOD=2009;
int n,T;
int w[N][N];
char a[N];
template<class T>
struct matrix
{
	int n,m;
	T a[N][N];
	inline void clear()
	{
		n=m=0;
		memset(a,0,sizeof a);
		return;
	}
	matrix() { clear(); }
	inline void equal(T g[][100],int nn,int mm)
	{
		int i,j;
		clear();
		n=nn; m=mm;
		for(i=1;i<=n;i++) 
			for(j=1;j<=m;j++)
				a[i][j]=g[i][j];
		return;
	} 
	inline void reset(int length)
	{
		clear();
		n=m=length;
		for(int i=1;i<=length;i++)
			a[i][i]=1;
		return;
	} 
	friend inline matrix operator*(const matrix &x,const matrix &y)
	{
		matrix z;
		// z(i,j)= omika : x(i,k)*y(k,j)
		z.n=x.n; z.m=y.m;
		int i,j,k;
		for(i=1;i<=z.n;i++) 
			for(j=1;j<=z.m;j++) 
				for(k=1;k<=x.m;k++) 
					z.a[i][j]=(z.a[i][j]+x.a[i][k]*y.a[k][j]%MOD)%MOD;
		return z;
	}
	template<class T1>
	friend inline matrix operator^(matrix x,T1 k)
	{
		matrix res;
		res.reset(x.n);
		while(k>0) {
			if(k&1) res=res*x;
			x=x*x; k>>=1;
		}
		return res;
	}
	friend inline matrix operator%(matrix x,T k)
	{
		int i,j;
		for(i=1;i<=x.n;i++) 
			for(j=1;j<=x.m;j++) 
				x.a[i][j]=(x.a[i][j]%k);
		return x;
	}
};
int main()
{
//	freopen("1.in","r",stdin);
	rint i,j,k;
	int x,y;
	scanf("%d%d",&n,&T);
	for(i=1;i<=n;i++) {
		scanf("%s",a+1);
		for(j=1;j<=n;j++) {
			x=a[j]-'0';
			y=9*i-8;
			if(x==0) 
				continue;
			for(k=1;k<=x-1;k++) 
				w[y+k-1][y+k]=1;
			w[y+x-1][9*j-8]=1;
		}
	}
	matrix<int> A;
	A.equal(w,9*n,9*n);
	A=A^T;
	printf("%d",A.a[1][9*n-8]);
	return 0;
}

