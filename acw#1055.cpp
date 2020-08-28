#include<cstdio>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=1e5+5;
LL a[N],f[N],cmax;
int n;
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	scanf("%d",&n);
	for(i=1;i<=n;i++) 
		scanf("%lld",&a[i]);
	cmax=-a[1];
	for(i=2;i<=n;i++) {
		f[i]=max(f[i-1],a[i]+cmax);
		cmax=max(cmax,f[i-1]-a[i]);
	}
//	for(i=1;i<=n;i++) 
//		cout<<f[i]<<" ";
	cout<<f[n];
	return 0;
}

