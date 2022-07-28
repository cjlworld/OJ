#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef vector<LL> Poly;

const LL N=2e6+5,P=998244353,G=3;

LL power(LL x,LL k,LL MOD)
{
	LL res=1; x%=MOD;
	while(k) {
		if(k&1) res=res*x%MOD;
		x=x*x%MOD; k>>=1;
	}
	return res%MOD;
}

int rev[N];
void ntt(LL a[],int n,int inv)
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
	if(inv==1) return;
	LL invn=power(n,P-2,P);
	for(int i=0;i<n;i++) a[i]=(a[i]*invn)%P;
}

Poly mul(Poly a,Poly b)
{
	static LL f[N],g[N];
	
	int bit=0,lim;
	while((1u<<bit)<=a.size()+b.size()) bit++;
	lim=(1<<bit);

	for(int i=0;i<lim;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
	
	for(int i=0;i<(int)a.size();i++) f[i]=a[i];
	for(int i=a.size();i<lim;i++) f[i]=0;
	for(int i=0;i<(int)b.size();i++) g[i]=b[i];
	for(int i=b.size();i<lim;i++) g[i]=0;
	
	ntt(f,lim,1); ntt(g,lim,1);
	for(int i=0;i<lim;i++) f[i]=(f[i]*g[i])%P;
	ntt(f,lim,-1);
	
	Poly res;
	for(int i=0;i<(int)(a.size()+b.size()-1);i++) 
		res.push_back(f[i]);
	return res;
}

Poly sub(Poly a,Poly b)
{
	while(a.size()<b.size()) a.push_back(0);
	for(int i=0;i<(int)b.size();i++) a[i]=(a[i]-b[i]+P)%P;
	return a;
}

Poly mul(Poly a,LL b)
{
	for(int i=0;i<(int)a.size();i++) a[i]=(a[i]*b+P)%P;
	return a;
}

Poly Polyinv(Poly A)
{
	Poly B;
	if(A.size()==1) {
		B.push_back(power(A[0],P-2,P));
		return B;
	}
	int len=(A.size()+1)/2;
	Poly A1=A; A1.erase(A1.begin()+len,A1.end());
	B=Polyinv(A1);
	B=sub(mul(B,2),mul(mul(B,A),B));
	B.erase(B.begin()+A.size(),B.end());
	return B;
}

int n;

int main()
{
//	freopen("1.in","r",stdin);
	Poly F,G;
	scanf("%d",&n);
	for(int i=0;i<n;i++) {
		LL x; scanf("%lld",&x);
		F.push_back(x);
	}
	G=Polyinv(F);
	for(int i=0;i<n;i++) printf("%lld ",G[i]);
	puts("");
	return 0;
}

