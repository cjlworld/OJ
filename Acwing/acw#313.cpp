#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
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

const int N=256;

int n,m;
LL a[N][N],f[N][N];
// f[i][j] 表示选到第 i 行第 j 列所得到的最大美观值。
// 其中 a[i][j] 不一定选了。
// 但第i行一定有选。 
int prex[N][N],prey[N][N];
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) 
		for(j=1;j<=m;j++) 
			scanf("%lld",&a[i][j]);
	memset(f,0xc0,sizeof f);
	memset(f[0],0,sizeof f[0]);
	for(i=1;i<=n;i++) {
		for(j=i;j<=m;j++) {
//			prex[i][j]=i-1;
//			prey[i][j]=j-1;
//			f[i][j]=f[i-1][j-1]+a[i][j];
//			
//			if(f[i][j-1]>=f[i][j]) {
//				prex[i][j]=i;
//				prey[i][j]=j-1;
//				f[i][j]=f[i][j-1];
//			}
			f[i][j]=max(f[i-1][j-1]+a[i][j],f[i][j-1]);
		}
	}
	cout<<f[n][m]<<endl;
		
	vector<int> ans;
	for(i=n;i>=1;i--) {
		if(i==n) 
			for(x=m;j>=1&&f[i][x-1]==f[n][m];x--);
		else {
			x=m;
			for(j=i;j<=m;j++) 
				if(f[i][j]+a[i+1][y]==f[i+1][y]) 
					x=min(x,j);	
		}
		y=x;
		ans.push_back(x);
	}
	reverse(ans.begin(),ans.end());
	
//	for(i=n,j=m;i>0&&j>0;i=x,j=y) {
//		x=prex[i][j]; y=prey[i][j];
//		if(f[i][j]==f[x][y]+a[i][j]) 
//			ans.push_back(j);
//	} 
//	sort(ans.begin(),ans.end());
	for(i=0;i<(int)ans.size();i++) 
		printf("%d ",ans[i]);
//	printf("\n");
//	LL sum=0;
//	for(i=1;i<=n;i++) 
//		sum+=a[i][ans[i-1]];
//	if(sum!=f[n][m]) printf("fault");
	return 0;
}

