#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=12;
int a[N][N],f[N][N][N][N];
int n;
int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	int i,j,k,r;
	int x,y,z;
	scanf("%d",&n);
	while(scanf("%d%d%d",&x,&y,&z)==3) 
		a[x][y]=z;
	for(i=1;i<=n;i++) 
		for(j=1;j<=n;j++) 
			for(k=1;k<=n;k++) 
				for(r=1;r<=n;r++) {
					f[i][j][k][r]=max(max(f[i-1][j][k-1][r],f[i][j-1][k-1][r]),max(f[i][j-1][k][r-1],f[i-1][j][k][r-1]))
						+a[i][j]+a[k][r]-(i==k&&j==r)*a[i][j];
			//		printf("%d %d %d %d : %d\n",i,j,k,r,f[i][j][k][r]);
				}
	cout<<f[n][n][n][n];
	return 0;
}

