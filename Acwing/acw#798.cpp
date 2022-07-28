#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=1024;

int n,m,q;
LL a[N][N],c[N][N];

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x1,y1,x2,y2;
	LL z;
	scanf("%d%d%d",&n,&m,&q);
	for(i=1;i<=n;i++) 
		for(j=1;j<=m;j++) 
			scanf("%lld",&a[i][j]);
	
	for(i=1;i<=n;i++) 
		for(j=1;j<=m;j++) 
			c[i][j]=a[i][j]+a[i-1][j-1]-a[i-1][j]-a[i][j-1];
	
	while(q--) {
		scanf("%d%d%d%d%lld",&x1,&y1,&x2,&y2,&z);
		c[x1][y1]+=z;
		c[x1][y2+1]-=z;
		c[x2+1][y1]-=z;
		c[x2+1][y2+1]+=z;
	}
	memset(a,0,sizeof a);
	for(i=1;i<=n;i++) 
		for(j=1;j<=m;j++) 
			a[i][j]=a[i-1][j]+a[i][j-1]-a[i-1][j-1]+c[i][j];
	
	for(i=1;i<=n;i++,printf("\n")) 
		for(j=1;j<=m;j++) 
			printf("%lld ",a[i][j]);
	return 0; 
}

