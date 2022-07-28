#include<bitset>
#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=256,INF=1e8;
int n,k;
int f[N],g[N]; // f[i][j] 表示 在前i个数能组成的数中 %k==j 的最大数.
// 因为我们发现 mod k 每一个同余系我们只要最大的那一个。 
// 这里用滚动数组优化掉了第一维 
int w[N];
int main()
{
	int i,j;
	scanf("%d%d",&n,&k);
	fill(f+1,f+k,-INF);
	for(i=1;i<=n;i++) {
		scanf("%d",&w[i]);
		memcpy(g,f,sizeof g);
		fill(f+1,f+k,-INF);
		for(j=k-1;j>=0;j--) 
			f[j]=max(g[j],g[((j-w[i])%k+k)%k]+w[i]);
	}
	cout<<f[0]<<endl;
	return 0;
}
