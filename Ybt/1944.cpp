#include<cstdio>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=56;
int n,m;
ULL f[N][N];
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	cin>>n>>m;
	f[1][0]=1;
	for(i=1;i<=m;i++) 
		for(j=1;j<=n;j++) 
			f[j][i]=f[(j==1) ? n : j-1][i-1]+f[(j==n) ? 1 : j+1][i-1];
	printf("%llu",f[1][m]);
	return 0;
}


