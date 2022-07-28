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

const int N=105;
const LL INF=0x3f3f3f3f3f3f3f3f;

inline void tense(LL &a,const LL &b) { a=((a<b) ? a : b); }
inline void relax(LL &a,const LL &b) { a=((a>b) ? a : b); }

struct Matrix 
{
	int n,m;
	LL a[N][N];
	Matrix(int n,int m) : n(n),m(m) { memset(a,0x3f,sizeof a); }
};

Matrix mul(Matrix x,Matrix y)
{
	Matrix z(x.n,y.m);
	int i,j,k;
	for(i=1;i<=z.n;i++) 
		for(j=1;j<=z.m;j++) 
			for(k=1;k<=y.n;k++)
				tense(z.a[i][j],x.a[i][k]+y.a[k][j]);
	return z;
}

Matrix fpow(Matrix x,Matrix res,int k)
{
	while(k) {
		if(k&1) res=mul(res,x);
		x=mul(x,x); k>>=1;
	}
	return res;
}

int n,m,T;

LL w[N][N],g[N][N];

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	int x,y,z;
	
	memset(w,0x3f,sizeof w);
	memset(g,0x3f,sizeof g);
	cin>>n>>m>>T;
	
	for(i=1;i<=m;i++) {
		cin>>x>>y>>z;
		tense(w[x][y],z);
		tense(g[x][y],-z);
	}
	for(i=1;i<=n;i++) w[i][i]=g[i][i]=0;
	for(k=1;k<=n;k++) 
		for(i=1;i<=n;i++) 
			for(j=1;j<=n;j++) 
				tense(w[i][j],w[i][k]+w[k][j]);
	
	if(T==0) {
		cout<<w[1][n]<<endl;
		return 0;
	}
	
	Matrix A(n,n);
	memcpy(A.a,w,sizeof A.a);
	Matrix B(n,n);
	memcpy(B.a,g,sizeof B.a);
	
	B=mul(B,A),B=mul(A,B);
	B=fpow(B,B,T-1);
	
	cout<<B.a[1][n]<<endl;
	return 0;
}

