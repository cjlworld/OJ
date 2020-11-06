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

const int N=305;

int n;
LL f[N][N],a[N],s[N];
// f[i][j] 表示合并石子 a[i]--a[j] 的最小代价。 
int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k,len;
	scanf("%d",&n);
	memset(f,0x3f,sizeof f);
	for(i=1;i<=n;i++) {
		scanf("%lld",&a[i]);
		f[i][i]=0;
		s[i]=s[i-1]+a[i];
	}
	for(len=2;len<=n;len++)  // 枚举区间长度 
		for(i=1;i+len-1<=n;i++) { // 枚举起点 
			j=i+len-1;
			for(k=i;k<=j-1;k++) // 枚举断点 
				f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]+s[j]-s[i-1]);
//			printf("%d %d : %lld \n",i,j,f[i][j]);
		}
	cout<<f[1][n]<<endl;
	return 0;
}

