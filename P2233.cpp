#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
#define rint register int
using namespace std;
const int N=100;
const int MOD=1000;
LL g[N][N]=
{
{0,},
{0,0,1,0,0,0,0,0,1},
{0,1,0,1,},
{0,0,1,0,1,},
{0,0,0,1,0},
{0,0,0,0,1,0,1},
{0,0,0,0,0,0,0,1},
{0,0,0,0,0,0,1,0,1},
{0,1,0,0,0,0,0,1},
};
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
	inline void equal(T g[N][N],int nn,int mm)
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
	inline void output()
	{
		int i,j;
		for(i=1;i<=n;i++,putchar('\n')) 
			for(j=1;j<=m;j++) 
				cout<<a[i][j]<<" "; 
		cout<<endl;
		return;
	}
};
matrix<LL> A;
matrix<LL> B;
int n;
int main()
{
//	freopen("1.in","r",stdin);
	cin>>n;
	B.equal(g,8,8);
//	B.output();
	B=B^(n);
	A.n=8; A.m=1;
	A.a[1][1]=1;
	A=B*A;
//	A.output();
//	
//	A.output();
	cout<<A.a[5][1];
	return 0;
}

