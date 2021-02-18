#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<complex>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
#define double long double
typedef complex<double> cp;

const int N=8e5+5;
const double PI=acos(-1);

LL MOD;

int rev[N];
void fft(cp a[],int n,int inv)
{
	for(int i=0;i<n;i++) 
		if(rev[i]<i) swap(a[rev[i]],a[i]);
	for(int k=2,m=1;k<=n;m=k,k<<=1) {
		cp wn(cos(2*PI/k),inv*sin(2*PI/k));
		for(int i=0;i<n;i+=k) {
			cp w(1,0);
			for(int j=0;j<m;j++,w*=wn) {
				cp u=a[i+j],v=a[i+j+m];
				a[i+j]=u+v*w,a[i+j+m]=u-v*w;
			}
		}
	}
	if(inv==-1) {
		for(int i=0;i<n;i++) 
			a[i].real(a[i].real()/n);
	}
}

void mtt(LL a[],LL b[],LL c[],int n)
{
	static cp A[N],B[N],C[N],D[N],E[N],F[N];
	static const LL M=(1ll<<15);
	
	int i,bit=0;
	while((1<<bit)<=2*n) bit++;
	n=(1<<bit);
	
	for(i=0;i<n;i++) 
		rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
		
	for(i=0;i<n;i++) 
		A[i]=cp(0,0),B[i]=cp(0,0),C[i]=cp(0,0),D[i]=cp(0,0);
	for(i=0;i<n;i++) A[i].real(a[i]/M),B[i].real(a[i]%M);
	for(i=0;i<n;i++) C[i].real(b[i]/M),D[i].real(b[i]%M);
	
	fft(A,n,1); fft(B,n,1); fft(C,n,1); fft(D,n,1);
	for(i=0;i<n;i++) E[i]=A[i]*C[i],F[i]=B[i]*D[i];		
	fft(E,n,-1); fft(F,n,-1);
	for(i=0;i<n;i++) c[i]=((LL)round(E[i].real()))%MOD*M%MOD*M%MOD+(LL)round(F[i].real());
	for(i=0;i<n;i++) c[i]%=MOD;
	for(i=0;i<n;i++) E[i]=A[i]*D[i]+B[i]*C[i];
	fft(E,n,-1);
	for(i=0;i<n;i++) c[i]=(c[i]+((LL)round(E[i].real()))%MOD*M%MOD)%MOD;
}

int n,m;
LL f[N],g[N],ans[N];

int main()
{
	scanf("%d%d%lld",&n,&m,&MOD);
	n++,m++;
	for(int i=0;i<n;i++) scanf("%lld",&f[i]);
	for(int i=0;i<m;i++) scanf("%lld",&g[i]);
	
	mtt(f,g,ans,max(n,m));
	for(int i=0;i<n+m-1;i++) 
		printf("%lld ",ans[i]);
	return 0;
}

