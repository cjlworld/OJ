#include<bits/stdc++.h>
using namespace std;
int n,m;//n种面值的货币系统，求组成面值为m的货币有多少种方案。
long long f[10000000];
long long a[10000000];
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	cin>>n>>m;
	for(i=1;i<=n;i++) 
		cin>>a[i];
	f[0]=1;
	for(i=1;i<=n;i++) {
		for(j=0;j<=m;j++) {
			if(j-a[i]>=0) {
				f[j]=f[j]+f[j-a[i]];
			}
		}
	}
	cout<<f[m];
	return 0;
}

