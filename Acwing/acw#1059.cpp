#ifdef cjlworld
f[i] ---> ��i���ܻ�õ��������
f[i] = max ---> f[i-1]  // ʲô�¶�����
	       ---> f[j]+a[i]-a[j]-f , 1<=j<=i-1; // j�� i�� 
#endif
#include<cstdio>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=1e5+5;
int a[N],w;
int n;
int f[N],cmax; 
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	scanf("%d%d",&n,&w);
	for(i=1;i<=n;i++) 
		scanf("%d",&a[i]);
	cmax=-a[1]-w;
	for(i=2;i<=n;i++) {
		f[i]=max(f[i-1],a[i]+cmax);
		cmax=max(cmax,f[i]-a[i]-w);
	}
	cout<<f[n];
	return 0;
}

