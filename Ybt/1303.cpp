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

const int N=10+5;
int T,m,n; // 把m分成n份
LL f[N][N][N]; // f[k][i][j] 表示 已经分到第k个数字,分了i份,和为j的方案数。
 
int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k,r;
	cin>>T;
	while(T--) {
		cin>>m>>n;
		memset(f,0,sizeof f);
		f[0][0][0]=1;
		for(k=1;k<=m;k++) {
			for(i=1;i<=n;i++) 
				for(j=k;j<=m;j++) {
					for(r=0;r<=k;r++) 
						f[k][i][j]+=f[r][i-1][j-k];
				}
		}
		LL ans=0;
		for(k=1;k<=m;k++) 
			for(i=1;i<=n;i++) 
				ans+=f[k][i][m];
		cout<<ans<<endl;
	}
	return 0;
}

