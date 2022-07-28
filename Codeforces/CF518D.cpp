#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<bitset>
#include<vector>
#include<cstdio>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=2000+5;

int n,m;
double p;
double f[N][N];
// f[i][j] 表示在第 i 秒,电梯上有 j 个人的概率。 

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	
	cin>>n>>p>>m;
	f[0][0]=1;
	for(i=1;i<=m;i++)
		for(j=0;j<=n;j++) {
			if(j) f[i][j]+=p*f[i-1][j-1];
			if(j<n) f[i][j]+=(1-p)*f[i-1][j];
			else f[i][j]+=f[i-1][j];
//			printf("f[%d][%d] = %lf\n",i,j,f[i][j]);
		}
		
	double ans=0;
	for(i=0;i<=n;i++)
		ans+=f[m][i]*i;
	printf("%.13lf\n",ans);
	return 0;
}

