#include<cstdio>
#include<iostream>
#define LL long long
using namespace std;
const int M=500;
int n,m;
int w[M],c[M];
int f[30005];
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++) {
		scanf("%d%d",&w[i],&x);
		c[i]=w[i]*x;
	}
	for(i=1;i<=m;i++) {
		for(j=n;j>=w[i];j--) {
			f[j]=max(f[j],f[j-w[i]]+c[i]);
		}
	}
	cout<<f[n];
	return 0;
}

