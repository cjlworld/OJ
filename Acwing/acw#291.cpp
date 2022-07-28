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

// 一行一行考虑，先只填竖条，同时判断是否合法。

const int N=12,S=(1<<11);

int n,m; 
LL f[N][S];
int g[S];

int check(int t)
{
	if(~g[t]) return g[t];
	int cnt=0;
	for(int i=0;i<m;i++) {
		if((t>>i)&1) {
			if(cnt&1) return g[t]=0;
			cnt=0;
		}
		else cnt++;
	}
	if(cnt&1) return g[t]=0;
	else return g[t]=1;
}

int main()
{
	int i,j,k;
	
	printf("{0},\n");
	for(n=1;n<=11;n++) {
		printf("{0,");
		for(m=1;m<=11;m++) {
			memset(g,-1,sizeof g);
			memset(f,0,sizeof f);
			f[0][0]=1; // 竖条统一后一行填。 
			for(i=1;i<n;i++) {
				for(j=0;j<(1<<m);j++) {
					for(k=0;k<(1<<m);k++) {
						if(j&k || !check(j|k)) continue;
						f[i][j]+=f[i-1][k];
					}
				}
			}
			LL ans=0;
			for(j=0;j<(1<<m);j++) 
				if(check(j)) 
					ans+=f[n-1][j];
			
			printf("%lld,",ans);
		}
		printf("},\n");
	}

	return 0;
}

