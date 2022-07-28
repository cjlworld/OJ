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

int rev[N];
void fft(cp a[],int n,int inv)
{
	for(int i=0;i<n;i++) 
		if(i<rev[i]) swap(a[i],a[rev[i]]);	
	for(int k=2,m=1;k<=n;m=k,k<<=1) {
		cp wn(cos(2*PI/k),inv*sin(2*PI/k));
		for(int i=0;i<n;i+=k) {
			cp w(1,0);
			for(int j=0;j<m;j++,w*=wn) {
				cp u=a[i+j],v=a[i+j+m];
				a[i+j]=u+w*v,a[i+j+m]=u-w*v;
			}
		}
	}
}

int n,m,tot,bit;
cp a[N],b[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	double x;
	scanf("%d%d",&n,&m);
	for(i=0;i<=n;i++) scanf("%lf",&x),a[i].real(x);
	for(i=0;i<=m;i++) scanf("%lf",&x),b[i].real(x);
	
	for(tot=1,bit=0;tot<=n+m;tot<<=1,bit++);
	for(i=0;i<tot;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
	fft(a,tot,1),fft(b,tot,1);
	for(i=0;i<tot;i++) a[i]=a[i]*b[i];
	fft(a,tot,-1);
	
	for(i=0;i<=n+m;i++)
		printf("%lld ",(LL)round(a[i].real()/tot)); // !
	return 0;
}

