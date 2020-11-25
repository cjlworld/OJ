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

const int N=252;
const LL INF=0x3f3f3f3f3f3f3f3f;

int n,m,day,fes,row;
LL c[N];

inline void relax(LL &a,const LL &b) { a=((a>b) ? a : b); }

struct Matrix
{
	int n,m;
	LL a[N][N];
	void clear() { n=m=0,memset(a,-0x3f,sizeof a); }
	Matrix() { clear(); }
	void AddEdge(int x,int y,LL z) { relax(a[x][y],z); }
};

int get(int x,int y) 
{
	return (x-1)*5+y+1;
}

struct Festival
{
	int tim,x;
	LL addc;
	bool operator<(const Festival &t) const
	{
		return tim<t.tim;
	}
}b[N];

Matrix mul(const Matrix &x,const Matrix &y)
{
	static Matrix z;
	z.clear();
	z.n=x.n; z.m=y.m;
	int i,j,k;
	for(i=1;i<=z.n;i++) 
		for(j=1;j<=z.m;j++) 
			for(k=1;k<=y.n;k++) 
				relax(z.a[i][j],x.a[i][k]+y.a[k][j]);
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

Matrix g[N];
Matrix vpow(Matrix v,int k)
{
	for(int i=log2(day);i>=0;i--) 
		if((k>>i)&1) v=mul(v,g[i]);
	return v;
}

void output(const Matrix &x)
{
	int i,j;
	for(i=1;i<=x.n;i++,printf("\n")) 
		for(j=1;j<=x.m;j++) {
			if(x.a[i][j]<=-INF/2) printf("-inf ");
			else printf("%lld ",x.a[i][j]);
		}
	printf("\n");
}

Matrix A,B,C;
LL ans=-INF;

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	
	cin>>n>>m>>day>>fes;
	
	row=A.n=A.m=get(n,4);
	for(i=1;i<=n;i++) {
		for(j=1;j<=4;j++) 
			A.AddEdge(get(i,j-1),get(i,j),0);
	}
	for(i=1;i<=n;i++) cin>>c[i];	
		
	for(i=1;i<=m;i++) {
		cin>>x>>y>>z;
		A.AddEdge(get(x,z-1),get(y,0),c[y]);
	}

	for(i=1;i<=fes;i++) 
		cin>>b[i].tim>>b[i].x>>b[i].addc;
		
	sort(b+1,b+fes+1);
	
	g[0]=A;
	for(i=1;(1ll<<i)<=day;i++) 
		g[i]=mul(g[i-1],g[i-1]);
	
	B.clear();
	B.n=1,B.m=A.m;
	B.a[1][1]=0;

	for(i=1;i<=fes;i++) {
		C=A;
		x=get(b[i].x,0);
		for(j=1;j<=row;j++) 
			if(C.a[j][x]>=0) C.a[j][x]+=b[i].addc;
		
		B=vpow(B,b[i].tim-b[i-1].tim-1);
		B=mul(B,C);
//		output(C);
//		output(B);
	}
	B=vpow(B,day-b[fes].tim);
//	output(B);
	relax(ans,B.a[1][1]+c[1]);
	if(ans<=-INF/2) printf("-1\n");
	else printf("%lld\n",ans);
	
	return 0;
}

