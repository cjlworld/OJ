#include<cmath>
#include<vector>
#include<cstdio>
#include<complex>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef vector<LL> Poly;
typedef complex<long double> cp;

const int N=8e5+5;
const LL MOD=100003;
const long double PI=acos(-1);

int rev[N];
void fft(cp a[],int n,int inv)
{
	for(int i=0;i<n;i++)
		if(rev[i]<i) swap(a[i],a[rev[i]]);
	for(int k=2,m=1;k<=n;m=k,k<<=1) {
		cp wn(cos(2*PI/k),inv*sin(2*PI/k));
		for(int i=0;i<n;i+=k) {
			cp w(1,0);
			for(int j=0;j<m;j++,w*=wn) {
				cp u=a[i+j],v=a[i+j+m];
				a[i+j]=u+w*v; a[i+j+m]=u-w*v;
			}
		}
	}
	if(inv==1) return;
	for(int i=0;i<n;i++) a[i].real(a[i].real()/n);
}


Poly mul(Poly a,Poly b)
{
	static cp f[N],g[N];
	
	int bit=0,lim;
	while((1u<<bit)<=a.size()+b.size()) bit++;
	lim=(1<<bit);
	
	for(int i=0;i<lim;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
	
	for(int i=0;i<(int)a.size();i++) f[i]=cp(a[i]%MOD,0);
	for(int i=a.size();i<lim;i++) f[i]=cp(0,0);
	for(int i=0;i<(int)b.size();i++) g[i]=cp(b[i]%MOD,0);
	for(int i=b.size();i<lim;i++) g[i]=cp(0,0);
	
	fft(f,lim,1); fft(g,lim,1);
	for(int i=0;i<lim;i++) f[i]*=g[i];
	fft(f,lim,-1);
	
	Poly res;
	for(int i=0;i<(int)(a.size()+b.size()-1);i++) 
		res.push_back(((LL)round(f[i].real())%MOD+MOD)%MOD);
//	for(int i=0;i<(int)res.size();i++) 
//		printf("%lld ",res[i]);
//	puts("");
	return res;
}

int n,m;
LL a[N];

Poly solve(int l,int r)
{
	if(l==r) {
		Poly res;
		res.push_back(1);
		res.push_back(a[l]%MOD);
		return res;
	}
	int mid=(l+r)>>1;
	return mul(solve(l,mid),solve(mid+1,r));
}

int main()
{
	int i,k;
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) 
		scanf("%lld",&a[i]),a[i]%=MOD;
	Poly ans=solve(1,n);
	
	while(m--) {
		scanf("%d",&k);
		printf("%lld\n",(ans[k]%MOD+MOD)%MOD);
	}
	return 0;
}

