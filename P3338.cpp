#include<cmath>
#include<vector>
#include<cstdio>
#include<cstring>
#include<complex>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef complex<double> cp;

const int N=8e5+5;
const double PI=acos(-1);

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
				a[i+j]=u+v*w; a[i+j+m]=u-v*w;
			}
		}
	}
	if(inv==-1) 
		for(int i=0;i<n;i++) 
			a[i].real(a[i].real()/n);
}

int n,bit,lim;
cp g[N],q[N],p[N],E1[N],E2[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	double x;
	scanf("%d",&n); 
	for(i=1;i<=n;i++) {
		scanf("%lf",&x);
		q[i].real(x);
		p[n-i].real(x);
		g[i].real(1/((double)i*i));
	}
	lim++;
	while((1<<bit)<=2*n) bit++;
	lim=(1<<bit);
	
	for(i=0;i<lim;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
	
	fft(g,lim,1); fft(q,lim,1); fft(p,lim,1);
	for(i=0;i<lim;i++) E1[i]=g[i]*q[i],E2[i]=g[i]*p[i];
	fft(E1,lim,-1); fft(E2,lim,-1);
	
	for(i=1;i<=n;i++) 
		printf("%.3lf\n",E1[i].real()-E2[n-i].real());
	return 0;
}

