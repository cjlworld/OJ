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

const int N=5e5+5;
const double PI=acos(-1);

char s1[N],s2[N];

int rev[N];
void fft(cp a[],int n,int inv)
{
	for(int i=0;i<n;i++) 
		if(i>rev[i]) swap(a[i],a[rev[i]]);
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

cp a[N],b[N];
int tot,bit,n,m;
LL c[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	
	scanf("%s%s",s1,s2);
	n=strlen(s1),m=strlen(s2);
	for(i=0;i<n;i++) a[i].real(s1[n-i-1]-'0');
	for(i=0;i<m;i++) b[i].real(s2[m-i-1]-'0');
	
	for(tot=1,bit=0;tot<=n+m;tot<<=1,bit++);
	for(i=0;i<tot;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
	
	fft(a,tot,1),fft(b,tot,1);
	for(i=0;i<tot;i++) a[i]*=b[i];
	fft(a,tot,-1);
	
	for(i=0;i<tot;i++) c[i]=round(a[i].real()/tot);
	LL t=0;
	for(i=0;i<tot;i++) {
		t+=c[i];
		c[i]=t%10;
		t/=10;
	}
	
	for(i=tot;!c[i] && i>=0;i--);
	if(i==-1) printf("0\n");
	else {
		for(;i>=0;i--) printf("%lld",c[i]);
	}
	return 0;
}

