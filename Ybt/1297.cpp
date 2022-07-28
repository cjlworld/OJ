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
char a[N],b[N]; 
int n,m;
int f[N][N]; 
// f[i][j] 表示 a[1]--a[i] 和 b[1]--b[j] 组成的最大公共子序列的长度。 

int main()
{
	int i,j;
	while(~scanf("%s%s",a+1,b+1)) {
		n=strlen(a+1),m=strlen(b+1);
		memset(f,0,sizeof f);
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++) {
				f[i][j]=max(f[i-1][j],f[i][j-1]);
				if(a[i]==b[j]) 
					f[i][j]=max(f[i][j],f[i-1][j-1]+1);
			}
		printf("%d\n",f[n][m]);
	}
	return 0;
}

