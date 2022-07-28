#include<cstdio>
#include<iostream>
#define LL long long
#define rint register int
using namespace std;
const int N=50*50;
int n;
int a[N][2];
int ans[50][50];
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	cin>>n;
	a[1][0]=1;
	a[1][1]=(n+1)>>1;
	ans[a[1][0]][a[1][1]]=1;
	for(i=2;i<=n*n;i++) {
		if(a[i-1][0]==1&&a[i-1][1]<n) 
			a[i][0]=n,a[i][1]=a[i-1][1]+1;
		else if(a[i-1][0]>1&&a[i-1][1]==n) 
			a[i][0]=a[i-1][0]-1,a[i][1]=1;
		else if(a[i-1][0]==1&&a[i-1][1]==n)	
			a[i][0]=2,a[i][1]=n;
		else if(ans[a[i-1][0]-1][a[i-1][1]+1]==0) 
			a[i][0]=a[i-1][0]-1,a[i][1]=a[i-1][1]+1;
		else a[i][0]=a[i-1][0]+1,a[i][1]=a[i-1][1];
		ans[a[i][0]][a[i][1]]=i;
	}
	for(i=1;i<=n;i++) {
		for(j=1;j<=n;j++) 
			printf("%d ",ans[i][j]);
		printf("\n");
	}
	return 0;
}

