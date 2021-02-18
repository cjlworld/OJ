#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=4e5+5;
const LL Ps[]={998244353,469762049,1004535809},G=3;

LL muler(LL x,LL y,LL MOD)
{
	x=(x%MOD+MOD)%MOD; y=(y%MOD+MOD)%MOD;
	LL high=(long double)x/MOD*y;
	LL low=x*y-high*MOD;
	return (low%MOD+MOD)%MOD;
}

LL power(LL x,LL k,LL MOD)
{
	LL res=1; x%=MOD;
	while(k) {
		if(k&1) res=muler(res,x,MOD);
		x=muler(x,x,MOD); k>>=1;
	}
	return res%MOD;
}

int rev[N];
void ntt(LL a[],LL n,LL inv,LL P)
{
	for(int i=0;i<n;i++) 
		if(rev[i]<i) swap(a[rev[i]],a[i]);
	for(int k=2,m=1;k<=n;m=k,k<<=1) {
		LL gn=power(G,(P-1)/k,P);
		if(inv==-1) gn=power(gn,P-2,P);
		for(int i=0;i<n;i+=k) {
			LL g=1;
			for(int j=0;j<m;j++,g=g*gn%P) {
				LL u=a[i+j],v=a[i+j+m];
				a[i+j]=u+g*v; a[i+j+m]=u-g*v;
			}
		}
		for(int i=0;i<n;i++) a[i]=(a[i]%P+P)%P;
	}
	if(~inv) return;
	LL invn=power(n,P-2,P);
	for(int i=0;i<n;i++) a[i]=(a[i]*invn)%P;
}

void TMntt(LL a[],LL b[],LL c[],int n,LL MOD)
{
	static LL A[N],B[N],E[N],F[N],Ans[3][N];
	static const LL Inv0=power(Ps[1],Ps[0]-2,Ps[0]),Inv1=power(Ps[0],Ps[1]-2,Ps[1]);
	static const LL M=Ps[0]*Ps[1],InvM=power(M,Ps[2]-2,Ps[2]);

	int bit=0,lim;
	while((1<<bit)<=n+n) bit++;
	lim=(1<<bit);
	
	for(int i=0;i<lim;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
	for(int i=0;i<n;i++) A[i]=a[i],B[i]=b[i];
	for(int i=n;i<lim;i++) A[i]=0,B[i]=0;
	
	for(int p=0;p<3;p++) {
		for(int i=0;i<lim;i++) E[i]=A[i]%Ps[p],F[i]=B[i]%Ps[p];
		ntt(E,lim,1,Ps[p]); ntt(F,lim,1,Ps[p]);
		for(int i=0;i<lim;i++) Ans[p][i]=(E[i]*F[i])%Ps[p];
		ntt(Ans[p],lim,-1,Ps[p]);
	}
	
	LL x,y;
	for(int i=0;i<lim;i++) {
		x=(muler(Ans[0][i]*Ps[1],Inv0,M)+muler(Ans[1][i]*Ps[0],Inv1,M))%M;
		y=muler(Ans[2][i]-x,InvM,Ps[2]);
		c[i]=(muler(y,M,MOD)+x)%MOD;
	}
}

int n,m;
LL MOD;
LL a[N],b[N],c[N];

int main()
{
	int i;
	scanf("%d%d%lld",&n,&m,&MOD); n++,m++;
	for(i=0;i<n;i++) scanf("%lld",&a[i]);
	for(i=0;i<m;i++) scanf("%lld",&b[i]);
	TMntt(a,b,c,max(n,m),MOD);
	for(i=0;i<n+m-1;i++) printf("%lld ",c[i]);
	puts("");
	return 0;
}

