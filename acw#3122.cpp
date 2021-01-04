#pragma GCC optimize("O2")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")

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
#include<complex>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef complex<double> cp;

const int N=4e5+5; // ¿ª4±¶
const double PI=acos(-1);

void fft(cp a[],int n,int inv)
{
	if(n==1) return;
	static cp buf[N];
	int m=n>>1;
	for(int i=0;i<m;i++) {
		buf[i]=a[2*i];
		buf[i+m]=a[2*i+1];
	}
	for(int i=0;i<n;i++) a[i]=buf[i];
	fft(a,m,inv);
	fft(a+m,m,inv);
	for(int i=0;i<m;i++) {
		cp x(cos(2*PI*i/n),inv*sin(2*PI*i/n));
		buf[i]=a[i]+x*a[i+m];
		buf[i+m]=a[i]-x*a[i+m];
	}
	for(int i=0;i<n;i++) a[i]=buf[i];
}

int n,m,tot;
cp a[N],b[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	double x;
	
	scanf("%d%d",&n,&m);
	for(i=0;i<=n;i++) 
		scanf("%lf",&x),a[i].real(x);
	for(i=0;i<=m;i++) 
		scanf("%lf",&x),b[i].real(x);
	
	for(tot=1;tot<n+m;tot<<=1);
	
	fft(a,tot,1),fft(b,tot,1);
	for(i=0;i<tot;i++) a[i]=a[i]*b[i];
	fft(a,tot,-1);
	
	for(i=0;i<=n+m;i++)
		printf("%lld ",(LL)round(a[i].real()/tot)); // !
	return 0;
}

