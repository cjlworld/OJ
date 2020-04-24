#include<bits/stdc++.h>
#define rint register int
#define INF 2147483646
using namespace std;
const int N=105;
int n,m;
int a[N][N],sum[N][N];
void Init()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=m;j++) 
			scanf("%d",&a[i][j]);
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=m;j++) 
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a[i][j];
	return;
} 
int answer()
{
	for(int k=min(n,m);k>=1;k--) {
		for(int i=k;i<=n;i++) {
			for(int j=k;j<=m;j++) {
				if(sum[i][j]-sum[i-k][j]-sum[i][j-k]+sum[i-k][j-k]==k*k) return k;
			}
		}
	}
	return 0;
}
int main()
{
//	freopen("1.in","r",stdin);
	Init();
	printf("%d",answer());
	return 0;
}

