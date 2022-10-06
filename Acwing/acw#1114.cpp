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
typedef long double LD;
typedef unsigned long long ULL;

const int N=10;

int n,m;
char a[N][N];
bool vis[N];
LL ans;

void dfs(int row,int k) // 行，已经放了几个 
{
	if(m==k) return void(ans++);
	if(row==n+1) return;
	dfs(row+1,k); // 不放 
	for(int i=1;i<=n;i++) {
		if(a[row][i]=='.' || vis[i]) continue;
		vis[i]=true;
		dfs(row+1,k+1);
		vis[i]=false;
	} 
}

int main()
{
//	freopen("1.in","r",stdin);
	while(scanf("%d%d",&n,&m),(n!=-1 && m!=-1)) {
		for(int i=1;i<=n;i++) 
			scanf("%s",a[i]+1);
		memset(vis,false,sizeof vis);
		ans=0;
		dfs(1,0);
		printf("%lld\n",ans);
	}
	return 0;
}

