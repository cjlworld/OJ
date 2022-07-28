#include<bits/stdc++.h>
using namespace std;
int n;
int a[1005][1005];
int f[1005][1005];
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	cin>>n;
	for(i=1;i<=n;i++) {
		for(j=1;j<=n;j++) {
			cin>>a[i][j];
		}
	}
	memset(f,0x3f3f3f,sizeof(f));
	f[1][0]=0;
	f[0][1]=0;
	for(i=1;i<=n;i++) {
		for(j=1;j<=n;j++) {
			f[i][j]=min(f[i][j],f[i][j-1]+a[i][j]);
			f[i][j]=min(f[i][j],f[i-1][j]+a[i][j]);
		}
	}
//	cout<<f[1][1]<<endl;
	cout<<f[n][n];
	return 0;
}

