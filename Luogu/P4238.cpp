#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;

const int N=8e5+5;
const LL P=998244353,G=3;

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
	int bit=0;
	while((1<<bit)<n) bit++;
	for(int i=0;i<n;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
	
	for(int i=0;i<n;i++) 
		if(rev[i]<i) swap(a[i],a[rev[i]]);
	for(int k=2,m=1;k<=n;m=k,k<<=1) {
		LL gn=power(G,(P-1)/k,P);
		if(inv==-1) gn=power(gn,P-2,P);
		for(int i=0;i<n;i+=k) {
			LL g=1;
			for(int j=0;j<m;j++,g=(g*gn)%P) {
				LL u=a[i+j],v=a[i+j+m];
				a[i+j]=u+g*v; a[i+j+m]=u-g*v;
			}
		}
		for(int i=0;i<n;i++) a[i]=(a[i]%P+P)%P;
	}
	if(inv==1) return;
	LL invn=power(n,P-2,P);
	for(int i=0;i<n;i++) a[i]=a[i]*invn%P;
}

void Polyinv(LL a[],LL b[],int n)
{
	static LL c[N];
    if(n==1) {
        b[0]=power(a[0],P-2,P);
        return;
    }
    Polyinv(a,b,(n+1)>>1);
    int lim=1;
    while(lim<(n<<1)) lim<<=1;

    for(int i=0;i<n;i++) c[i]=a[i];
    for(int i=n;i<lim;i++) c[i]=0;
    ntt(c,lim,1); ntt(b,lim,1);
    for(int i=0;i<lim;i++) b[i]=(2+P-b[i]*c[i]%P)*b[i]%P;
    ntt(b,lim,-1);
    for(int i=n;i<lim;i++) b[i]=0;
}

int n;
LL a[N],b[N];

int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;i++) 
		scanf("%lld",&a[i]),a[i]%=P;
	Polyinv(a,b,n);
	for(int i=0;i<n;i++) printf("%lld ",b[i]);
	return 0;
}
