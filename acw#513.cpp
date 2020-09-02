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
const int N=256;
int m=128+30;
int a[N][N],s[N][N];
int n,d;
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d%d",&d,&n);
	for(i=1;i<=n;i++) {
		scanf("%d%d%d",&x,&y,&z);
		x+=30; y+=30;
		a[x][y]=z;
	}
	for(i=1;i<=N-30;i++) 
		for(j=1;j<=N-30;j++) 
			s[i][j]=s[i-1][j]+s[i][j-1]-s[i-1][j-1]+a[i][j];
	int ans=0,cnt=0;
	for(i=30;i<=m;i++) 
		for(j=30;j<=m;j++) {
			ans=max(ans,s[i+d][j+d]-s[i-d-1][j+d]-s[i+d][j-d-1]+s[i-d-1][j-d-1]);
		}
	for(i=30;i<=m;i++) 
		for(j=30;j<=m;j++) 
			if(s[i+d][j+d]-s[i-d-1][j+d]-s[i+d][j-d-1]+s[i-d-1][j-d-1]==ans) 
				cnt++;//,printf("%d %d\n",i,j);
	cout<<cnt<<" "<<ans;
	return 0;
}

