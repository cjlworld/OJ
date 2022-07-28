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

const int N=2000+5;
char a[N],b[N];
int n,m,T;
int f[N][N];
// 由于操作都是对偶的，所以本题实际上是 1276【例9.20】编辑距离 
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	cin>>T;
	while(T--) {
		scanf("%s%s",a+1,b+1);
		n=strlen(a+1),m=strlen(b+1);
		memset(f,0x3f,sizeof f);
		for(i=0;i<=n;i++) f[i][0]=i;
		for(j=0;j<=m;j++) f[0][j]=j;
		for(i=1;i<=n;i++) {
			for(j=1;j<=m;j++) {
				if(a[i]==b[j]) f[i][j]=f[i-1][j-1];
				else f[i][j]=f[i-1][j-1]+1;
				f[i][j]=min(f[i][j],f[i][j-1]+1);
				f[i][j]=min(f[i][j],f[i-1][j]+1);
			}
		}
		cout<<f[n][m]<<endl;
	}

	return 0;
}

