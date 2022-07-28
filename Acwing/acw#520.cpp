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

const LL MOD=1e9+7;
const int N=1000+5,M=200+5;

int n,m,kk;

LL f[M][M][2],g[M][M][2];
char a[N],b[M];

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	scanf("%d%d%d",&n,&m,&kk);
	scanf("%s%s",a+1,b+1);
	
	f[0][0][0]=1;
	for(i=1;i<=n;i++) {
		memcpy(g,f,sizeof g);
		memset(f,0,sizeof f);
		for(j=0;j<=m;j++) {
			for(k=0;k<=kk;k++) {
				if(a[i]==b[j]) {
					f[j][k][1]=g[j-1][k][1];
					if(k>=1) 
						f[j][k][1]+=g[j-1][k-1][0]+g[j-1][k-1][1];
				}
				f[j][k][0]=g[j][k][0]+g[j][k][1];
				
				f[j][k][0]%=MOD,f[j][k][1]%=MOD;
				
//				printf("%d %d %d : %lld , %lld\n",i,j,k,f[j][k][0],f[j][k][1]);
 			}
		}
	}
	cout<<(f[m][kk][1]+f[m][kk][0])%MOD<<endl;
	return 0;
}

