#include<cstdio>
#include<iostream>

using namespace std;

const int N=100+5,INF=1e9;
int a[N][N],s[N][N]; // s[i][j] 表示第i行的前j个数的和。 
int n;

int main()
{
	int i,j,l,r,x;
	cin>>n;
	for(i=1;i<=n;i++) 
		for(j=1;j<=n;j++) 
			cin>>a[i][j],s[i][j]=s[i][j-1]+a[i][j];
	int ans=-INF,cmax;
	for(l=1;l<=n;l++) {
		for(r=l;r<=n;r++) { // 枚举子矩阵的左边界和右边界 。 
			// 然后用最大子段和的那个DP，DP出上边界和下边界。 
			cmax=s[1][r]-s[1][l-1]; //非空 
			ans=max(ans,cmax);
			for(i=2;i<=n;i++) {
				x=s[i][r]-s[i][l-1];
				ans=max(ans,x); // Case 1
				ans=max(ans,cmax+x); // Case 2
				cmax=max(cmax+x,x); // 最大下缀和必须有x（非空） 
			}
		}
	}
	cout<<ans;
	return 0;
}
